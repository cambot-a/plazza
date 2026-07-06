/*
** EPITECH PROJECT, 2026
** UnimplementedFeatureException.hpp
** File description:
** UnimplementedFeatureException
*/

#ifndef UNIMPLEMENTEDFEATUREEXCEPTION_HPP_
    #define UNIMPLEMENTEDFEATUREEXCEPTION_HPP_
    #include "PlazzaException.hpp"

class UnimplementedFeatureException  : public PlazzaException {
private:
    const std::string msg;
public:
    UnimplementedFeatureException(const std::string msg = "unimplemented feature : ") : msg(msg) {}
    const char* what() const noexcept override {
        return msg.data();
    }
};

#endif /* UNIMPLEMENTEDFEATUREEXCEPTION_HPP_ */
