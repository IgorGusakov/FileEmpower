//
// Created by Igor Gusakov on 07.04.2023.
//

#include "FileSystem.h"

namespace file_empower {

    std::vector<Data> FileSystem::get_data_filesystem() {
        try
        {
            if (mfs->exists(path))
            {
                if (mfs->is_regular_file(path)) {
                    logger.Log(ident_file,LogLevel::kInfo, "size is: " + std::to_string(mfs->file_size(path)));
                    data_fm.set_type("File", Color::Code::BG_GREEN);
                    data_fm.set_size(mfs->file_size(path));
                }
                else if (mfs->is_directory(path))
                {
                    logger.Log(ident_file,LogLevel::kInfo, "is a directory containing: " + path);

                    auto v = mfs->directory_iter(path);
                    std::sort(v.begin(), v.end());

                    for (auto&& x : v)
                    {
                        if(mfs->is_regular_file(x)) {
                            data_fm.set_type("File", Color::Code::BG_GREEN);
                            data_fm.set_size(mfs->file_size(x));
                        }
                        else if(mfs->is_directory(x)) {
                            data_fm.set_type("Folder", Color::Code::BG_YELLOW);
                        }
                        try {
                            data_fm.set_permissions(mfs->permissions(x));
                            data_fm.set_time(mfs->last_write_time(x));
                        } catch (const std::exception& ex) {
                            // catch exception and log error message
                            logger.Log(ident_file,LogLevel::kError, std::string("Unable to get file/directory info: ") + ex.what());
                        }
                        data_fm.set_name(mfs->get_back_filename(x));
                        files_fm.emplace_back(data_fm);
                    }
                }
                else if (mfs->is_empty(path)) {
                    logger.Log(ident_file,LogLevel::kInfo, path + " is empty");
                }
                else
                    logger.Log(ident_file,LogLevel::kWarning, path + " exists, but is not a regular file or directory");
            }
            else
                logger.Log(ident_file,LogLevel::kWarning, path + " does not exist");

            return files_fm;
        }

        catch (const sfs::filesystem_error& ex)
        {
            logger.Log(ident_file,LogLevel::kError, ex.what());
        }
        return {};
    }

}// namespace file_empower