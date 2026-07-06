/*
** EPITECH PROJECT, 2026
** PizzaSingle.hpp
** File description:
** PizzaSingle
*/

#ifndef PIZZASINGLE_HPP_
    #define PIZZASINGLE_HPP_
    #include <unistd.h>
    #include "pizza_data_t.hpp"
    #include "Cellar.hpp"

class PizzaSingle
{
private:
    size_t pizza_type;
    size_t pizza_size;
public:
    friend inline std::ostream &operator<<(std::ostream &s, const PizzaSingle &pizza) {
        return s << "pizza{name :" << pizza_recipes[pizza.pizza_type].name
            << "; size :" << pizza_size_as_str[pizza.pizza_size] << "}";
    }
    PizzaSingle(size_t pizza_type, size_t pizza_size)
        : pizza_type(pizza_type), pizza_size(pizza_size) {}
    void cook(byte_t recipe, Cellar& cellar, size_t multiplier);
    byte_t get_recipe();
};

#endif /* PIZZASINGLE_HPP_ */