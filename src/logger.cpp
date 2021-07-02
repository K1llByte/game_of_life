#include <iostream>
#include "logger.hpp"

void Logger::info(const std::string& str)
{
    std::cout << "[INFO]" << str << '\n';
}

void Logger::error(const std::string& str)
{
    std::cout << "[ERROR]" << str << '\n';
}

void Logger::debug(const std::string& str)
{
    std::cout << "[DEBUG]" << str << '\n';
}