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
#include "ui/homepage.hpp"
#include "ui/search_results.hpp"
#include "ui/about.hpp"
#include "ui/wiki_text.hpp"
#include "api/wikipedia_client.hpp"
#include <memory>
#include <thread>
#include <atomic>
#include <mutex>
#include <vector>

class application {
public:
    enum class Page { Home, Search, About, Article };

private:
    ftxui::ScreenInteractive screen;

    header header_bar;
    wikipedia_client wiki_client;

    std::unique_ptr<homepage> home_page;
    std::unique_ptr<search_results> search_page;
    std::unique_ptr<about> about_page;
    std::unique_ptr<wiki_text> article_page;

    ftxui::Component home_comp;
    ftxui::Component search_comp;
    ftxui::Component about_comp;
    ftxui::Component article_comp;

    ftxui::Component body_container;
    ftxui::Component main_layout;
    ftxui::Component event_handler;
    Page current_page;

    std::mutex wiki_mutex;
    std::atomic<bool> async_search_ready{false};
    std::vector<search_result_item> async_search_results;
    std::string async_search_query;
    std::atomic<int> search_gen{0};

    std::atomic<bool> async_article_ready{false};
    std::string async_article_title;
    std::string async_article_content;

    ftxui::Component wrap_with_maybe(ftxui::Component comp, Page page);
    void handle_async_completions();

public:
    application();
    ~application();
    void run();
    void switch_to(Page page);
    void search_query(const std::string& query);
};
