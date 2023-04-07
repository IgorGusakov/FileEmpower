//
// Created by Igor Gusakov on 07.04.2023.
//

#ifndef FILEEMPOWER_FILESYSTEM_H
#define FILEEMPOWER_FILESYSTEM_H

#include <string_view>
#include <string>
#include "Data.h"
#include <boost/filesystem.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "Logger.h"

namespace file_empower {

    namespace fs = boost::filesystem;

    class FileSystem {
    public:
        explicit FileSystem( const std::string& path_in ) : path( path_in )
        {
            data_fm.set_path(path_in);
            path_fs.append(path);
        };
        std::vector<Data> get_data_filesystem();

    private:
        std::string_view path;
        Data data_fm;
        fs::path path_fs;
        std::vector<Data> files_fm;
        Logger logger;
        std::string_view ident_file = "FileSystem.cpp";
    };

}// namespace file_empower

#endif//FILEEMPOWER_FILESYSTEM_H
