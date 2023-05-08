//
// Created by Igor Gusakov on 07.04.2023.
//

#ifndef FILEEMPOWER_FILESYSTEM_H
#define FILEEMPOWER_FILESYSTEM_H

#include <string>
#include <vector>
#include "Data.h"
#include "Logger.h"
#include "adapter_fs/FileSystemInterface.h"
#include "adapter_fs/BoostFileSystemAdapter.h"
#include "adapter_fs/StdFileSystemAdapter.h"

namespace file_empower {
    class FileSystem {
    public:
        explicit FileSystem( const std::string& path_in ) : path( path_in )
        {
#ifdef BOOST_LIB
                mfs = std::make_unique<BoostFileSystemAdapter>();
                logger.Log(ident_file,LogLevel::kInfo, "We are using boost::filesystems");
#else
                mfs = std::make_unique<StdFileSystemAdapter>();
                logger.Log(ident_file,LogLevel::kInfo, "We are using std::filesystems");
#endif
            data_fm.set_path(path_in);
        };
        std::vector<Data> get_data_filesystem();

    private:
        std::unique_ptr<FileSystemInterface> mfs;
        const std::string path;
        Data data_fm;
        std::vector<Data> files_fm;
        Logger logger;
        std::string_view ident_file = "FileSystem.cpp";
    };

}// namespace file_empower

#endif//FILEEMPOWER_FILESYSTEM_H
