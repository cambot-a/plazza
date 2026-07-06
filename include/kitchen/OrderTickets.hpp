/*
** EPITECH PROJECT, 2026
** OrderTickets.hpp
** File description:
** OrderTickets
*/

#ifndef ORDERTICKETS_HPP_
    #define ORDERTICKETS_HPP_
    #include <mutex>
    #include <thread>
    #include <list>
    #include <condition_variable>
    #include "CommandPacket.hpp"
    #include "OrderPipes.hpp"
    #include "PizzaSingle.hpp"

class OrderTickets
{
private:
    std::list<std::shared_ptr<PizzaCmd>> tickets_fifo;
    std::mutex ticket_protector;
    std::condition_variable ticket_refill;
    bool exit_command;

    bool contains_a_ticket_private();
    std::shared_ptr<PizzaSingle> take_next_pizza_private();
    void add_pizza_ticket_private(std::shared_ptr<PizzaCmd> &pizza_ticket);
public:
    void add_pizza_ticket(std::shared_ptr<PizzaCmd> &pizza_ticket);
    OrderTickets()
        : tickets_fifo(), ticket_protector(), ticket_refill(), exit_command(false) {}
    ~OrderTickets();
    bool is_exiting() { return exit_command; }
    bool contains_a_ticket();
    std::shared_ptr<PizzaSingle> take_next_pizza();
};

#endif /* ORDERTICKETS_HPP_ */
