//
// Created by ste on 5/19/24.
//

#ifndef NET_SERVER_LOGGER_H
#define NET_SERVER_LOGGER_H

#include <string>
#include <format>

#ifndef __PRETTY_FUNCTION__
#define __PRETTY_FUNCTION__ __func__
#endif

namespace saws {
    enum class LogLevel {
        TRACE,
        INFO,
        WARN,
        ERROR,
        FATAL,
        LDEBUG
    };

    class Logger {
    public:
        static void log(LogLevel level, std::string message);
    };

    extern Logger g_logger;

#define TRACE(...) saws::g_logger.log(saws::LogLevel::TRACE, std::format("Function: {0}, File: {1}, Line: {2}, Message: {3}", __PRETTY_FUNCTION__, __FILE__, __LINE__, std::format(__VA_ARGS__)))
#define INFO(...) saws::g_logger.log(saws::LogLevel::INFO, std::format("Function: {0}, File: {1}, Line: {2}, Message: {3}", __PRETTY_FUNCTION__, __FILE__, __LINE__, std::format(__VA_ARGS__)))
#define WARN(...) saws::g_logger.log(saws::LogLevel::WARN, std::format("Function: {0}, File: {1}, Line: {2}, Message: {3}", __PRETTY_FUNCTION__, __FILE__, __LINE__, std::format(__VA_ARGS__)))
#define ERROR(...) saws::g_logger.log(saws::LogLevel::ERROR, std::format("Function: {0}, File: {1}, Line: {2}, Message: {3}", __PRETTY_FUNCTION__, __FILE__, __LINE__, std::format(__VA_ARGS__)))
#define FATAL(...) saws::g_logger.log(saws::LogLevel::FATAL, std::format("Function: {0}, File: {1}, Line: {2}, Message: {3}", __PRETTY_FUNCTION__, __FILE__, __LINE__, std::format(__VA_ARGS__)))
#ifndef NDEBUG
#define DEBUG(...) saws::g_logger.log(saws::LogLevel::LDEBUG, std::format("Function: {0}, File: {1}, Line: {2}, Message: {3}", __PRETTY_FUNCTION__, __FILE__, __LINE__, std::format(__VA_ARGS__)))
#else
#define DEBUG(...) TRACE(...)
#endif
}


#endif //NET_SERVER_LOGGER_H
