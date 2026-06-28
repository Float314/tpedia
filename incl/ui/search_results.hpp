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
#include "api/wikipedia_client.hpp"
#include <functional>
#include <string>
#include <vector>
#include <memory>

class search_results : public main_screen {
private:
    std::vector<search_result_item> results;
    ftxui::Component body;
    std::function<void(std::string)> on_open_article;
    int selected;

    struct row_components {
        ftxui::Component go_button;
    };
    std::vector<row_components> row_comps;

    void rebuild_list();

public:
    search_results();
    ftxui::Component MainBodyComponent() override;
    void set_results(const std::vector<search_result_item>& items);
    void set_on_open_article(std::function<void(std::string)> cb);
};
