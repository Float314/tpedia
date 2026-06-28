/* variables for logos. Yo are wish to use these logos for your projects
   if this api is useful for you. 
   
   Conditions to use these logos - 
   1. They follow the same redistirbutable material rules as GNU GPL And CC-BY4.0
   2. You MUST NOT CLAIM that you wrote the original art. 
   3. You should give proper credits to author. 
   4. Just follow the rules cmon man its not even hard


   Material produced by - https://patorjk.com/software/taag (patorjk's text to ascii 
   converter).   
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
#include <iostream>

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

    std::string slogan = R"md(
╶┬╴╷ ╷╭─╴   ╭─╮╭─╴╭─╮╭─╴╭─╴╭─╴╶┬╴   ╭─╴╭╮╷╭─╴╷ ╷╭─╴╷  ╭─╮╭─╮╭─╴╶┬╮╷╭─╮
 │ ├─┤├╴    ├─╯├╴ ├┬╯├╴ ├╴ │   │    ├╴ │╰┤│  ╰┬╯│  │  │ │├─╯├╴  │││├─┤
 ╵ ╵ ╵╰─╴   ╵  ╰─╴╵╰╴╵  ╰─╴╰─╴ ╵    ╰─╴╵ ╵╰─╴ ╵ ╰─╴╰─╴╰─╯╵  ╰─╴╶┴╯╵╵ ╵
         ╭─╴╭─╮╭─╮   ╷ ╷╭─╮╷ ╷╭─╮   ╶┬╴╭─╴╭─╮╭┬╮╷╭╮╷╭─╮╷              
         ├╴ │ │├┬╯   ╰┬╯│ ││ │├┬╯    │ ├╴ ├┬╯│││││╰┤├─┤│              
         ╵  ╰─╯╵╰╴    ╵ ╰─╯╰─╯╵╰╴    ╵ ╰─╴╵╰╴╵ ╵╵╵ ╵╵ ╵╰─╴ 
    
    )md";

    std::string legal_copyrights = R"md(
 Licensed under the GNU GPL v3 and CC-BY 4.0
 Contents provided by the Wikimedia foundation. (Through Wikipedia API).
 Copyright (C) Float314. 
 Copyright (C) The Wikimedia Foundation.
 All rights reserved.
    )md";

    std::string standard_with_slogan = standard + slogan;
    std::string st_slog_copyright = standard + slogan + legal_copyrights;
}