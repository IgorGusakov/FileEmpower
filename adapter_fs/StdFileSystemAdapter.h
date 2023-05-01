//
// Created by Igor Gusakov on 26.04.2023.
//

#ifndef FILEEMPOWER_STDFILESYSTEMADAPTER_H
#define FILEEMPOWER_STDFILESYSTEMADAPTER_H

#include "FileSystemInterface.h"
#include <filesystem>
#include <sstream>

namespace file_empower {
    namespace sfs = std::filesystem;
    class StdFileSystemAdapter : public FileSystemInterface {
    public:
        bool exists(const std::string& path) override {
            return sfs::exists(path);
        }

        bool is_directory(const std::string& path) override {
            return sfs::is_directory(path);
        }

        bool is_regular_file(const std::string& path) override {
            return sfs::is_regular_file(path);
        }

        bool is_empty(const std::string& path) override {
            return sfs::is_empty(path);
        }

        std::vector<std::string> directory_iter(const std::string& path) override {
            std::vector<std::string> v;

            for (auto&& x : sfs::directory_iterator(path)) {
                v.emplace_back(x.path());
            }
            return std::move(v);
        }

        const std::string permissions(const std::string& path) override {
            auto perm_ = sfs::status(path).permissions();
            std::ostringstream os_buf;
            auto show = [perm_,&os_buf](char op, sfs::perms perm)
            {
              os_buf << (sfs::perms::none == (perm & perm_) ? '-' : op);
            };
            show('r', sfs::perms::owner_read);
            show('w', sfs::perms::owner_write);
            show('x', sfs::perms::owner_exec);
            show('r', sfs::perms::group_read);
            show('w', sfs::perms::group_write);
            show('x', sfs::perms::group_exec);
            show('r', sfs::perms::others_read);
            show('w', sfs::perms::others_write);
            show('x', sfs::perms::others_exec);
            return std::move(os_buf.str());
        }

        uint64_t last_write_time(const std::string& path) override {
            auto time = sfs::last_write_time(path);
            return std::chrono::duration_cast<std::chrono::seconds>(time.time_since_epoch()).count();
        }

        const std::string get_back_filename(const std::string& path) override {
            return std::move(sfs::path(path).filename().string());
        }

        std::uintmax_t file_size(const std::string& path) override {
            return sfs::file_size(path);
        }
    };
}// namespace file_empower

#endif//FILEEMPOWER_STDFILESYSTEMADAPTER_H
