/* Settings screen */

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

#include "ui/settings.hpp"
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>

settings_screen::settings_screen(settings_manager& settings)
    : set(settings)
{
    lang_input = set.get_lang_code();
    limit_input = std::to_string(set.get_search_limit());
    logo_style_idx = (set.logo() == settings_manager::logo_style::blocky) ? 0 : 1;
    logo_style_entries = {"Blocky", "Messy"};
    build_ui();
}

void settings_screen::build_ui() {
    lang_input_comp = ftxui::Input(&lang_input, "Language code (e.g. en)");
    limit_input_comp = ftxui::Input(&limit_input, "Search limit (e.g. 10)");
    logo_style_comp = ftxui::Radiobox(&logo_style_entries, &logo_style_idx);

    save_btn = ftxui::Button("Save", [this] {
        set.set_lang_code(lang_input);
        try {
            int val = std::stoi(limit_input);
            if (val < 1) val = 1;
            if (val > 50) val = 50;
            set.set_search_limit(val);
            limit_input = std::to_string(val);
        } catch (...) {
            status_msg = "Invalid search limit!";
            return;
        }
        set.set_logo(logo_style_idx == 0
            ? settings_manager::logo_style::blocky
            : settings_manager::logo_style::messy);
        set.save();
        status_msg = "Settings saved!";
    });

    about_btn = ftxui::Button("About", [this] {
        if (on_about) on_about();
    });

    auto settings_form = ftxui::Container::Vertical({
        lang_input_comp,
        limit_input_comp,
        logo_style_comp,
        save_btn,
        about_btn,
    });

    body = ftxui::Renderer(settings_form, [this] {
        auto status_el = status_msg.empty()
            ? ftxui::text("")
            : ftxui::text(status_msg) | ftxui::center | ftxui::color(ftxui::Color::Green);

        return ftxui::vbox({
            ftxui::text("Join the Tpedia Discord server! <https://discord.gg/W6X3gXMpmA>") | ftxui::center | ftxui::border | ftxui::color(ftxui::Color::Purple4Bis),
            ftxui::separator(),
            ftxui::hbox({
                ftxui::filler(),
                ftxui::vbox({
                    ftxui::hbox({
                        ftxui::text("Language Code: "),
                        lang_input_comp->Render() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 20),
                    }),
                    ftxui::hbox({
                        ftxui::text("Search Limit : "), /* Fix spacing */
                        limit_input_comp->Render() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 20),
                    }),
                    ftxui::hbox({
                        ftxui::text("Logo Style   : "),
                        logo_style_comp->Render() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 20),
                    }),
                    ftxui::separator(),
                    save_btn->Render() | ftxui::center | ftxui::vcenter,
                    status_el,
                    ftxui::separator(),
                    about_btn->Render() | ftxui::center,
                }) | ftxui::border,
                ftxui::filler(),
            }),
            ftxui::filler(),
        }) | ftxui::flex | ftxui::borderDashed;
    });
}

ftxui::Component settings_screen::MainBodyComponent() {
    return body;
}

void settings_screen::set_on_about(std::function<void()> cb) {
    on_about = std::move(cb);
}
