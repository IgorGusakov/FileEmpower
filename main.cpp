#include <iostream>
#include <vector>
#include "boost/filesystem.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>

class Color {
public:
    enum class Code {
        FG_RED = 31,
        FG_GREEN = 32,
        FG_YELLOW = 33,
        FG_BLUE = 34,
        FG_CYAN = 36,
        FG_DEFAULT = 39,
        BG_RED = 41,
        BG_GREEN = 42,
        BG_YELLOW = 43,
        BG_BLUE = 44,
        BG_DEFAULT = 49
    };

    static std::string code(Code color) {
        return "\033[" + std::to_string(static_cast<int>(color)) + "m";
    }

    static std::string reset() {
        return code(Code::FG_DEFAULT);
    }
};



int main() {
    namespace fs = boost::filesystem;
    namespace pt = boost::posix_time;

    fs::path p(fs::current_path());  // avoid repeated path construction below


    struct Object {
        std::tuple<std::string, Color::Code> Folder {"Folder" , Color::Code::BG_GREEN};
        std::tuple<std::string, Color::Code> File {"File" , Color::Code::BG_YELLOW};
        std::tuple<std::string, Color::Code> Unknown {"Unknown" , Color::Code::BG_RED};
    };

    std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string>> files;
    try
    {
        if (fs::exists(p))
        {
            if (fs::is_regular_file(p))
                std::cout << p << " size is " << file_size(p) << '\n';

            else if (fs::is_directory(p))
            {
                std::cout << p << " is a directory containing:\n";

                std::vector<fs::path> v;

                for (auto&& x : fs::directory_iterator(p))
                    v.push_back(x.path());

                std::sort(v.begin(), v.end());

                for (auto&& x : v)
                {
                    std::string_view type = "Unknown";
                    std::string size = " - ";

                    if(fs::status(x).type() == 2) { //file
                        type = "File";
                        size = std::to_string(fs::file_size(x));
                    }
                    else if(fs::status(x).type() == 3) { //folder
                        type = "Folder";
                    }

                    std::string permissions = std::to_string(fs::status(x).permissions());

                    auto time_t = fs::last_write_time(x);
                    auto utc_t  = boost::posix_time::from_time_t(time_t);
                    std::string last_access_time = to_simple_string(utc_t);

                    std::string filename = x.filename().string();

                    files.emplace_back(permissions, size, last_access_time, type,  filename);
                }
                // Compute column widths
                std::size_t perm_width = 0, size_width = 0, time_width = 0, type_width =0, name_width = 0;
                for (const auto& [perm, size, time, type, name] : files) {
                    perm_width = std::max(perm_width, perm.length());
                    size_width = std::max(size_width, size.length());
                    time_width = std::max(time_width, time.length());
                    type_width = std::max(type_width, type.length());
                    name_width = std::max(name_width, name.length());
                }

                // Output files with column alignment
                for (const auto& [perm, size, time, type, name] : files) {
                    std::cout <<  Color::code(Color::Code::FG_BLUE) << std::left << std::setw(perm_width) << perm << Color::reset() << " | ";
                    std::cout <<  Color::code(Color::Code::FG_CYAN) << std::right << std::setw(size_width) << size << Color::reset() <<  " | ";
                    std::cout << std::left << std::setw(time_width) << time << " | ";
                    std::cout << std::left << std::setw(type_width) << type << " | ";
                    std::cout <<  Color::code(Color::Code::FG_YELLOW) << std::left << std::setw(name_width) << name << Color::reset() << std::endl;
                }
            }
            else
                std::cout << p << " exists, but is not a regular file or directory\n";
        }
        else
            std::cout << p << " does not exist\n";
    }

    catch (const fs::filesystem_error& ex)
    {
        std::cout << ex.what() << '\n';
    }
    return 0;
}
