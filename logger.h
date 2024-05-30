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
        ERR,
        FATAL,
        LDEBUG
    };

    class Logger {
    public:
        static bool silent;

        static void log(LogLevel level, std::string message);

        Logger() {
            silent = false;
        }
    };

    extern Logger g_logger;

#define LTRACE(...) saws::g_logger.log(saws::LogLevel::TRACE, std::format("Function: {0}, File: {1}, Line: {2}, Message: {3}", __PRETTY_FUNCTION__, __FILE__, __LINE__, std::format(__VA_ARGS__)))
#define LINFO(...) saws::g_logger.log(saws::LogLevel::INFO, std::format("Function: {0}, File: {1}, Line: {2}, Message: {3}", __PRETTY_FUNCTION__, __FILE__, __LINE__, std::format(__VA_ARGS__)))
#define LWARN(...) saws::g_logger.log(saws::LogLevel::WARN, std::format("Function: {0}, File: {1}, Line: {2}, Message: {3}", __PRETTY_FUNCTION__, __FILE__, __LINE__, std::format(__VA_ARGS__)))
#define LERROR(...) saws::g_logger.log(saws::LogLevel::ERR, std::format("Function: {0}, File: {1}, Line: {2}, Message: {3}", __PRETTY_FUNCTION__, __FILE__, __LINE__, std::format(__VA_ARGS__)))
#define LFATAL(...) saws::g_logger.log(saws::LogLevel::FATAL, std::format("Function: {0}, File: {1}, Line: {2}, Message: {3}", __PRETTY_FUNCTION__, __FILE__, __LINE__, std::format(__VA_ARGS__)))
#ifndef NDEBUG
#define LDEBUG(...) saws::g_logger.log(saws::LogLevel::LDEBUG, std::format("Function: {0}, File: {1}, Line: {2}, Message: {3}", __PRETTY_FUNCTION__, __FILE__, __LINE__, std::format(__VA_ARGS__)))
#else
#define LDEBUG(...) LTRACE(...)
#endif
}


#endif //NET_SERVER_LOGGER_H
