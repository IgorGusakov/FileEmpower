//
// Created by Igor Gusakov on 02.04.2023.
//

#include "OutputConsoleFE.h"

namespace file_empower {

    void OutputConsoleFE::calc_max_width()
    {
        for (const auto& data_fm_ : files_fm)
        {
            data_width.perm_width = std::max(data_width.perm_width, data_fm_.get_permissions_len());
            data_width.perm_width = std::max(data_width.size_width, data_fm_.get_size_len());
            data_width.time_width = std::max(data_width.time_width, data_fm_.get_time_len());
            data_width.type_width = std::max(data_width.type_width, data_fm_.get_type_len());
            data_width.name_width = std::max(data_width.name_width, data_fm_.get_name_len());
        }
    }

     void OutputConsoleFE::draw_data_console()
    {
        for (Data data_fm_ : files_fm) {
            std::cout <<  Color::code(Color::Code::FG_BLUE) << std::left << std::setw(static_cast<int>(data_width.perm_width)) << data_fm_.get_permissions() << Color::reset_fg() << " | ";
            std::cout <<  Color::code(Color::Code::FG_CYAN) << std::right << std::setw(static_cast<int>(data_width.size_width)) << data_fm_.get_size() << Color::reset_fg() <<  " | ";
            std::cout << std::left << std::setw(static_cast<int>(data_width.time_width)) << data_fm_.get_time() << " | ";
            std::cout << Color::code(std::get<1>(data_fm_.get_type())) << std::left << std::setw(static_cast<int>(data_width.type_width)) << std::get<0>(data_fm_.get_type()) << Color::reset_bg() << " | ";
            std::cout <<  Color::code(Color::Code::FG_YELLOW) << std::left << std::setw(static_cast<int>(data_width.name_width)) << data_fm_.get_name() << Color::reset_fg() << std::endl;
        }
    }

} // file_empower