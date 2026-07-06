/*
** EPITECH PROJECT, 2026
** Cellar.hpp
** File description:
** Cellar
*/

#ifndef CELLAR_HPP_
    #define CELLAR_HPP_
    #include <condition_variable>
    #include <chrono>
    #include <semaphore>
    #include "pizza_data_t.hpp"
    #include <stdbool.h>

#define INGREDIENT_VARIETY_COUNT 9

using cellar_time_t = std::chrono::milliseconds::rep;
#define CELLAR_RETRIEVAL_COUNTER_TYPE(var) int var[INGREDIENT_VARIETY_COUNT]

using ingredients_idx_t = enum : size_t {
    TOMATO_IDX = 0,
    GRUYERE_IDX = 1,
    HAM_IDX = 2,
    MUSHROOMS_IDX = 3,
    STEAK_IDX = 4,
    EGGPLANT_IDX = 5,
    GOAT_CHEESE_IDX = 6,
    CHIEF_LOVE_IDX = 7,
    DOUGH_IDX = 8,
};

static const ingredients_t ingredients_reftable[] = {
    TOMATO,
    GRUYERE,
    HAM,
    MUSHROOMS,
    STEAK,
    EGGPLANT,
    GOAT_CHEESE,
    CHIEF_LOVE,
    DOUGH,
};

class Cellar {
private:
    size_t restock_delay;
    cellar_time_t init_time;
    CELLAR_RETRIEVAL_COUNTER_TYPE(retrieval);
    CELLAR_RETRIEVAL_COUNTER_TYPE(ingredients_buffer);
    std::mutex ingredient_mutex;
    std::condition_variable cond_variable;
    std::string private_print();
    void private_update_ingredients_buffer();
    bool private_has_ingredients(byte_t recipe);
    void private_retrieve_ingredients(byte_t recipe);
public:
    Cellar(const Cellar& to_copy);
    Cellar(size_t restock_delay);
    std::string print();
    void update_ingredients_buffer();
    bool has_ingredients(byte_t recipe);
    void retrieve_ingredients(byte_t recipe);
};

#define DEFAULT_INGREDIENTS_COUNT 5

#endif /* CELLAR_HPP_ */
