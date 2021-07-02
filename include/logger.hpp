#ifndef LOGGER_HPP
#define LOGGER_HPP

class Logger
{
    public:
        static void info(const std::string&);
        static void error(const std::string&);
        static void debug(const std::string&);
};

#endif // LOGGER_HPP