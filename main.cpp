#include "Color.h"
#include "Logger.h"
#include <algorithm>
#include "logic_fe/LogicFE.h"

int main() {
    std::string input;
    std::string_view ident_file = "main.cpp";
    file_empower::Logger logger;
    logger.Log(ident_file,file_empower::LogLevel::kDebug, "Started File Manager <FileEmpower>");

    std::string current_path = getenv("HOME");
    file_empower::LogicFE logic(current_path);

    logic.start_logic_fe();
    return 0;
}