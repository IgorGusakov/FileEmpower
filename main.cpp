#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>
#include "Color.h"
#include "Logger.h"
#include "FileSystem.h"
#include "OutputConsoleFE.h"


using namespace file_empower;

int main() {
    std::string input;
    std::string_view ident_file = "main.cpp";
    Logger logger;
    logger.Log(ident_file,LogLevel::kDebug, "Started File Manager <FileEmpower>");

    auto current_path = boost::filesystem::current_path().string();

    auto logic_fm = [] (const std::string& path)
    {
        FileSystem fs_file_empower(path);
        auto files_fm = std::move(fs_file_empower.get_data_filesystem());

        OutputConsoleFE out_console(files_fm);
        out_console.draw_data_console();
    };

    logic_fm(current_path);

    auto command_handler = [&] (const std::string& cmd, const std::string& path)
    {
        if (cmd == "back") {
            std::cout << "Moving backward..." << std::endl;
            auto sym = path.find_last_of('/');
            std::cout << "sym :"<< sym << std::endl;
            std::string new_path;
            ///todo: fix to root
            if(!sym)
                new_path = "/";
            else
                new_path = path.substr(0,sym);

            std::cout << "new path :"<< new_path << std::endl;
            logic_fm(new_path);
            ///todo: fix double message
            std::cout << "Enter a command (back/exit): ";
            return new_path;
        } else if (cmd == "exit") {
            std::cout << "Exit FileEmpower..." << std::endl;
            exit(0);
        } else {
            std::cout << "Invalid command" << std::endl;
        }
        std::cout << "Enter a command (back/exit): ";
        return current_path;
    };

    std::cout << "Enter a command (back/exit): ";
    //loop
    while ((getline(std::cin, input )))
    {
        logger.Log(ident_file,LogLevel::kDebug, input);

        current_path = command_handler(input, current_path);
    }

    return 0;
}