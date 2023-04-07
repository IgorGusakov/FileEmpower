//
// Created by Igor Gusakov on 02.04.2023.
//

#ifndef FILEEMPOWER_DATA_H
#define FILEEMPOWER_DATA_H

#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "Color.h"

namespace file_empower {
    class Data {
    public:
        explicit Data() = default;
        //path
        void set_path(const std::string &p) { path = p;};
        const std::string& get_path( ) { return path;};
        [[nodiscard]] size_t get_path_len( ) const { return path.length();};
        //type
        void set_type(const std::string &id, const Color::Code& color) { std::get<0>(type) = id; std::get<1>(type) = color;};
        std::tuple<std::string, Color::Code> get_type() {return type;};
        [[nodiscard]] size_t get_type_len( ) const { return std::get<0>(type).length();};
        //size
        void set_size(uint64_t size_) { size = size_;};
        [[nodiscard]] uint64_t get_size( ) const { return size;};
        [[nodiscard]] size_t get_size_len( ) const { return std::to_string(size).length();};
        //time
        void set_time(const time_t& time_) { time = time_;};
        [[nodiscard]] std::string get_time( ) const { return to_simple_string(boost::posix_time::from_time_t(time));};
        [[nodiscard]] size_t get_time_len( ) const { return to_simple_string(boost::posix_time::from_time_t(time)).length();};
        //permissions
        void set_permissions(int perm) { permissions = perm;};
        [[nodiscard]] int get_permissions( ) const { return permissions;};
        [[nodiscard]] size_t get_permissions_len( ) const { return std::to_string(permissions).length();};
        //name file or folder
        void set_name(const std::string &name) { name_object = name;};
        const std::string& get_name( ) { return name_object;};
        [[nodiscard]] size_t get_name_len( ) const { return name_object.length();};
    private:
        std::string path {"."};
        std::tuple<std::string, Color::Code> type = {"Unknown", Color::Code::BG_RED};
        uint64_t size{0};
        time_t time{0};
        int permissions{0};
        std::string name_object {"-"};
    };
}

#endif //FILEEMPOWER_DATA_H