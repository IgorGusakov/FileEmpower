//
// Created by Igor Gusakov on 02.04.2023.
//

#ifndef FILEEMPOWER_OUTPUTCONSOLEFE_H
#define FILEEMPOWER_OUTPUTCONSOLEFE_H
#include "Data.h"

namespace file_empower {

    class OutputConsoleFE {
    public:
        explicit OutputConsoleFE( const std::vector<Data>& Data ) : files_fm( Data ) { };
        OutputConsoleFE() = delete;
        void draw_data_console();

    private:
        std::vector<Data> files_fm;
        struct WidthData {
            std::size_t perm_width = 0;
            std::size_t size_width = 0;
            std::size_t time_width = 0;
            std::size_t type_width = 0;
            std::size_t name_width = 0;
        };
        WidthData data_width;
        void calc_max_width();
    };

} // file_empower

#endif//FILEEMPOWER_OUTPUTCONSOLEFE_H