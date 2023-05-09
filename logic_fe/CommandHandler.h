//
// Created by Igor Gusakov on 08.05.2023.
//

#ifndef FILEEMPOWER_COMMANDHANDLER_H
#define FILEEMPOWER_COMMANDHANDLER_H
#include "string"
#include <cstdint>
#include <algorithm>

namespace file_empower {

    enum class commands {
        NONE,
        GO,
        BACK,
        CREATE,
        CRYPT,
        ENCRYPT,
        EXIT
    };

    class CommandHandler {
    public:
        explicit CommandHandler() = default;
        commands get_command ( const std::string& input );
        uint8_t count_back_step ( const std::string& data );
    private:
        std::string substr;
    };

}// namespace file_empower

#endif//FILEEMPOWER_COMMANDHANDLER_H
