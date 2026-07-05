/* Header for the program. */

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

#include "ui/header.hpp"
#include "ui/scrollbar.hpp"
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

class main_screen { // main vase class for childeren Screnns
protected:
    std::string text;
public:
    virtual ~main_screen() = default;
    void setText(const std::string& t) { text = t; };
    const std::string& getText() const { return text; }; // ragebaited at one liners :)

    ftxui::Component text_renderer_comp() {
        return ftxui::Renderer([this] {
            return ftxui::paragraph(text);
        });
    };

    ftxui::Component scroll_text_comp() {
        return ftxui::Scroller(text_renderer_comp());
    }

    virtual ftxui::Component MainBodyComponent() = 0;
};

class header {
private:
    ftxui::Component home_btn;
    ftxui::Component search_btn;
    ftxui::Component about_btn;
    ftxui::Component close_btn;
    ftxui::Component layout;
    std::function<void()> on_home;
    std::function<void()> on_search;
    std::function<void()> on_about;
    std::function<void()> on_close;
    std::string title_text;
public:
    header() : title_text("tpedia - Terminal Wikipedia") {
            home_btn = ftxui::Button("Home", [this] {
                if (on_home) on_home();
            });
        search_btn = ftxui::Button("Search", [this] {
            if (on_search) on_search();
        });
        about_btn = ftxui::Button("About", [this] {
            if (on_about) on_about();
        });
        close_btn = ftxui::Button("Close", [this] {
            if (on_close) on_close();
        });

        auto btn_container = ftxui::Container::Horizontal({
            home_btn,
            search_btn,
            about_btn,
            close_btn,
        });

        layout = ftxui::Renderer(btn_container, [this] {
            return ftxui::hbox({
                home_btn->Render(),
                search_btn->Render(),
                ftxui::filler(),
                ftxui::text(title_text) | ftxui::vcenter,
                ftxui::filler(),
                about_btn->Render(),
                close_btn->Render(),
            }) | ftxui::color(ftxui::Color::White) | ftxui::bgcolor(ftxui::Color::Blue);
        });
    };

    void set_on_home(std::function<void()> cb) { on_home = std::move(cb); };
    void set_on_search(std::function<void()> cb) { on_search = std::move(cb); };
    void set_on_about(std::function<void()> cb) { on_about = std::move(cb); };
    void set_on_close(std::function<void()> cb) { on_close = std::move(cb); };
    void set_title(const std::string& t) {title_text = t;};

    ftxui::Component Render() { return layout; };
};