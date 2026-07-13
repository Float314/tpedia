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

#include "settings_manager.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>
#include <cstdlib>

settings_manager::settings_manager() {
    load();
}

std::string settings_manager::get_lang_code() const {
    return lang_code;
}

int settings_manager::get_search_limit() const {
    return search_limit;
}

void settings_manager::set_lang_code(const std::string& code) {
    lang_code = code;
}

void settings_manager::set_search_limit(int limit) {
    search_limit = limit;
}

std::string settings_manager::get_config_dir() const {
#ifdef _WIN32
    // win32 default appdata
    const char* appdata = std::getenv("APPDATA");
    if (appdata) {
        return std::string(appdata) + "/tpedia";
    }
    return "./tpedia_config";
#elif defined(__APPLE__)
    // apple default
    const char* home = std::getenv("HOME");
    if (home) {
        return std::string(home) + "/Library/Application Support/tpedia";
    }
    return "./tpedia_config";
#else
    // linux 
    const char* xdg = std::getenv("XDG_CONFIG_HOME");
    if (xdg) {
        return std::string(xdg) + "/tpedia";
    }
    const char* home = std::getenv("HOME");
    if (home) {
        return std::string(home) + "/.config/tpedia";
    }
    return "./tpedia_config";
#endif
}

std::string settings_manager::get_config_path() const {
    return get_config_dir() + "/settings.json";
}

void settings_manager::load() {
    std::string path = get_config_path();
    std::ifstream file(path);
    if (!file.is_open()) {
        return;
    }

    try {
        nlohmann::json root;
        file >> root;

        if (root.contains("lang_code") && root["lang_code"].is_string()) {
            lang_code = root["lang_code"].get<std::string>();
        }
        if (root.contains("search_limit") && root["search_limit"].is_number_integer()) {
            search_limit = root["search_limit"].get<int>();
        }
    } catch (const nlohmann::json::parse_error&) {
    }
}

void settings_manager::save() {
    std::filesystem::create_directories(get_config_dir());

    nlohmann::json root;
    root["lang_code"] = lang_code;
    root["search_limit"] = search_limit;
    if(lgo == settings_manager::logo_style::messy) {
        root["logo_style"] = 0;
    }
    if(lgo == settings_manager::logo_style::blocky) {
        root["logo_style"] = 1;
    }

    std::ofstream file(get_config_path());
    if (file.is_open()) {
        file << root.dump(2);
    }
}

settings_manager::logo_style settings_manager::logo() {
    return lgo;
}