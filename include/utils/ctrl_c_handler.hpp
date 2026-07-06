/*
** EPITECH PROJECT, 2026
** ctrl_c_handler.hpp
** File description:
** ctrl_c_handler
*/

#include <functional>

#ifndef CTRL_C_HANDLER_HPP_
    #define CTRL_C_HANDLER_HPP_

extern std::function<void(int)> ctrlc_handler;
void ctrlc_handler_wrapper(int signal);

#endif /* CTRL_C_HANDLER_HPP_ */
