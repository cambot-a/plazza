/*
** EPITECH PROJECT, 2026
** pizza_parsers.cpp
** File description:
** pizza_parsers
*/

#include "pizza_data_t.hpp"
#include <cstring>
#include "UnimplementedFeatureException.hpp"
#include <iostream>

pizza_type_t str_to_pizza_type(std::string pizza_type)
{
    for (size_t i = 0; i < (sizeof(pizza_recipes) / sizeof(pizza_data_t)); ++i) {
        if (!std::strcmp(pizza_recipes[i].name, pizza_type.c_str()))
            return pizza_recipes[i].pizza_type;
    }
    throw UnimplementedFeatureException("undefined behaviour in str_to_pizza_type");
}

pizza_size_t str_to_pizza_size(std::string pizza_size)
{
    for (size_t i = 0; i < (sizeof(pizza_size_as_str) / sizeof(char *)); ++i) {
        if (!std::strcmp(pizza_size_as_str[i], pizza_size.c_str()))
            return (pizza_size_t)i;
    }
    throw UnimplementedFeatureException("undefined behaviour in str_to_pizza_size");
}
