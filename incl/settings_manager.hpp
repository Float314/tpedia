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

#include <string>

class settings_manager {
public:
    settings_manager();

    std::string get_lang_code() const;
    int get_search_limit() const;

    void set_lang_code(const std::string& code);
    void set_search_limit(int limit);

    enum class logo_style{
        blocky = 0,
        messy = 1
    };

    logo_style logo();
    void set_logo(logo_style style);

    void load();
    void save();

private:
    std::string get_config_dir() const;
    std::string get_config_path() const;

    std::string lang_code = "en";
    int search_limit = 10;
    logo_style lgo = logo_style::messy;
};
 