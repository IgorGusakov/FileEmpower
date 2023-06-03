//
// Created by Igor Gusakov
//

#ifndef FILEEMPOWER_LOGICFE_H
#define FILEEMPOWER_LOGICFE_H
#include "../output_viewer/OutputConsoleFE.h"
#include "../FileSystem.h"
#include "CommandHandler.h"
#include <experimental/propagate_const>
#include <sstream>

namespace file_empower {

    class LogicFE
    {
        class impl;
        std::experimental::propagate_const<std::unique_ptr<impl>> pImpl;
    public:
        LogicFE() = delete;
        explicit LogicFE( const std::string& path );
        ~LogicFE();
        LogicFE(LogicFE&&);
        LogicFE(const LogicFE&) = delete;
        LogicFE& operator=(LogicFE&&);
        LogicFE& operator=(const LogicFE&) = delete;
        void start_logic_fe( );
    };

}// namespace file_empower

#endif//FILEEMPOWER_LOGICFE_H
