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

#include "ui/about.hpp"
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

about::about() {
    text =R"md(
tpedia - Wikipedia (Terminal mode!)

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

This program also uses Wikimedia API and the MediaWiki API for 
searches and results.

Libraries - 
- matjson (github: geode-sdk/json) [JSON Parsing] Under Boost Software 
  License v1.0
- result (github: geode-sdk/result) [Dependency of MATJson] Under Boost
  Software License v1.0
- FTXUI (github: ArthurSonzogni/FTXUI) [Terminal IO Handling, is a VERY 
  Great Library] Under MIT License
- cpp-httplib (github: yhirose/cpp-httplib) [Great Library for HTTPS 
  Requests!]
- OpenSSL (website: <https://www.openssl.org/>, github: openssl/openssl)
  [Cryptography and SSL Library, dependency of cpp-httplib] Under the
  Apache 2.0 License


All of these licenses can be found in the docs/ folder of the source
code (<https://github.com/Float314/tpedia>).
    )md";

    body = ftxui::Renderer([this] {
        return ftxui::vbox({
            ftxui::filler(),
            ftxui::text("About tpedia") | ftxui::bold | ftxui::center | ftxui::color(ftxui::Color::IndianRed1Bis),
            ftxui::paragraph(text) | ftxui::center,
            ftxui::filler(),
            ftxui::text("Thank you!") | ftxui::center | ftxui::color(ftxui::Color::Red3),
        }) | ftxui::flex;
    });
}

ftxui::Component about::MainBodyComponent() {
    return body;
}
