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
#include <functional>
#include <string>

class homepage : public main_screen {
private:
    settings_manager& set;
    std::string search_query;
    ftxui::Component input;
    ftxui::Component body;
    std::function<void(std::string)> on_search;
    std::string query_progress;
public:
    homepage(settings_manager& settings);
    ftxui::Component MainBodyComponent() override;
    void set_on_search(std::function<void(std::string)> cb);
    void clear_progress();
};
