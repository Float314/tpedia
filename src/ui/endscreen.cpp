#include "ui/endscreen.hpp"
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>

int* endscreen::render() {
    ftxui::Render(endscreen, endscreen_doc); 
    endscreen.Print();
    return 0;
}