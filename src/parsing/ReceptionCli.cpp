/*
** EPITECH PROJECT, 2026
** ReceptionCli.cpp
** File description:
** ReceptionCli
*/

#include "ReceptionCli.hpp"
#include <iostream>
#include <string>
#include "ThreadSafeOstream.hpp"

static void thread_safe_getline(std::string dest)
{
    std::lock_guard<std::mutex> lock(stream_mutex);
    getline(std::cin, dest);
}

void ReceptionCli::get_command_packet(
    std::shared_ptr<ACommandPacket> &command_packet)
{
    ThreadSafeOstream safe_cout(std::cout);

    safe_cout << "$>";
    thread_safe_getline(this->user_in);
    if (this->user_in == "status") {
        command_packet = std::make_shared<StatusCmd>();
    } else if (this->user_in == "exit") {
        command_packet = std::make_shared<ExitCmd>();
    } else
        command_packet = std::make_shared<PizzaCmd>(this->user_in);
}
