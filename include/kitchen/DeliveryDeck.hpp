/*
** EPITECH PROJECT, 2026
** DeliveryDeck.hpp
** File description:
** DeliveryDeck
*/

#ifndef DELIVERYDECK_HPP_
    #define DELIVERYDECK_HPP_
    #include <mutex>
    #include "CommandPacket.hpp"
    #include "OrderPipes.hpp"

class DeliveryDeck
{
private:
    OrderPipes& ticket_delivery_pipe;
    std::mutex delivery_protector;

    void deliver_pizza_private(std::shared_ptr<PizzaCmd>& pizza_to_deliver);
public:
    DeliveryDeck(OrderPipes& ticket_delivery_pipe)
        : ticket_delivery_pipe(ticket_delivery_pipe), delivery_protector() {}
    ~DeliveryDeck() = default;
    void deliver_pizza(std::shared_ptr<PizzaCmd>& pizza_to_deliver);
};

#endif /* DELIVERYDECK_HPP_ */