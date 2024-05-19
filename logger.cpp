//
// Created by ste on 5/19/24.
//

#include "logger.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <filesystem>

namespace saws {

    struct LogMessage {
        LogLevel level;
        std::string message;
    };

    class LoggerImpl {
    public:

        LoggerImpl() {
            std::filesystem::create_directory("logs");
            updateLogFile();
        }

        ~LoggerImpl() {
            if (m_logFile.is_open()) {
                m_logFile.close();
            }
        }

        void Log(LogLevel level, std::string &message) {
            LogMessage logMessage{level, message};
            print(logMessage);
            fflush(stdout);
        }

    private:
        void print(const LogMessage &message) {
            std::string log_level;
            std::string msg;
            switch (message.level) {
                case LogLevel::TRACE:
                    log_level = "[TRACE]:";
                    msg = "\033[37m[TRACE]: " + message.message + '\n' + "\033[0m";
                    break;
                case LogLevel::INFO:
                    log_level = "[INFO]:";
                    msg = "\033[32m[INFO]: " + message.message + '\n' + "\033[0m";
                    break;
                case LogLevel::WARN:
                    log_level = "[WARN]:";
                    msg = "\033[33m[WARN]: " + message.message + '\n' + "\033[0m";
                    break;
                case LogLevel::ERROR:
                    log_level = "[ERROR]:";
                    msg = "\033[31m[ERROR]: " + message.message + '\n' + "\033[0m";
                    break;
                case LogLevel::FATAL:
                    log_level = "[FATAL]:";
                    msg = "\033[35m[FATAL]: " + message.message + '\n' + "\033[0m";
                    break;
                case LogLevel::LDEBUG:
                    log_level = "[DEBUG]:";
                    msg = "\033[36m[DEBUG]: " + message.message + '\n' + "\033[0m"; // Cyan color for Debug
                    break;
            }
            auto now = std::chrono::system_clock::now();
            std::time_t now_c = std::chrono::system_clock::to_time_t(now);
            std::tm now_tm = *std::localtime(&now_c);
            std::stringstream ss;
            ss << std::put_time(&now_tm, "%H:%M:%S");
            std::string time = ss.str() + " | ";
            // Check if the log file needs to be updated
            updateLogFile();

            std::cout << time << msg;
            if (m_logFile.is_open() && message.level != LogLevel::TRACE && message.level != LogLevel::INFO) {
                m_logFile << time << log_level << " " << message.message << std::endl;
            }
            if (message.level == LogLevel::FATAL) {
                exit(EXIT_FAILURE);
            }
        }

        std::ofstream m_logFile;
        std::string m_logFileName = "logs/log.txt";

        void updateLogFile() {
            auto now = std::chrono::system_clock::now();
            std::time_t now_c = std::chrono::system_clock::to_time_t(now);
            std::tm now_tm = *std::localtime(&now_c);

            std::stringstream ss;
            ss << "logs/" << std::put_time(&now_tm, "%Y-%m-%d") << "_log.txt";
            std::string newFileName = ss.str();

            if (m_logFileName != newFileName) {
                m_logFileName = newFileName;
                if (m_logFile.is_open()) {
                    m_logFile.close();
                }
                m_logFile.open(m_logFileName, std::ios::app);
                if (!m_logFile) {
                    std::cerr << "Unable to open log file";
                    exit(1);
                }
                std::filesystem::permissions(m_logFileName,
                                             std::filesystem::perms::owner_all |
                                             std::filesystem::perms::group_read |
                                             std::filesystem::perms::others_read,
                                             std::filesystem::perm_options::add);
            }
        }
    };

    LoggerImpl g_loggerImpl;

    void Logger::log(LogLevel level, std::string message) {
        g_loggerImpl.Log(level, message);
    }

    Logger g_logger;
}  // namespace ether