#include <iostream>
#include <boost/filesystem.hpp>
#include "Color.h"
#include "Logger.h"
#include "FileSystem.h"
#include "OutputConsoleFE.h"
#include <algorithm>


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
      std::string new_path = current_path;
      if (cmd.find("back",0,4) != std::string::npos) {
          new_path.clear();
          size_t num_of_symbol = 0;
          new_path = "/";
          std::cout << "cmd.find('.',5): " << cmd.find('.',5) << std::endl;
          if( cmd.find('.',5) != std::string::npos ) {
              auto count_s = std::count(cmd.begin(), cmd.end(),'.');
              num_of_symbol = path.size();
              std::cout << "count_s: " << count_s << std::endl;
              std::cout << "cmd.length(): " << num_of_symbol << std::endl;
              for(size_t i = 0; i < count_s; i++) {
                  auto new_num_of_symbol = path.find_last_of('/',num_of_symbol);
                  if(new_num_of_symbol != std::string::npos) {
                      if (!new_num_of_symbol)
                          num_of_symbol = 0;
                      else
                          num_of_symbol = new_num_of_symbol - 1;
                  }
                  else{
                      num_of_symbol = 0;
                      break;
                  }
                  std::cout << "new_num_of_symbol: " << num_of_symbol << std::endl;
              }
          }
          else
              num_of_symbol = path.find_last_of('/');

          std::cout << "Moving backward..." << std::endl;
          std::cout << "num_of_symbol: " << num_of_symbol << std::endl;

//          auto sym = path.find_last_of('/');

//          ///fixme: fix to root
          if (!num_of_symbol)
              new_path = bfs::path(path).root_path().string(); ///todo:boost::filesystem::last_write_time: No such file or directory
          else
              new_path = path.substr(0, ++num_of_symbol);

          std::cout << "new path :" << new_path << std::endl;
          logic_fm(new_path);

      } else if (cmd.find("go",0,2) != std::string::npos) {
          if(cmd.substr(2).size()) {
              new_path.clear();
              if(cmd[3] == '/') { //new path
                  new_path = cmd.substr(3);
              }
              else { //continue path
                  new_path = path + '/' + cmd.substr(3);
              }
              std::cout << "go to folder " << new_path << std::endl;
              logic_fm( new_path );
          }
          else {
              std::cout << "path not specified " <<std::endl;
          }

      } else if (cmd == "exit") {
          std::cout << "Exit FileEmpower..." << std::endl;
          exit(0);
      } else {
          std::cout << "Invalid command" << std::endl;
      }
      std::cout << "Enter a command (back/exit/go): ";
      return new_path;
    };

    std::cout << "Enter a command (back/exit/go): ";
    //loop
    while ((getline(std::cin, input )))
    {
        logger.Log(ident_file,LogLevel::kDebug, input);

        current_path = command_handler(input, current_path);
    }

    return 0;
}