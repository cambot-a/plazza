/*
** EPITECH PROJECT, 2026
** pizza_data_t.hpp
** File description:
** pizza_data_t
*/

#ifndef PIZZA_DATA_T_HPP_
    #define PIZZA_DATA_T_HPP_
    #include <cstddef>
    #include "plazza_utils.hpp"
    #include <regex>
    #include <format>

    #define PIZZA_SIZES_COUNT 5
using pizza_size_t = enum {
    PIZZA_S = 0,
    PIZZA_M = 1,
    PIZZA_L = 2,
    PIZZA_XL = 3,
    PIZZA_XXL = 4,
};

static const char *const pizza_size_as_str[] = {
    "S",
    "M",
    "L",
    "XL",
    "XXL"
};

pizza_size_t str_to_pizza_size(std::string pizza_size);

using ingredients_t = enum : byte_t {
    DOUGH = 255,
    TOMATO = 1,
    GRUYERE = 2,
    HAM = 4,
    MUSHROOMS = 8,
    STEAK = 16,
    EGGPLANT = 32,
    GOAT_CHEESE = 64,
    CHIEF_LOVE = 128
};

    #define PIZZA_TYPES_COUNT 4
using pizza_type_t = enum {
    MARGARITA = 0,
    REGINA = 1,
    AMERICANA = 2,
    FANTASIA = 3,
    NO_PIZZA = 4,
};
pizza_type_t str_to_pizza_type(std::string pizza_type);

using pizza_data_t = struct pizza_data_s {
    const char *name;
    pizza_type_t pizza_type;
    byte_t recipe;
    size_t preparation_time;
};

static const pizza_data_t pizza_recipes[] = {
    {"Margarita", MARGARITA, TOMATO | GRUYERE, 1},
    {"Regina", REGINA, TOMATO | GRUYERE | HAM | MUSHROOMS, 2},
    {"Americana", AMERICANA, TOMATO | GRUYERE | STEAK, 2},
    {"Fantasia", FANTASIA, TOMATO | EGGPLANT | GOAT_CHEESE | CHIEF_LOVE, 4}
};

#define PIZZ_TYPE_RGX_PATTERN std::string("(Margarita|Regina|Americana|Fantasia)")
#define PIZZ_SIZE_RGX_PATTERN std::string("(S|M|L|XL|XXL)")
#define SINGLE_PIZZA_CMD_RGX_PATTERN (PIZZ_TYPE_RGX_PATTERN + " " + PIZZ_SIZE_RGX_PATTERN + " x" + UINT_RGX_PATTERN)

static const std::regex pizza_regex(
    std::format("^{}(; {})*$", SINGLE_PIZZA_CMD_RGX_PATTERN, SINGLE_PIZZA_CMD_RGX_PATTERN));

#endif /* PIZZA_DATA_T_HPP_ */
