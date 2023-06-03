//
// Created by Igor Gusakov
//

#ifndef FILEEMPOWER_DATA_H
#define FILEEMPOWER_DATA_H

#include <string>
#include <cstdint>
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
        void set_type(const std::string &id, const Color::Code& color) { std::get<0>(type_f) = id; std::get<1>(type_f) = color;};
        std::tuple<std::string, Color::Code> get_type() const {return type_f;};
        [[nodiscard]] size_t get_type_len( ) const { return std::get<0>(type_f).length();};
        //size
        void set_size(uint64_t size_) { size = size_;};
        [[nodiscard]] uint64_t get_size( ) const { return size;};
        [[nodiscard]] size_t get_size_len( ) const { return std::to_string(size).length();};
        //time
        void set_time(const uint64_t time_) { time = time_;};
        [[nodiscard]] std::string get_time( ) const { return std::to_string(time);};
        [[nodiscard]] size_t get_time_len( ) const { return std::to_string(time).length();};
        //permissions
        void set_permissions(std::string_view perm) { permissions = perm;};
        [[nodiscard]] const std::string& get_permissions( ) const { return permissions;};
        [[nodiscard]] size_t get_permissions_len( ) const { return permissions.length();};
        //name file or folder
        void set_name(std::string_view name) { name_object = name;};
        const std::string& get_name( ) const { return name_object;};
        [[nodiscard]] size_t get_name_len( ) const { return name_object.length();};
    private:
        std::string path {"."};
        std::tuple<std::string, file_empower::Color::Code> type_f;// = {std::to_string("Unknown"), Color::Code::BG_RED};
        std::tuple<char, long unsigned int> type_f2;
        uint64_t size{0};
        uint64_t time{0};
        std::string permissions{"---------"};
        std::string name_object {"-"};
    };
}

#endif //FILEEMPOWER_DATA_H