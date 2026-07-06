/*
** EPITECH PROJECT, 2026
** DeliveryDeck.cpp
** File description:
** DeliveryDeck
*/

#include "DeliveryDeck.hpp"

void DeliveryDeck::deliver_pizza_private(std::shared_ptr<PizzaCmd>& pizza_to_deliver)
{
    this->ticket_delivery_pipe << pizza_to_deliver;
}

void  DeliveryDeck::deliver_pizza(std::shared_ptr<PizzaCmd>& pizza_to_deliver)
{
    std::lock_guard<std::mutex> lock(this->delivery_protector);
    deliver_pizza_private(pizza_to_deliver);
}
