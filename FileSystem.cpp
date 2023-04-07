//
// Created by Igor Gusakov on 07.04.2023.
//

#include "FileSystem.h"

namespace file_empower {

    std::vector<Data> FileSystem::get_data_filesystem() {
        try
        {
            if (fs::exists(path_fs))
            {
                if (fs::is_regular_file(path_fs))
                    logger.Log(ident_file,LogLevel::kInfo, "size is: " + std::to_string(file_size(path_fs)));

                else if (fs::is_directory(path_fs))
                {
                    logger.Log(ident_file,LogLevel::kInfo, "is a directory containing: " + path_fs.string());

                    std::vector<fs::path> v;

                    for (auto&& x : fs::directory_iterator(path_fs)) {
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
                }
                else
                    logger.Log(ident_file,LogLevel::kWarning, path_fs.string() + " exists, but is not a regular file or directory");
            }
            else
                logger.Log(ident_file,LogLevel::kWarning, path_fs.string() + " does not exist");

            return files_fm;
        }

        catch (const fs::filesystem_error& ex)
        {
            logger.Log(ident_file,LogLevel::kError, ex.what());
        }
        return {};
    }

}// namespace file_empower