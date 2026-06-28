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

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>
#include <format>
#include <matjson.hpp>
#include <string>
#include <vector>

struct search_result_item {
    std::string title;
    std::string snippet;
};

struct rawrequest_result {
    std::string content;
    int http_status = 0;
    std::string error_message;
};

class wikipedia_client {
    private:
        std::string query;
        std::string wikipedia_server;
        httplib::SSLClient cli;
    public:
        wikipedia_client() : cli("en.wikipedia.org") {}
        rawrequest_result rawrequest(const std::string& thedamnpage);
        std::vector<search_result_item> search_pages(const std::string& query, int limit = 10);
};
