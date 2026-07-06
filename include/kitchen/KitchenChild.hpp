/*
** EPITECH PROJECT, 2026
** KitchenChild.hpp
** File description:
** KitchenChild
*/

#ifndef KITCHENCHILD_HPP_
    #define KITCHENCHILD_HPP_
    #include "OrderPipes.hpp"
    #include <vector>
    #include "Cellar.hpp"
    #include "CookWorker.hpp"
    #include "DeliveryDeck.hpp"
    #include "OrderTickets.hpp"
    #include "PizzaSingle.hpp"

class KitchenChild
{
private:
    std::vector<std::unique_ptr<CookWorker>> cooks;
public:
    Cellar cellar;
private:
    size_t nb_cooks;
    OrderPipes packet_manager;
    DeliveryDeck delivery_deck;
    OrderTickets order_tickets;
public:
    size_t multiplier;
    std::string print();
    std::shared_ptr<PizzaSingle> get_pizza_command();
    KitchenChild(size_t nb_cooks, Cellar cellar, size_t multiplier, OrderPipes& packet_manager);
    void start_cooks();
    int execute_command(std::shared_ptr<ACommandPacket>& command);
    int run();
    bool is_exiting() { return this->order_tickets.is_exiting(); }
    ~KitchenChild();
};

#endif /* KITCHENCHILD_HPP_ */