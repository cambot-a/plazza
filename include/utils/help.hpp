/*
** EPITECH PROJECT, 2026
** help.hpp
** File description:
** help
*/

#ifndef HELP_HPP_
    #define HELP_HPP_
    #include <exception>
    #include <string>
    #include <regex>
    
const char *const help_file_path = "./HELP.md";
const std::regex help_regx(std::string("^(-h|--help)$"));

class HelpException : public std::exception {
private:
    const std::string msg;
public:
    HelpException(const std::string msg = "Help failed (parse error) : ") : msg(msg) {};
    inline const char *what(void) const noexcept override { return msg.data(); };
};

void help(void);

#endif /* HELP_HPP_ */
