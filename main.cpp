#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "Color.h"
#include "Logger.h"
#include "Data.h"
#include "FileSystem.h"
#include "OutputConsoleFE.h"


using namespace file_empower;

int main() {

    std::string_view ident_file = "main.cpp";
    Logger logger;
    logger.Log(ident_file,LogLevel::kDebug, "Started File Manager <FileEmpower>");
    FileSystem fs_file_empower(boost::filesystem::current_path().string());

//    std::size_t perm_width = 0, size_width = 0, time_width = 0, type_width =0, name_width = 0;
    auto files_fm = std::move(fs_file_empower.get_data_filesystem());
    OutputConsoleFE out_console(files_fm);
    out_console.draw_data_console();

    return 0;
}