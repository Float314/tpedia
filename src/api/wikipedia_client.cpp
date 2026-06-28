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

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "api/wikipedia_client.hpp"
#include <httplib.h>
#include <format>
#include <matjson.hpp>
#include <cstdio>
#include <string>

rawrequest_result wikipedia_client::rawrequest(const std::string& thedamnpage) {
    std::string encoded = thedamnpage;
    size_t pos = 0;
    while ((pos = encoded.find(' ', pos)) != std::string::npos) {
        encoded.replace(pos, 1, "_");
        pos += 1;
    }

    auto html_res = cli.Get("/w/rest.php/v1/page/" + encoded + "/html");
    if (!html_res) {
        auto err = html_res.error();
        std::string msg = std::format("HTTP Error [rawrequest GET]: {}", static_cast<int>(err));
        std::fprintf(stderr, "%s\n", msg.c_str());
        return {"", 0, msg};
    }

    if (html_res->status != 200) {
        std::string msg = std::format("HTTP Error [rawrequest GET]: status {} - {}", html_res->status, html_res->body);
        std::fprintf(stderr, "%s\n", msg.c_str());
        return {"", html_res->status, msg};
    }

    auto json_payload = matjson::Value::object();
    json_payload.set("html", html_res->body);
    json_payload.set("scrub_wikitext", true);

    auto wiki_res = cli.Post("/w/rest.php/v1/transform/html/to/wikitext", json_payload.dump(), "application/json");
    if (!wiki_res) {
        auto err = wiki_res.error();
        std::string msg = std::format("HTTP Error [rawrequest POST]: {}", static_cast<int>(err));
        std::fprintf(stderr, "%s\n", msg.c_str());
        return {"", 0, msg};
    }

    if (wiki_res->status != 200) {
        std::string msg = std::format("HTTP Error [rawrequest POST]: status {} - {}", wiki_res->status, wiki_res->body);
        std::fprintf(stderr, "%s\n", msg.c_str());
        return {"", wiki_res->status, msg};
    }

    auto content = wiki_res->body;
    if (content.empty()) {
        std::string msg = "Empty wikitext returned for page: " + thedamnpage;
        std::fprintf(stderr, "%s\n", msg.c_str());
        return {"", 200, msg};
    }

    return {content, 200, ""};
}

std::vector<search_result_item> wikipedia_client::search_pages(const std::string& query, int limit) {
    std::vector<search_result_item> results;

    httplib::Params params;
    params.emplace("q", query);
    params.emplace("limit", std::to_string(limit));

    auto req = cli.Get("/w/rest.php/v1/search/page", params, httplib::Headers());
    if (!req) {
        auto err = req.error();
        std::string msg = std::format("HTTP Error [search_pages]: {}", static_cast<int>(err));
        std::fprintf(stderr, "%s\n", msg.c_str());
        return results;
    }

    if (req->status != 200) {
        std::string msg = std::format("HTTP Error [search_pages]: status {} - {}", req->status, req->body);
        std::fprintf(stderr, "%s\n", msg.c_str());
        return results;
    }

    std::string json_raw = req->body;
    auto parse = matjson::parse(json_raw);
    if (!parse) {
        std::string msg = "JSON parse error [search_pages]: " + parse.err()->message;
        std::fprintf(stderr, "%s\n", msg.c_str());
        return results;
    }

    auto root = parse.unwrap();
    auto pages = root["pages"];
    if (!pages.isArray()) {
        return results;
    }

    for (auto& page : pages) {
        auto title = page["title"].as<std::string>().unwrapOr("");
        auto excerpt = page["excerpt"].as<std::string>().unwrapOr("");
        results.push_back({title, excerpt});
    }

    return results;
}
