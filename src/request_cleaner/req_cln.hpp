/* Response cleaner for cleaning responses */

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

#include <string>
#include <regex>

// Remove <ref>...</ref> blocks entirely (this is ugly)
std::string stripRefs(const std::string& input) {
    static const std::regex refTag(R"(<ref[^>]*>[\s\S]*?</ref>|<ref[^>]*/>)");
    return std::regex_replace(input, refTag, "");
}

// Remove any remaining {{...}} templates 
std::string stripTemplates(const std::string& input) {
    std::string result;
    result.reserve(input.size());
    size_t i = 0;
    while (i < input.size()) {
        if (input[i] == '{' && i + 1 < input.size() && input[i + 1] == '{') {
            size_t end = input.find("}}", i + 2);
            if (end != std::string::npos) {
                i = end + 2;
                continue;
            }
        }
        result += input[i];
        ++i;
    }
    return result;
}

// Unwrap [[target|display]] or [[target]] to just the display text
std::string unwrapWikilinks(const std::string& input) {
    static const std::regex link(R"(\[\[([^\]|]*)(?:\|([^\]]*))?\]\])");
    return std::regex_replace(input, link, "$2$1");
    // note: $2 (display text) wins if present, else falls back to $1 (target)
}


std::string wikitextToPlain(const std::string& input) {
    std::string s = input;
    s = stripRefs(s);
    s = stripTemplates(s);
    s = unwrapWikilinks(s);
    return s;
}