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

#include "ui/header.hpp"
#include "settings_manager.hpp"
#include <vector>

class settings_screen : public main_screen {
private:
    settings_manager& set;
    ftxui::Component body;

    std::string lang_input;
    std::string limit_input;
    std::string status_msg;
    int logo_style_idx;
    std::vector<std::string> logo_style_entries;

    ftxui::Component lang_input_comp;
    ftxui::Component limit_input_comp;
    ftxui::Component logo_style_comp;
    ftxui::Component save_btn;
    ftxui::Component about_btn;

    std::function<void()> on_about;
    void build_ui();

public:
    settings_screen(settings_manager& settings);
    void set_on_about(std::function<void()> cb);
    ftxui::Component MainBodyComponent() override;
};
