/* Application to manage screens */
/*
    tpedia
    Copyright (C) 2026, Float314

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "application.hpp"
#include "request_cleaner/req_cln.hpp"
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <memory>

ftxui::Component application::wrap_with_maybe(ftxui::Component comp, Page page) {
    return ftxui::Maybe(comp, [this, page] {
        return current_page == page;
    });
}

application::application()
    : screen(ftxui::ScreenInteractive::Fullscreen()),
      wiki_client(settings.get_lang_code()),
      current_page(Page::Home),
      previous_page(Page::Home)
{
    home_page = std::make_unique<homepage>(settings);
    search_page = std::make_unique<search_results>();
    settings_page = std::make_unique<settings_screen>(settings);
    about_page = std::make_unique<about>();
    article_page = std::make_unique<wiki_text>();

    home_comp = home_page->MainBodyComponent();
    search_comp = search_page->MainBodyComponent();
    settings_comp = settings_page->MainBodyComponent();
    about_comp = about_page->MainBodyComponent();
    article_comp = article_page->MainBodyComponent();

    header_bar.set_on_home([this] { switch_to(Page::Home); });
    header_bar.set_on_search([this] { switch_to(Page::Search); });
    header_bar.set_on_settings([this] { switch_to(Page::Settings); });
    header_bar.set_on_close([this] { screen.Exit(); });

    settings_page->set_on_about([this] {
        previous_page = Page::Settings;
        switch_to(Page::About);
    });

    about_page->set_on_back([this] {
        switch_to(previous_page);
    });

    home_page->set_on_search([this](const std::string& query) {
        search_query(query);
    });

    search_page->set_on_open_article([this](const std::string& title) {
        async_article_title = title;

        std::thread([this, title]() {
            rawrequest_result raw;
            {
                std::lock_guard<std::mutex> lock(wiki_mutex);
                raw = wiki_client.rawrequest(title);
            }

            std::string content;
            if (raw.http_status != 200 || raw.content.empty()) {
                content = "Failed to load page: " + title + "\n";
                if (raw.http_status == 0) {
                    content += "Connection error: " + raw.error_message;
                } else {
                    content += "HTTP " + std::to_string(raw.http_status);
                    if (!raw.error_message.empty()) {
                        content += " - " + raw.error_message;
                    }
                }
            } else {
                content = wikitextToPlain(raw.content);
            }

            async_article_content = std::move(content);
            async_article_ready.store(true, std::memory_order_release);
            screen.PostEvent(ftxui::Event::Custom);
        }).detach();
    });

    body_container = ftxui::Container::Vertical({
        wrap_with_maybe(home_comp, Page::Home),
        wrap_with_maybe(search_comp, Page::Search),
        wrap_with_maybe(settings_comp, Page::Settings),
        wrap_with_maybe(about_comp, Page::About),
        wrap_with_maybe(article_comp, Page::Article),
    });

    main_layout = ftxui::Container::Vertical({
        header_bar.Render(),
        body_container | ftxui::flex,
    });

    event_handler = ftxui::CatchEvent(main_layout, [this](ftxui::Event event) {
        if (event == ftxui::Event::Custom) {
            handle_async_completions();
            return true;
        }
        return false;
    });
}

application::~application() {
    search_gen.store(search_gen.load() + 1);
}

void application::run() {
    screen.Loop(event_handler);
}

void application::switch_to(Page page) {
    current_page = page;
    header_bar.set_title(
        page == Page::Home ? "tpedia - Terminal Wikipedia" :
        page == Page::Search ? "Search Results" :
        page == Page::Settings ? "Settings" :
        page == Page::About ? "About tpedia" :
        "Article"
    );
}

void application::search_query(const std::string& query) {
    header_bar.set_title("Searching: " + query);
    int gen = ++search_gen;

    std::thread([this, query, gen]() {
        std::vector<search_result_item> results;
        {
            std::lock_guard<std::mutex> lock(wiki_mutex);
            results = wiki_client.search_pages(query, settings.get_search_limit());
        }

        if (gen != search_gen.load()) {
            return;
        }

        async_search_results = std::move(results);
        async_search_query = query;
        async_search_ready.store(true, std::memory_order_release);
        screen.PostEvent(ftxui::Event::Custom);
    }).detach();
}

void application::handle_async_completions() {
    if (async_search_ready.load(std::memory_order_acquire)) {
        async_search_ready.store(false);
        home_page->clear_progress();
        search_page->set_results(async_search_results);
        switch_to(Page::Search);
    }

    if (async_article_ready.load(std::memory_order_acquire)) {
        async_article_ready.store(false);
        search_page->clear_loading();
        article_page->set_content(async_article_title, async_article_content);
        switch_to(Page::Article);
        header_bar.set_title(async_article_title);
    }
}
