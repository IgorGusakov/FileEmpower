//
// Created by Igor Gusakov
//

#ifndef FILEEMPOWER_FILESYSTEMINTERFACE_H
#define FILEEMPOWER_FILESYSTEMINTERFACE_H

#include <string>
#include <vector>

namespace file_empower {

    class FileSystemInterface {
    public:
        virtual bool exists(const std::string& path) = 0;
        virtual bool is_regular_file(const std::string& path) = 0;
        virtual bool is_directory(const std::string& path) = 0;
        virtual bool is_empty(const std::string& path) = 0;
        virtual std::vector<std::string> directory_iter(const std::string& path) = 0;
        virtual const std::string permissions(const std::string& path) = 0;
        virtual uint64_t last_write_time(const std::string& path) = 0;
        virtual const std::string get_back_filename(const std::string& path) = 0;
        virtual std::uintmax_t file_size(const std::string& path) = 0;
        virtual ~FileSystemInterface() = default;
    };

}// namespace file_empower

#endif//FILEEMPOWER_FILESYSTEMINTERFACE_H
