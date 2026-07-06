/* variables for logos. You are free to use these logos, under certain
   conditions -

   Conditions to use these logos -
   1. They follow the same redistirbutable material rules as GNU GPL
   2. You MUST NOT CLAIM that you wrote the original art.
   3. You should give proper credits to author.
   4. Just follow the rules cmon man its not even hard


   Material produced by - https://patorjk.com/software/taag (patorjk's text to
   ascii converter).
*/

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
#include <iostream>
#include <string>

namespace tpedia_logos {

std::string standard = R"md(
                                                     _______                     
        _________   _...._            __.....__    \  ___ `'.   .--.           
        \        |.'      '-.     .-''         '.   ' |--.\  \  |__|           
     .|  \        .'```'.    '.  /     .-''"'-.  `. | |    \  ' .--.           
   .' |_  \      |       \     \/     /________\   \| |     |  '|  |    __     
 .'     |  |     |        |    ||                  || |     |  ||  | .:--.'.   
'--.  .-'  |      \      /    . \    .-------------'| |     ' .'|  |/ |   \ |  
   |  |    |     |\`'-.-'   .'   \    '-.____...---.| |___.' /' |  |`" __ | |  
   |  |    |     | '-....-'`      `.             .'/_______.'/  |__| .'.''| |  
   |  '.' .'     '.                 `''-...... -'  \_______|/       / /   | |_ 
   |   /'-----------'                                               \ \._,\ '/ 
   `'-'                                                              `--'  `"  

)md";

std::string logo2 = R"md(
   ░██                                 ░██ ░██           
   ░██                                 ░██               
░████████ ░████████   ░███████   ░████████ ░██ ░██████   
   ░██    ░██    ░██ ░██    ░██ ░██    ░██ ░██      ░██  
   ░██    ░██    ░██ ░█████████ ░██    ░██ ░██ ░███████  
   ░██    ░███   ░██ ░██        ░██   ░███ ░██░██   ░██  
    ░████ ░██░█████   ░███████   ░█████░██ ░██ ░█████░██ 
          ░██                                            
          ░██                                            
                                                         
      )md";

std::string slogan = R"md(
╶┬╴╷ ╷╭─╴   ╭─╮╭─╴╭─╮╭─╴╭─╴╭─╴╶┬╴   ╭─╴╭╮╷╭─╴╷ ╷╭─╴╷  ╭─╮╭─╮╭─╴╶┬╮╷╭─╮
 │ ├─┤├╴    ├─╯├╴ ├┬╯├╴ ├╴ │   │    ├╴ │╰┤│  ╰┬╯│  │  │ │├─╯├╴  │││├─┤
 ╵ ╵ ╵╰─╴   ╵  ╰─╴╵╰╴╵  ╰─╴╰─╴ ╵    ╰─╴╵ ╵╰─╴ ╵ ╰─╴╰─╴╰─╯╵  ╰─╴╶┴╯╵╵ ╵
         ╭─╴╭─╮╭─╮   ╷ ╷╭─╮╷ ╷╭─╮   ╶┬╴╭─╴╭─╮╭┬╮╷╭╮╷╭─╮╷              
         ├╴ │ │├┬╯   ╰┬╯│ ││ │├┬╯    │ ├╴ ├┬╯│││││╰┤├─┤│              
         ╵  ╰─╯╵╰╴    ╵ ╰─╯╰─╯╵╰╴    ╵ ╰─╴╵╰╴╵ ╵╵╵ ╵╵ ╵╰─╴ 
    
    )md";

std::string legal_copyrights = R"md(
    tpedia - Copyright (C) 2026, Float314. Click on "About" For more details.
    Licensed under the GNU GPL. Powered by the Wikimedia Foundation.
    )md";

std::string standard_with_slogan = standard + slogan;
std::string st_slog_copyright = standard + slogan + legal_copyrights;

int *example_neovim_config =
    nullptr; // this doesnt does anything, its for checking the LSP for nvim
} // namespace tpedia_logos
