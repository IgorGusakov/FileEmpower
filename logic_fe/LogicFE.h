//
// Created by Igor Gusakov on 08.05.2023.
//

#ifndef FILEEMPOWER_LOGICFE_H
#define FILEEMPOWER_LOGICFE_H
#include "../output_viewer/OutputConsoleFE.h"
#include "../FileSystem.h"
#include "CommandHandler.h"

namespace file_empower {

    class LogicFE {
    public:
        explicit LogicFE( const std::string& path ) : path_cur(path) {
            show_path_data(path_cur);
        };
        void run_logic( );
        void show_path_data( const std::string& path );
    private:
        std::string input_str_data = {};
        Logger logger;
        std::string_view ident_file = "LogicFE.cpp";
        CommandHandler command;
        std::string path_cur;
    };

}// namespace file_empower

#endif//FILEEMPOWER_LOGICFE_H
