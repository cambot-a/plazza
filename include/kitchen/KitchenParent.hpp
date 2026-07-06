/*
** EPITECH PROJECT, 2026
** KitchenParent.hpp
** File description:
** KitchenParent
*/

#ifndef KITCHEN_HPP_
    #define KITCHEN_HPP_
    #include "Cellar.hpp"
    #include "OrderPipes.hpp"
    #include <vector>
    #include <thread>

class KitchenParent
{
public:
    pid_t pid;
    size_t nb_cooks;
    Cellar cellar;
    size_t multiplier;
    OrderPipes packet_manager;
    std::string print();
    KitchenParent(size_t nb_cooks, size_t multiplier, size_t restock_delay);
    ~KitchenParent();
    int start(void);
};

std::ostream &operator<<(std::ostream &os, const KitchenParent &kitchen);

#endif /* KITCHEN_HPP_ */
