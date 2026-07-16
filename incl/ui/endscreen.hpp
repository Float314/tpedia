#include <ftxui/ftxui.hpp>
#include <ftxui/screen/screen.hpp>

class endscreen {
    private:
        ftxui::Element endscreen_doc =  ftxui::hbox({
        ftxui::text("Join the tpedia discord server! <https://discord.gg/W6X3gXMpmA>") | ftxui::border | ftxui::color(ftxui::Color::Purple4Bis)
    });;
        ftxui::Screen endscreen = ftxui::Screen::Create(
            ftxui::Dimension::Full(),
            ftxui::Dimension::Fit(endscreen_doc)
        );
    public: 
        int* render();
};