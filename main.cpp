#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "Color.h"
#include "Logger.h"
#include "Data.h"


using namespace file_empower;

int main() {

    namespace fs = boost::filesystem;
    namespace pt = boost::posix_time;

    std::string_view ident_file = "main.cpp";
    Logger logger;

//    logger.Log(ident_file, LogLevel::kDebug, "Debug message");
//    logger.Log(ident_file,LogLevel::kInfo, "Informational message");
//    logger.Log(ident_file,LogLevel::kWarning, "Warning message");
//    logger.Log(ident_file,LogLevel::kError, "Error message");

    Data data_fm;
    data_fm.set_path(fs::current_path().string());

    fs::path p(data_fm.get_path());  // avoid repeated path construction below

    std::vector<Data> files_fm;

    try
    {
        if (fs::exists(p))
        {
            if (fs::is_regular_file(p))
                std::cout << p << " size is " << file_size(p) << '\n';

            else if (fs::is_directory(p))
            {
                logger.Log(ident_file,LogLevel::kInfo, "is a directory containing: " + p.string());

                std::vector<fs::path> v;

                for (auto&& x : fs::directory_iterator(p)) {
                    v.push_back(x.path());
                }


                std::sort(v.begin(), v.end());

                for (auto&& x : v)
                {
                    if(fs::status(x).type() == 2) { //file
                        data_fm.set_type("File", Color::Code::BG_GREEN);
                        data_fm.set_size(fs::file_size(x));
                    }
                    else if(fs::status(x).type() == 3) //folder
                        data_fm.set_type("Folder", Color::Code::BG_YELLOW);

                    data_fm.set_permissions(fs::status(x).permissions());

                    data_fm.set_time(fs::last_write_time(x));

                    data_fm.set_name(x.filename().string());
                    files_fm.emplace_back(data_fm);
                }

                std::size_t perm_width = 0, size_width = 0, time_width = 0, type_width =0, name_width = 0;

                for (const auto& data_fm_ : files_fm) {
                    perm_width = std::max(perm_width, data_fm_.get_permissions_len());
                    size_width = std::max(size_width, data_fm_.get_size_len());
                    time_width = std::max(time_width, data_fm_.get_time_len());
                    type_width = std::max(type_width, data_fm_.get_type_len());
                    name_width = std::max(name_width, data_fm_.get_name_len());
                }
                // Output files with column alignment
                for (Data data_fm_ : files_fm) {
                    std::cout <<  Color::code(Color::Code::FG_BLUE) << std::left << std::setw(perm_width) << data_fm_.get_permissions() << Color::reset_fg() << " | ";
                    std::cout <<  Color::code(Color::Code::FG_CYAN) << std::right << std::setw(size_width) << data_fm_.get_size() << Color::reset_fg() <<  " | ";
                    std::cout << std::left << std::setw(time_width) << data_fm_.get_time() << " | ";
                    std::cout << Color::code(std::get<1>(data_fm_.get_type())) << std::left << std::setw(type_width) << std::get<0>(data_fm_.get_type()) << Color::reset_bg() << " | ";
                    std::cout <<  Color::code(Color::Code::FG_YELLOW) << std::left << std::setw(name_width) << data_fm_.get_name() << Color::reset_fg() << std::endl;
                }
            }
            else
                std::cout << p << " exists, but is not a regular file or directory\n";
        }
        else
            std::cout << p << " does not exist\n";
    }

    catch (const fs::filesystem_error& ex)
    {
        std::cout << ex.what() << '\n';
    }
    return 0;
}