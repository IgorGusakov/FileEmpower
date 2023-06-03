//
// Created by Igor Gusakov
//

#include "LogicFEImpl.h"

namespace file_empower {

    void LogicFE::impl::create_logic_fe( )
    {
        logger.Log(ident_file,LogLevel::kInfo,
                    "Enter a command (go \\(backward)/exit/go path(forward)): ");
        while ((getline(std::cin, input_str_data ))) {
            logger.Log(ident_file,LogLevel::kDebug, input_str_data);

            switch (command.get_command(input_str_data)) {
                case commands::EXIT:
                    logger.Log(ident_file,LogLevel::kInfo, "Exit FileEmpower...");
                    exit(0);
                    break ;

                case commands::BACKWARD:
                    backward(input_str_data);
                    break;

                case commands::FORWARD:
                    forward(input_str_data);
                    break ;

                case commands::NONE:
                    break;

                case commands::CREATE:
                    break;

                case commands::CRYPT:
                    break;

                case commands::ENCRYPT:
                    break;
            }
        }
    }

    template <typename T>
    void LogicFE::impl::show_path_data( T&& rhs_param )
    {
        FileSystem fs_file_empower( std::forward<T>(rhs_param) );
        auto files_fm = fs_file_empower.get_data_filesystem();
        //if you want to use different output, so change OutputConsoleFE to need
        if( files_fm.has_value( ) )
        {
            std::unique_ptr<OutputConsoleFE> show_path_ptr = std::make_unique<OutputConsoleFE>(files_fm.value());
            show_path_ptr->draw_data();
            show_path_ptr.reset();
        }
    }

    void LogicFE::impl::backward(const std::string &data)
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
        auto count_s = command.count_back_step(data);

        if(points_symbol_vec.size() > count_s) {
            auto num_of_symbol = points_symbol_vec[ count_s - 1 ];
            path_cur = path_cur.substr(0, num_of_symbol);
        }
        else
            path_cur = "/";

        show_path_data(path_cur);
    }

    void LogicFE::impl::forward(const std::string &data)
    {
        std::string path_new;

        if(data[3] == '/') { //new path
            path_new = data.substr(3);
        }
        else { //continue path
            path_new = path_cur + '/' + data.substr(3);
        }
        FileSystem fs(path_new);

        if( fs.is_valid_path( ) )
            path_cur = path_new;

        logger.Log(ident_file,LogLevel::kInfo,"current path: " + path_cur);
        show_path_data(std::move(fs));
    }

    void LogicFE::start_logic_fe( ) { pImpl->create_logic_fe( ); }
    LogicFE::LogicFE(const std::string& path) : pImpl{std::make_unique<impl>(path)} {}
    LogicFE::LogicFE(LogicFE&&) = default;
    LogicFE::~LogicFE() = default;
    LogicFE& LogicFE::operator=(LogicFE&&) = default;
}// namespace file_empower