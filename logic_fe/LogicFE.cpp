//
// Created by Igor Gusakov on 08.05.2023.
//

#include "LogicFE.h"
#include <sstream>

namespace file_empower {

    void LogicFE::run_logic( )
    {
        std::cout << "Enter a command (go \\(backward)/exit/go path(forward)): ";
        while ((getline(std::cin, input_str_data ))) {
            logger.Log(ident_file,LogLevel::kDebug, input_str_data);

            switch (command.get_command(input_str_data)) {
                case commands::EXIT:
                    std::cout << "Exit FileEmpower..." << std::endl;
                    exit(0);
                    break ;

                case commands::BACKWARD:
                {
                    auto arr_of_symbol = [&](std:: vector<uint16_t> &vec)  {
                      uint64_t lastIndex = path_cur.size( );
                      while ( lastIndex != std::string::npos && lastIndex != 0) {
                          uint16_t prevIndex = lastIndex;
                          lastIndex = path_cur.find_last_of('/', prevIndex - 1);
                          if (lastIndex != std::string::npos) {
                              vec.emplace_back(static_cast<uint16_t>(lastIndex));
                          }
                      }
                    };

                    std::vector<uint16_t> points_symbol_vec;
                    arr_of_symbol(points_symbol_vec);
//                    for(uint16_t n : points_symbol_vec) {
//                        logger.Log(ident_file,LogLevel::kDebug, "n " + std::to_string(n));
//                    }
                    auto count_s = command.count_back_step(input_str_data);
//                    logger.Log(ident_file,LogLevel::kDebug, path_cur);
//                    logger.Log(ident_file,LogLevel::kDebug, "all symbol / " + std::to_string(points_symbol_vec.size()));
//                    logger.Log(ident_file,LogLevel::kDebug, "back count" + std::to_string(count_s));

                    if(points_symbol_vec.size() > count_s) {
                        auto num_of_symbol = points_symbol_vec[ count_s - 1 ];
//                        logger.Log(ident_file,LogLevel::kDebug, "num_of_symbol" + std::to_string(num_of_symbol));
                        path_cur = path_cur.substr(0, num_of_symbol);
                    }
                    else
                        path_cur = "/";

                    show_path_data(path_cur);
                    break;
                }
                case commands::FORWARD:
                    if(input_str_data[3] == '/') { //new path
                        path_cur = input_str_data.substr(3);
                    }
                    else { //continue path
                        path_cur = path_cur + '/' + input_str_data.substr(3);
                    }
                    std::cout << "go to folder " << path_cur << std::endl;
                    show_path_data( path_cur );
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