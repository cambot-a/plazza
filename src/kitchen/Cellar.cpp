/*
** EPITECH PROJECT, 2026
** Cellar.cpp
** File description:
** Cellar
*/

#include "Cellar.hpp"
#include "UnimplementedFeatureException.hpp"
#include "epitech_standard_macros.hpp"
#include <chrono>
#include <iostream>
#include "ThreadSafeOstream.hpp"
#include "ThreadSafeStringstream.hpp"

static cellar_time_t get_time_since_epoch()
{
    auto clock_since_epoch = std::chrono::system_clock::now().time_since_epoch();
    auto time_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(clock_since_epoch);

    return time_since_epoch.count();
}

void Cellar::private_update_ingredients_buffer()
{
    cellar_time_t current_time = get_time_since_epoch();
    size_t ingredients_added_since_creation = (current_time - this->init_time) / this->restock_delay;

    for (size_t i = 0; i < INGREDIENT_VARIETY_COUNT; ++i) {
        if ((int)ingredients_added_since_creation + this->retrieval[i] < 0)
            throw UnimplementedFeatureException("ingredient contents negative");
        this->ingredients_buffer[i] = ingredients_added_since_creation + this->retrieval[i];
    }

}

void Cellar::update_ingredients_buffer()
{
    std::lock_guard<std::mutex> lock(ingredient_mutex);
    this->private_update_ingredients_buffer();
}

std::string Cellar::private_print()
{
    ThreadSafeStringstream result_stream;

    result_stream << "Cellar {\n"
        << "    restock_delay: " << this->restock_delay << ",\n"
        << "    TOMATO; GRUYERE; HAM; MUSHROOMS; STEAK; EGGPLANT; GOAT_CHEESE; CHIEF_LOVE; DOUGH\n"
        << "    ingredients_buffer: ";
    for (size_t i = 0; i < INGREDIENT_VARIETY_COUNT; ++i)
        result_stream << this->ingredients_buffer[i] << "; ";
    result_stream << ",\n"
        << "}";
    return result_stream.str();
}

std::string Cellar::print()
{
    std::unique_lock<std::mutex> lock(ingredient_mutex);
    return private_print();
}

Cellar::Cellar(size_t restock_delay)
    : restock_delay(restock_delay), init_time(0), ingredient_mutex(), cond_variable()
{
    for (size_t i = 0; i < INGREDIENT_VARIETY_COUNT; ++i) {
        retrieval[i] = (int)(DEFAULT_INGREDIENTS_COUNT);
        this->ingredients_buffer[i] = (size_t)DEFAULT_INGREDIENTS_COUNT;
    }
    init_time = get_time_since_epoch();
    private_update_ingredients_buffer();
}

bool Cellar::private_has_ingredients(byte_t recipe)
{
    private_update_ingredients_buffer();
    for (size_t i = 0; i < INGREDIENT_VARIETY_COUNT - 1; ++i) {
        if ((ingredients_reftable[i] & recipe) == false)
            continue;
        if (ingredients_buffer[i] == 0)
            return false;
    }
    return true;
}

bool Cellar::has_ingredients(byte_t recipe)
{
    std::lock_guard<std::mutex> lock(ingredient_mutex);
    return private_has_ingredients(recipe);
}

void Cellar::private_retrieve_ingredients(byte_t recipe)
{
    for (size_t i = 0; i < INGREDIENT_VARIETY_COUNT; ++i) {
        if (i == DOUGH_IDX)
            continue;
        if ((ingredients_reftable[i] & recipe) == false)
            continue;
        if (ingredients_buffer[i] == 0)
            throw UnimplementedFeatureException("trying to retrieve emtpy resource");
        retrieval[i] -= 1;
    }
}

void Cellar::retrieve_ingredients(byte_t recipe)
{
    std::unique_lock<std::mutex> lock(ingredient_mutex);
    cond_variable.wait_for(
        lock, std::chrono::milliseconds(this->restock_delay),
        [this, recipe](){ return this->private_has_ingredients(recipe); });
    private_retrieve_ingredients(recipe);
    lock.unlock();
}

Cellar::Cellar(const Cellar& to_copy) : Cellar(to_copy.restock_delay) {}
