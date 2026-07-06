/*
** EPITECH PROJECT, 2026
** OrderTickets.cpp
** File description:
** OrderTickets
*/

#include "OrderTickets.hpp"
#include "plazza_constants.hpp"

bool OrderTickets::contains_a_ticket_private()
{
    return (this->tickets_fifo.size() != 0);
}

std::shared_ptr<PizzaSingle> OrderTickets::take_next_pizza_private()
{
    while (this->tickets_fifo.size() > 0) {
        std::shared_ptr<PizzaSingle> pizza_command = this->tickets_fifo.front()->pop_pizza();
        if (pizza_command == nullptr) {
            this->tickets_fifo.pop_front();
        } else {
            return pizza_command;
        }
    }
    return nullptr;
}

void OrderTickets::add_pizza_ticket_private(std::shared_ptr<PizzaCmd>& pizza_ticket)
{
    this->tickets_fifo.push_back(pizza_ticket);
    this->ticket_refill.notify_all();
}

void OrderTickets::add_pizza_ticket(std::shared_ptr<PizzaCmd>& pizza_ticket)
{
    std::lock_guard lock(this->ticket_protector);
    std::shared_ptr<PizzaCmd> pizza_cmd_copy = std::make_shared<PizzaCmd>(*pizza_ticket);
    this->add_pizza_ticket_private(pizza_cmd_copy);
}

bool OrderTickets::contains_a_ticket()
{
    std::lock_guard lock(this->ticket_protector);
    return contains_a_ticket_private();
}

std::shared_ptr<PizzaSingle> OrderTickets::take_next_pizza()
{
    std::shared_ptr<PizzaSingle> extracted_pizza = nullptr;
    std::unique_lock<std::mutex> lock(this->ticket_protector);

    while (extracted_pizza == nullptr) {
        this->ticket_refill.wait(
            lock, [this](){ return (this->exit_command || this->contains_a_ticket_private()); });
        if (exit_command == true)
            return nullptr;
        extracted_pizza = take_next_pizza_private();
        if (extracted_pizza == nullptr)
            std::this_thread::yield();
    }
    lock.unlock();
    return extracted_pizza;
}
/*
        this->ticket_refill.wait_for(
            lock, std::chrono::milliseconds(COOK_THREAD_TIMEOUT - 100),
            [this](){ return this->exit_command || this->contains_a_ticket_private(); });
*/

OrderTickets::~OrderTickets()
{
    {
        std::lock_guard lock(this->ticket_protector);
        exit_command = true;
        ticket_refill.notify_all();
    }
    std::this_thread::sleep_for(cook_thread_timeout);
}
