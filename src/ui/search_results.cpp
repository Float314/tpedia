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

#include "ui/search_results.hpp"
#include "ui/scrollbar.hpp"
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/event.hpp>

search_results::search_results() : selected(0) {
    body = ftxui::Container::Vertical({
        ftxui::Renderer([this] {
            return ftxui::vbox({
                ftxui::filler(),
                ftxui::text("No search results.") | ftxui::center,
                ftxui::filler(),
            }) | ftxui::flex;
        }),
    });
}

ftxui::Component search_results::MainBodyComponent() {
    return body;
}

void search_results::rebuild_list() {
    row_comps.clear();
    body->DetachAllChildren();

    if (results.empty()) {
        body->Add(ftxui::Renderer([this] {
            return ftxui::vbox({
                ftxui::filler(),
                ftxui::text("No search results.") | ftxui::center,
                ftxui::filler(),
            }) | ftxui::flex;
        }));
        return;
    }

    std::vector<ftxui::Component> rows;
    row_comps.resize(results.size());

    for (size_t i = 0; i < results.size(); ++i) {
        auto& rc = row_comps[i];

        rc.go_button = ftxui::Button(" Go to this Page ", [this, i] {
            if (on_open_article && i < results.size()) {
                on_open_article(results[i].title);
            }
        });

        auto row = ftxui::Container::Horizontal({
            rc.go_button,
        });

        auto row_renderer = ftxui::Renderer(row, [this, i, &rc] {
            bool is_selected = (static_cast<int>(i) == selected);
            auto title_elem = ftxui::text(results[i].title) | ftxui::bold;
            auto snippet_elem = ftxui::text("  " + results[i].snippet)
                | ftxui::color(ftxui::Color::GrayDark);

            if (is_selected) {
                title_elem = title_elem | ftxui::color(ftxui::Color::Cyan);
            }

            return ftxui::hbox({
                ftxui::vbox({
                    title_elem,
                    snippet_elem,
                }) | ftxui::flex,
                rc.go_button->Render(),
            });
        });

        rows.push_back(row_renderer);
    }

    auto list = ftxui::Container::Vertical(std::move(rows));

    auto content = ftxui::Renderer(list, [this, list] {
        return ftxui::vbox({
            ftxui::text("") | ftxui::bold | ftxui::center,
            // ftxui::separator(),
            list->Render() | ftxui::flex,
        }) | ftxui::flex;
    });

    body->Add(ftxui::CatchEvent(content, [this](ftxui::Event event) {
        if (event == ftxui::Event::Return && !results.empty()) {
            if (on_open_article) {
                on_open_article(results[selected].title);
            }
            return true;
        }
        if (event == ftxui::Event::ArrowUp || event == ftxui::Event::Character('k')) {
            if (selected > 0) {
                --selected;
            }
            return true;
        }
        if (event == ftxui::Event::ArrowDown || event == ftxui::Event::Character('j')) {
            if (selected < static_cast<int>(results.size()) - 1) {
                ++selected;
            }
            return true;
        }
        return false;
    }));
}

void search_results::set_results(const std::vector<search_result_item>& items) {
    results = items;
    selected = 0;
    rebuild_list();
}

void search_results::set_on_open_article(std::function<void(std::string)> cb) {
    on_open_article = std::move(cb);
}
