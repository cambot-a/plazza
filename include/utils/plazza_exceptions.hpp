/*
** EPITECH PROJECT, 2026
** plazza_exceptions.hpp
** File description:
** plazza_exceptions
*/

#ifndef PLAZZA_EXCEPTIONS_HPP_
    #define PLAZZA_EXCEPTIONS_HPP_
    #include "PlazzaException.hpp"

class ParsingError : public PlazzaException {
private:
    const std::string msg;
public:
    ParsingError(const std::string msg = "parse error : ") : msg(msg) {}
    ~ParsingError() = default;
    const char* what() const noexcept override {
        return msg.data();
    }
};

class CLIerror : public PlazzaException {
private:
    const std::string msg;
public:
    CLIerror(const std::string msg = "CLI error : ") : msg(msg) {}
    ~CLIerror() = default;
    const char* what() const noexcept override {
        return msg.data();
    }
};

class KitchenDispatchError : public PlazzaException {
private:
    const std::string msg;
public:
    KitchenDispatchError(const std::string msg = "kitchen dispatch error : ") : msg(msg) {}
    ~KitchenDispatchError() = default;
    const char* what() const noexcept override {
        return msg.data();
    }
};

#endif /* PLAZZA_EXCEPTIONS_HPP_ */
