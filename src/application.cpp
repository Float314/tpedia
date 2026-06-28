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
      current_page(Page::Home)
{
    home_page = std::make_unique<homepage>();
    search_page = std::make_unique<search_results>();
    about_page = std::make_unique<about>();
    article_page = std::make_unique<wiki_text>();

    home_comp = home_page->MainBodyComponent();
    search_comp = search_page->MainBodyComponent();
    about_comp = about_page->MainBodyComponent();
    article_comp = article_page->MainBodyComponent();

    header_bar.set_on_home([this] { switch_to(Page::Home); });
    header_bar.set_on_search([this] { switch_to(Page::Search); });
    header_bar.set_on_about([this] { switch_to(Page::About); });
    header_bar.set_on_close([this] { screen.Exit(); });

    home_page->set_on_search([this](const std::string& query) {
        search_query(query);
    });

    search_page->set_on_open_article([this](const std::string& title) {
        article_page->load_page(title);
        header_bar.set_title(title);
        switch_to(Page::Article);
    });

    body_container = ftxui::Container::Vertical({
        wrap_with_maybe(home_comp, Page::Home),
        wrap_with_maybe(search_comp, Page::Search),
        wrap_with_maybe(about_comp, Page::About),
        wrap_with_maybe(article_comp, Page::Article),
    });

    main_layout = ftxui::Container::Vertical({
        header_bar.Render(),
        body_container | ftxui::flex,
    });
}

void application::run() {
    screen.Loop(main_layout);
}

void application::switch_to(Page page) {
    current_page = page;
    header_bar.set_title(
        page == Page::Home ? "tpedia - Terminal Wikipedia" :
        page == Page::Search ? "Search Results" :
        page == Page::About ? "About tpedia" :
        "Article"
    );
}

void application::search_query(const std::string& query) {
    header_bar.set_title("Searching: " + query);

    auto results = wiki_client.search_pages(query);

    search_page->set_results(results);

    if (!results.empty()) {
        article_page->load_page(results[0].title);
    }

    switch_to(Page::Search);
}
