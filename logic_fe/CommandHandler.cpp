//
// Created by Igor Gusakov
//

#include "CommandHandler.h"

namespace file_empower {

    commands CommandHandler::get_command(const std::string &input)
    {
        if (input.find("go .",0,4) != std::string::npos) {
            substr.clear();
            substr = input.substr(3);
            return commands::BACKWARD;
        }
        else if (input.find("go",0,2) != std::string::npos) {
            substr.clear();
            substr = input.substr(2);
            return commands::FORWARD;
        }
        else if (input == "exit") {
            return commands::EXIT;
        }
        else
            return commands::NONE;
    }

    uint8_t CommandHandler::count_back_step ( const std::string& data )
    {
        if( data.find(SYMBOL_BACKWARD) != std::string::npos )
            return std::count(data.begin(), data.end(),SYMBOL_BACKWARD);
        else
            return 0;
    }
}// namespace file_empower