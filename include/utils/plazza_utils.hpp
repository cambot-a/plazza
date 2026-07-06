/*
** EPITECH PROJECT, 2026
** plazza_utils.hpp
** File description:
** plazza_utils
*/

#ifndef PLAZZA_UTILS_HPP_
    #define PLAZZA_UTILS_HPP_
    #include <string>
    #include <regex>
    #include <format>
    #define UINT_RGX_PATTERN std::string("[1-9][0-9]*")

static const std::regex uint_rgx(std::format("^{}$", UINT_RGX_PATTERN));

using byte_t = unsigned char;

#endif /* PLAZZA_UTILS_HPP_ */