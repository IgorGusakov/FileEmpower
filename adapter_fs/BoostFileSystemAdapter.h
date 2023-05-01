//
// Created by Igor Gusakov on 26.04.2023.
//

#ifndef FILEEMPOWER_BOOSTFILESYSTEMADAPTER_H
#define FILEEMPOWER_BOOSTFILESYSTEMADAPTER_H
#include <boost/filesystem.hpp>
#include "FileSystemInterface.h"
#include <sstream>

namespace file_empower {
    namespace bfs = boost::filesystem;
    class BoostFileSystemAdapter : public FileSystemInterface {
    public:
        bool exists(const std::string& path) override {
            return bfs::exists(path);
        }

        bool is_directory(const std::string& path) override {
            return bfs::is_directory(path);
        }

        bool is_regular_file(const std::string& path) override {
            return bfs::is_regular_file(path);
        }

        std::vector<std::string> directory_iter(const std::string& path) override {
            std::vector<std::string> v;

            for (auto&& x : bfs::directory_iterator(path)) {
                v.emplace_back(x.path().string());
            }
            return std::move(v);
        }

        const std::string permissions(const std::string& path) override {
            auto perm_ = bfs::status(path).permissions();
            std::ostringstream os_buf;
            auto show = [=,&os_buf](char op, bfs::perms perm)
            {
              os_buf << (bfs::perms::no_perms == (perm & perm_) ? '-' : op);
            };
            show('r', bfs::perms::owner_read);
            show('w', bfs::perms::owner_write);
            show('x', bfs::perms::owner_exe);
            show('r', bfs::perms::group_read);
            show('w', bfs::perms::group_write);
            show('x', bfs::perms::group_exe);
            show('r', bfs::perms::others_read);
            show('w', bfs::perms::others_write);
            show('x', bfs::perms::others_exe);
            return std::move(os_buf.str());
        }

        uint64_t last_write_time(const std::string& path) override {
            return bfs::last_write_time(path);
        }

        const std::string get_back_filename(const std::string& path) override {
                return std::move(bfs::path(path).filename().string());
        }

        std::uintmax_t file_size(const std::string& path) override {
            return bfs::file_size(path);
        }
    };

}// namespace file_empower

#endif//FILEEMPOWER_BOOSTFILESYSTEMADAPTER_H
