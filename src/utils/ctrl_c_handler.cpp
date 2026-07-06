/*
** EPITECH PROJECT, 2026
** ctrl_c_handler.cpp
** File description:
** ctrl_c_handler
*/

#include "ctrl_c_handler.hpp"

std::function<void(int)> ctrlc_handler;

void ctrlc_handler_wrapper(int signal)
{
    ctrlc_handler(signal);
}