//
// Created by Igor Gusakov
//

#ifndef FILEEMPOWER_OUTPUTCONSOLEFE_H
#define FILEEMPOWER_OUTPUTCONSOLEFE_H
#include "../Data.h"
#include "../Logger.h"
#include <vector>
#include "OutputCRTPViewer.h"
#include <iomanip>

namespace file_empower {

    class OutputConsoleFE : public OutputCRTPViewer<OutputConsoleFE> {
    public:
        explicit OutputConsoleFE( const std::vector<Data>& Data ) : files_fm( Data ) { };
        OutputConsoleFE() = delete;
        void draw_data() {
            auto calc_max_width = [&] () -> WidthData {
                WidthData data_width;
                for (const auto& data_fm_ : files_fm)
                {
                    data_width.perm_width = std::max(data_width.perm_width, data_fm_.get_permissions_len());
                    data_width.size_width = std::max(data_width.size_width, data_fm_.get_size_len());
                    data_width.time_width = std::max(data_width.time_width, data_fm_.get_time_len());
                    data_width.type_width = std::max(data_width.type_width, data_fm_.get_type_len());
                    data_width.name_width = std::max(data_width.name_width, data_fm_.get_name_len());
                }
                return data_width;
            };

            auto data_w = calc_max_width();
            for (Data data_fm_ : files_fm) {
                std::cout <<  Color::code(Color::Code::FG_BLUE) << std::left << std::setw(static_cast<int>(data_w.perm_width)) << data_fm_.get_permissions() << Color::reset_fg() << " | ";
                std::cout <<  Color::code(Color::Code::FG_CYAN) << std::right << std::setw(static_cast<int>(data_w.size_width)) << data_fm_.get_size() << Color::reset_fg() <<  " | ";
                std::cout << std::left << std::setw(static_cast<int>(data_w.time_width)) << data_fm_.get_time() << " | ";
                std::cout << Color::code(std::get<1>(data_fm_.get_type())) << std::left << std::setw(static_cast<int>(data_w.type_width)) << std::get<0>(data_fm_.get_type()) << Color::reset_bg() << " | ";
                std::cout <<  Color::code(Color::Code::FG_YELLOW) << std::left << std::setw(static_cast<int>(data_w.name_width)) << data_fm_.get_name() << Color::reset_fg() << std::endl;
            }
        };

    private:
        std::vector<Data> files_fm;
        struct WidthData {
            std::size_t perm_width = 0;
            std::size_t size_width = 0;
            std::size_t time_width = 0;
            std::size_t type_width = 0;
            std::size_t name_width = 0;
        };
        std::string_view ident_file = "OutputConsoleFE.cpp";
        Logger logger;
    };

} // file_empower

#endif//FILEEMPOWER_OUTPUTCONSOLEFE_H