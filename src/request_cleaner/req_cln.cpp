#include "request_cleaner/req_cln.hpp"

std::string stripRefs(const std::string& input) {
    static const std::regex refTag(R"(<ref[^>]*>[\s\S]*?</ref>|<ref[^>]*/>)");
    return std::regex_replace(input, refTag, "");
}

std::string stripTemplates(const std::string& input) {
    std::string result;
    result.reserve(input.size());
    size_t i = 0;
    int depth = 0;
    while (i < input.size()) {
        if (input[i] == '{' && i + 1 < input.size() && input[i + 1] == '{') {
            depth += 2;
            i += 2;
        } else if (input[i] == '}' && i + 1 < input.size() && input[i + 1] == '}') {
            if (depth >= 2) {
                depth -= 2;
            } else {
                result += "}}";
            }
            i += 2;
        } else {
            if (depth == 0) {
                result += input[i];
            }
            ++i;
        }
    }
    return result;
}

std::string unwrapWikilinks(const std::string& input) {
    static const std::regex link(R"(\[\[([^\]|]*)(?:\|([^\]]*))?\]\])");
    return std::regex_replace(input, link, "$2$1");
}

std::string stripComments(const std::string& input) {
    static const std::regex comment(R"(<!--[\s\S]*?-->)");
    return std::regex_replace(input, comment, "");
}

std::string wikitextToPlain(const std::string& input) {
    std::string s = input;
    s = stripComments(s);
    s = stripRefs(s);
    s = stripTemplates(s);
    s = unwrapWikilinks(s);
    return s;
}
