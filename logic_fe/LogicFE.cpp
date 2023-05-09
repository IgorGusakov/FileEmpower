//
// Created by Igor Gusakov on 08.05.2023.
//

#include "LogicFE.h"

namespace file_empower {

    void LogicFE::run_logic( )
    {
        std::cout << "Enter a command (back/exit/go): ";
        while ((getline(std::cin, input_str_data ))) {
            logger.Log(ident_file,LogLevel::kDebug, input_str_data);

            switch (command.get_command(input_str_data)) {
                case commands::EXIT:
                    std::cout << "Exit FileEmpower..." << std::endl;
                    exit(0);
                    break ;

                case commands::BACK:
                {
                    auto new_num_of_symbol = path_cur.find_last_of('/');
                    auto count_s = command.count_back_step(path_cur);
                    if(new_num_of_symbol > count_s) {
                        auto num_of_symbol = path_cur.size();
                        for(size_t i = 0; i < count_s; i++) {
                            num_of_symbol = path_cur.find_last_of('/', num_of_symbol);
                        }
                        path_cur = path_cur.substr(0, ++num_of_symbol);
                    }
                    else
                        path_cur = "/";

                    show_path_data(path_cur);
                    break;
                }
                case commands::GO:

                    break ;

            }
        }
    }


    void LogicFE::show_path_data(const std::string &path)
    {
        FileSystem fs_file_empower(path);
        auto files_fm = std::move(fs_file_empower.get_data_filesystem());
        //if you want to use different output, so change OutputConsoleFE to need
        std::unique_ptr<OutputConsoleFE> show_path_ptr = std::make_unique<OutputConsoleFE>(files_fm);
        show_path_ptr.get()->draw_data();
        show_path_ptr.reset();
    }

}// namespace file_empower