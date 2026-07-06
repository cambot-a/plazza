/*
** EPITECH PROJECT, 2026
** PizzaSingle.cpp
** File description:
** PizzaSingle
*/

#include "PizzaSingle.hpp"
#include <thread>

void PizzaSingle::cook(byte_t recipe, Cellar& cellar, size_t multiplier)
{
    std::chrono::milliseconds cooking_delay(pizza_recipes[this->pizza_type].preparation_time * 1000 * multiplier);

    cellar.retrieve_ingredients(recipe);
    std::this_thread::sleep_for(cooking_delay);
}

byte_t PizzaSingle::get_recipe()
{
    return pizza_recipes[this->pizza_type].recipe;
}
