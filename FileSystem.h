//
// Created by Igor Gusakov on 07.04.2023.
//

#ifndef FILEEMPOWER_FILESYSTEM_H
#define FILEEMPOWER_FILESYSTEM_H

//#include <string_view>
#include <string>
#include "Data.h"
//#include <boost/filesystem.hpp>
//#include <boost/date_time/posix_time/posix_time.hpp>
//#include <filesystem>
#include "Logger.h"
#include "adapter_fs/FileSystemInterface.h"
#include "adapter_fs/BoostFileSystemAdapter.h"
#include "adapter_fs/StdFileSystemAdapter.h"

namespace file_empower {

//    namespace bfs = boost::filesystem;
//    namespace sfs = std::filesystem;

    class FileSystem {
    public:
        explicit FileSystem( const std::string& path_in ) : path( path_in )
        {
            if (use_boost) {
                mfs = std::make_unique<BoostFileSystemAdapter>();
            } else {
                mfs = std::make_unique<StdFileSystemAdapter>();
            }
            data_fm.set_path(path_in);
//            path_fs.append(path);
        };
//        std::vector<Data> get_data_boost_filesystem();
//        std::vector<Data> get_data_std_filesystem();
        std::vector<Data> get_data_filesystem();

    private:
        std::unique_ptr<FileSystemInterface> mfs;
        bool use_boost = false;
        const std::string path;
        Data data_fm;
//        sfs::path path_fs;
        std::vector<Data> files_fm;
        Logger logger;
        std::string_view ident_file = "FileSystem.cpp";
    };

}// namespace file_empower

#endif//FILEEMPOWER_FILESYSTEM_H
