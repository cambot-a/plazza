/*
** EPITECH PROJECT, 2026
** Pizzeria.hpp
** File description:
** Pizzeria
*/

#ifndef PIZZERIA_HPP_
    #define PIZZERIA_HPP_
    #include "KitchenParent.hpp"
    #include "PlazzaException.hpp"
    #define DEFAULT_ARGUMENT_COUNT 3
    #include "ReceptionCli.hpp"
    #include "KitchenPool.hpp"

class Pizzeria
{
private:
    size_t multiplier;
    size_t nb_cooks;
    size_t restock_delay;
    ReceptionCli reception_cli;
    std::unique_ptr<KitchenPool> kitchens;
    std::atomic<bool> exit_flag;

    friend void plazza_parse_program_args(int ac, char **av, Pizzeria& pizzeria);
public:
    bool is_running();
    void pizzeria_manual_destroy();
    Pizzeria(int ac, char **av);
    ~Pizzeria();
    int run(void);
};

#endif /* PIZZERIA_HPP_ */