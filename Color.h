//
// Created by Igor Gusakov on 02.04.2023.
//

#ifndef FILEEMPOWER_COLOR_H
#define FILEEMPOWER_COLOR_H

#include <string>
namespace file_empower {
    class Color {
    public:
        enum class Code {
            FG_RED = 31,
            FG_GREEN = 32,
            FG_YELLOW = 33,
            FG_BLUE = 34,
            FG_CYAN = 36,
            FG_DEFAULT = 39,
            BG_RED = 41,
            BG_GREEN = 42,
            BG_YELLOW = 43,
            BG_BLUE = 44,
            BG_DEFAULT = 49
        };

        static std::string code(Code color) {
            return "\033[" + std::to_string(static_cast<int>(color)) + "m";
        }

        static std::string reset_fg() {
            return code(Code::FG_DEFAULT);
        }

        static std::string reset_bg() {
            return code(Code::BG_DEFAULT);
        }
    };
}



#endif //FILEEMPOWER_COLOR_H