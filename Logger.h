//
// Created by Igor Gusakov on 02.04.2023.
//

#ifndef FILEEMPOWER_LOGGER_H
#define FILEEMPOWER_LOGGER_H
#include <iostream>
#include <chrono>
#include <ctime>
#include <string>
#include <concepts>
#include "Color.h"

namespace file_empower {

    enum class LogLevel { kDebug, kInfo, kWarning, kError };

    class Logger {
    public:
        Logger() : output_stream{std::cout} {}

        template<typename T>
        requires std::convertible_to<T, std::string_view>
        void Log(std::string_view identify, LogLevel level, T message) {
            output_stream << "[" << Color::code(Color::Code::FG_GREEN) << identify << Color::reset_fg() << "]" "[" << Timestamp() << "] ";
            switch (level) {
                case LogLevel::kDebug:
                    output_stream << "[DEBUG]   ";
                    break;
                case LogLevel::kInfo:
                    output_stream << "[INFO]    ";
                    break;
                case LogLevel::kWarning:
                    output_stream << "[WARNING] ";
                    break;
                case LogLevel::kError:
                    output_stream << "[ERROR]   ";
                    break;
            }
            output_stream << message << std::endl;
        }

    private:
        std::ostream& output_stream;

        static std::string Timestamp() {
            auto now = std::chrono::system_clock::now();
            auto now_c = std::chrono::system_clock::to_time_t(now);
            std::string timestamp{std::ctime(&now_c)};
            // Remove newline character from timestamp
            timestamp.pop_back();
            return timestamp;
        }
    };
}// namespace file_empower

#endif//FILEEMPOWER_LOGGER_H
