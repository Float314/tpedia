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
#pragma once

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/event.hpp>
#include <functional>
#include <string>

class main_screen {
protected:
    std::string text;
public:
    virtual ~main_screen() = default;
    void setText(const std::string& t);
    const std::string& getText() const;

    ftxui::Component text_renderer_comp();
    ftxui::Component scroll_text_comp();

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
    header();

    void set_on_home(std::function<void()> cb);
    void set_on_search(std::function<void()> cb);
    void set_on_about(std::function<void()> cb);
    void set_on_close(std::function<void()> cb);
    void set_title(const std::string& t);

    ftxui::Component Render();
};
