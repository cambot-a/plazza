/*
** EPITECH PROJECT, 2026
** plazza_exception.hpp
** File description:
** plazza_exception
*/

#ifndef PLAZZA_EXCEPTION_HPP_
    #define PLAZZA_EXCEPTION_HPP_
    #include <exception>
    #include <string>

class PlazzaException : public std::exception {
private:
    const std::string msg;
public:
    PlazzaException(const std::string msg = "plazza : ") : msg(msg) {}
    const char* what() const noexcept override {
        return msg.data();
    }
};

#endif /* PLAZZA_EXCEPTION_HPP_ */
