/*
** EPITECH PROJECT, 2026
** plazza_constants
** File description:
** plazza_constants
*/

#ifndef PLAZZA_CONSTANTS_HPP_
    #define PLAZZA_CONSTANTS_HPP_
    #include <cstddef>
    #include "pizza_data_t.hpp"
    #include <chrono>

static const size_t kitchen_timeout = 5000;
#define COOK_THREAD_TIMEOUT 2500U
static const std::chrono::milliseconds cook_thread_timeout(COOK_THREAD_TIMEOUT);

#endif /* PLAZZA_CONSTANTS_HPP_ */
