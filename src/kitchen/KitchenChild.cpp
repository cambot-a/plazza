/*
** EPITECH PROJECT, 2026
** KitchenChild.cpp
** File description:
** KitchenChild
*/

#include "KitchenChild.hpp"
#include "epitech_standard_macros.hpp"
#include "ThreadSafeOstream.hpp"
#include <iostream>
#include <unistd.h>
#include "PizzaSingle.hpp"
#include "ThreadSafeStringstream.hpp"

std::shared_ptr<PizzaSingle> KitchenChild::get_pizza_command()
{
    return this->order_tickets.take_next_pizza();
}

std::string KitchenChild::print()
{
    ThreadSafeStringstream result_stream;

    result_stream << "KitchenChild {\n"
        << "  multiplier: " << this->multiplier << '\n'
        << "  nb_cooks: " << this->nb_cooks << '\n'
        << "  cooks: [\n";
    for (std::unique_ptr<CookWorker>& cook : this->cooks)
        result_stream << cook->print() << "\n";
    result_stream << "]\n"
        << "  cellar:\n"
        << this->cellar.print() << '\n'
        << "  packet_manager:\n"
        << this->packet_manager << '\n'
        << "}";
    return result_stream.str();
}

KitchenChild::KitchenChild(size_t nb_cooks, Cellar cellar, size_t multiplier, OrderPipes& packet_manager)
    : cooks(), cellar(cellar), nb_cooks(nb_cooks),
    packet_manager(packet_manager), delivery_deck(packet_manager),
    order_tickets(), multiplier(multiplier) {}

int KitchenChild::execute_command(std::shared_ptr<ACommandPacket>& command)
{
    if (command->command_type == EXIT_CMD)
        return true;
    this->cellar.update_ingredients_buffer();
    return false;
}

void KitchenChild::start_cooks()
{
    for (size_t i = 0; i < this->nb_cooks; i++)
        cooks.push_back(std::make_unique<CookWorker>(*this));
}

int KitchenChild::run()
{
    ThreadSafeOstream thread_safe_cout(std::cout);

    this->start_cooks();
    for (;;) {
        std::shared_ptr<ACommandPacket> new_command = nullptr;
        this->packet_manager >> new_command;
        command_type_t command_type = new_command->command_type;
        if (command_type == EXIT_CMD) {
            return SUCCESS;
        } else if (command_type == PIZZA_CMD) {
            std::shared_ptr<PizzaCmd> new_pizza_cmd = std::dynamic_pointer_cast<PizzaCmd>(new_command);
            this->order_tickets.add_pizza_ticket(new_pizza_cmd);
        } else if (command_type == STATUS_CMD) {
            thread_safe_cout << this->print() << std::endl;
        } else
            throw UnimplementedFeatureException("unrecognized command received");
    }
    return SUCCESS;
}

KitchenChild::~KitchenChild() {}
