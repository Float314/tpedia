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

#include "ui/wiki_text.hpp"
#include "request_cleaner/req_cln.hpp"
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

wiki_text::wiki_text() {
    text = "Loading...";
    scrollable = scroll_text_comp();
    body = ftxui::Renderer(scrollable, [this] {
        return ftxui::vbox({
            ftxui::text(page_title) | ftxui::bold | ftxui::center | ftxui::underlined,
            ftxui::separator(),
            scrollable->Render() | ftxui::flex,
        }) | ftxui::flex;
    });
}

ftxui::Component wiki_text::MainBodyComponent() {
    return body;
}

void wiki_text::load_page(const std::string& title) {
    page_title = title;
    auto result = wiki_client.rawrequest(title);
    if (result.http_status != 200 || result.content.empty()) {
        text = "Failed to load page: " + title + "\n";
        if (result.http_status == 0) {
            text += "Connection error: " + result.error_message;
        } else {
            text += "HTTP " + std::to_string(result.http_status);
            if (!result.error_message.empty()) {
                text += " - " + result.error_message;
            }
        }
        return;
    }
    text = wikitextToPlain(result.content);
}
