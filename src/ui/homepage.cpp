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
#include "ui/homepage.hpp"
#include "macros.hpp"
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/event.hpp>

homepage::homepage(settings_manager& settings)
    : set(settings)
{
    input = ftxui::Input(&search_query, "Search Wikipedia...");

    auto vertical = ftxui::Container::Vertical({input});

    body = ftxui::Renderer(vertical, [&] {
        const auto& logo = (set.logo() == settings_manager::logo_style::blocky)
            ? tpedia_logos::logo2_with_slogan
            : tpedia_logos::standard_with_slogan;

        auto base = ftxui::vbox({
            ftxui::filler(),
            ftxui::text(logo) | ftxui::center,
            ftxui::separator() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 15) | ftxui::center,
            ftxui::text("Enter a search term to begin.") | ftxui::center | ftxui::bold,
            input->Render() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 25) | ftxui::center,
            ftxui::separator() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 15) | ftxui::center,
            ftxui::filler(),
            ftxui::separator(),
            ftxui::text(tpedia_logos::legal_copyrights)
        }) | ftxui::flex;

        if (!query_progress.empty()) {
            base = ftxui::dbox({
                base,
                ftxui::text(query_progress) | ftxui::center | ftxui::bold
                    | ftxui::color(ftxui::Color::Yellow) | ftxui::border | ftxui::clear_under | ftxui::center,
            });
        }

        return base;
    });

    body = ftxui::CatchEvent(body, [this](ftxui::Event event) {
        if (event == ftxui::Event::Return && !search_query.empty()) {
            if (on_search) {
                query_progress = "This may take a few moments...";
                on_search(search_query);
            }
            return true;
        }
        return false;
    });
}

ftxui::Component homepage::MainBodyComponent() {
    return body;
}

void homepage::clear_progress() {
    query_progress = "";
}

void homepage::set_on_search(std::function<void(std::string)> cb) {
    on_search = std::move(cb);
}