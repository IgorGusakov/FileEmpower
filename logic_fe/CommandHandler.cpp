//
// Created by Igor Gusakov on 08.05.2023.
//

#include "CommandHandler.h"

namespace file_empower {

    commands CommandHandler::get_command(const std::string &input)
    {
        if (input.find("back",0,4) != std::string::npos) {
            substr.clear();
            substr = input.substr(4);
            return commands::BACK;
        }
        else if (input.find("go",0,2) != std::string::npos) {
            substr.clear();
            substr = input.substr(2);
            return commands::GO;
        }
        else if (input == "exit") {
            return commands::EXIT;
        }
        else
            return commands::NONE;
    }

    uint8_t CommandHandler::count_back_step ( const std::string& data )
    {
        if( data.find('.') != std::string::npos )
            return std::count(data.begin(), data.end(),'.');
        else
            return 0;
    }
}// namespace file_empower