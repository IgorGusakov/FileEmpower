//
// Created by Igor Gusakov
//

#ifndef FILEEMPOWER_LOGICFEIMPL_H
#define FILEEMPOWER_LOGICFEIMPL_H
#include "LogicFE.h"

namespace file_empower {

    class LogicFE::impl
    {
        std::string input_str_data = {};
        Logger logger;
        std::string_view ident_file = "LogicFE.cpp";
        CommandHandler command;
        std::string path_cur;
        void backward(const std::string &data);
        void forward(const std::string &data);
        template <typename T>
        void show_path_data( T &&rhs_param );
    public:
        void create_logic_fe( );
        impl(const std::string& path) : path_cur(path) {
            show_path_data(path);
        }
    };


}// namespace file_empower

#endif//FILEEMPOWER_LOGICFEIMPL_H
