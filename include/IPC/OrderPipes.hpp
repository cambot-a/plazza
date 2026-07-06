/*
** EPITECH PROJECT, 2026
** OrderPipes.hpp
** File description:
** OrderPipes
*/

#ifndef ORDERPIPES_HPP_
    #define ORDERPIPES_HPP_
    #include <thread>
    #include <unistd.h>
    #include "CommandPacket.hpp"

enum {
    KITCHEN_ORDER_END = 0,
    RECEPTION_ORDER_END = 1,
};

class OrderPipes {
public:
    int end;
    int pipe_to_kitchen[2];
    int pipe_to_reception[2];
    int pipe_in;
    int pipe_out;
    OrderPipes();
    ~OrderPipes();

    void set_end(int end);
    OrderPipes &operator<<(const std::shared_ptr<ACommandPacket> &data);
    OrderPipes &operator>>(std::shared_ptr<ACommandPacket> &data);
};

std::ostream &operator<<(std::ostream &os, const OrderPipes &pipes);

#endif /* ORDERPIPES_HPP_ */