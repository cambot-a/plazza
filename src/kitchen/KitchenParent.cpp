/*
** EPITECH PROJECT, 2026
** KitchenParent.cpp
** File description:
** KitchenParent
*/

#include "KitchenParent.hpp"
#include "KitchenChild.hpp"
#include <cstdlib>
#include <iostream>
#include <signal.h>
#include "epitech_standard_macros.hpp"
#include "ThreadSafeStringstream.hpp"

std::string KitchenParent::print()
{
    ThreadSafeStringstream result_stream;

    result_stream << "KitchenParent {\n"
        << "  pid: " << this->pid << '\n'
        << "  nb_cooks: " << this->nb_cooks << '\n'
        << "  multiplier: " << this->multiplier << '\n'
        << "  cellar:\n"
        << this->cellar.print() << '\n'
        << "  packet_manager:\n"
        << this->packet_manager << '\n'
        << "}";
    return result_stream.str();
}

KitchenParent::KitchenParent(size_t nb_cooks, size_t multiplier, size_t restock_delay)
    : pid(-1), nb_cooks(nb_cooks), cellar(restock_delay), multiplier(multiplier), packet_manager()
{}

KitchenParent::~KitchenParent()
{
    if (pid == 0)
        return;
    this->packet_manager << std::make_shared<ExitCmd>();
}

int KitchenParent::start(void)
{
    this->pid = fork();
    if (this->pid == 0) {
        this->packet_manager.set_end(KITCHEN_ORDER_END);
        KitchenChild kitchen(nb_cooks, cellar, multiplier, packet_manager);
        kitchen.run();
        return FAILURE;
    } else {
        this->packet_manager.set_end(RECEPTION_ORDER_END);
    }
    return SUCCESS;
}
