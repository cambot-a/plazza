/*
** EPITECH PROJECT, 2026
** OrderPipes.cpp
** File description:
** OrderPipes
*/

#include "OrderPipes.hpp"
#include "epitech_standard_macros.hpp"
#include "plazza_exceptions.hpp"
#include "PacketDeserializer.hpp"

/*
static void copy_order_pipes_contents(OrderPipes& dest, const OrderPipes& origin)
{
    dest.end = origin.end;
    dest.pipe_in = origin.pipe_in;
    dest.pipe_out = origin.pipe_out;
    dest.pipe_to_kitchen[0] = origin.pipe_to_kitchen[0];
    dest.pipe_to_kitchen[1] = origin.pipe_to_kitchen[1];
    dest.pipe_to_reception[0] = origin.pipe_to_reception[0];
    dest.pipe_to_reception[1] = origin.pipe_to_reception[1];
}

OrderPipes::OrderPipes(const OrderPipes& to_copy)
{
    copy_order_pipes_contents(*this, to_copy);
}

OrderPipes& OrderPipes::operator=(const OrderPipes&order_pipes)
{
    copy_order_pipes_contents(*this, order_pipes);
    return *this;
}
*/

OrderPipes::OrderPipes() : end(0), pipe_in(0), pipe_out(0)
{
    if (pipe(pipe_to_kitchen) == FAILURE || pipe(pipe_to_reception) == FAILURE)
        throw KitchenDispatchError("OrderPipes, pipe failed");
}

OrderPipes::~OrderPipes()
{
    close(pipe_in);
    close(pipe_out);
}

void OrderPipes::set_end(int end)
{
    int read_end_to_close = 0;
    int write_end_to_close = 0;

    this->end = end;
    if (end == KITCHEN_ORDER_END) {
        read_end_to_close = pipe_to_reception[0];
        pipe_in = pipe_to_kitchen[0];
        write_end_to_close = pipe_to_kitchen[1];
        pipe_out = pipe_to_reception[1];
    } else if (end == RECEPTION_ORDER_END) {
        read_end_to_close = pipe_to_kitchen[0];
        pipe_in = pipe_to_reception[0];
        write_end_to_close = pipe_to_reception[1];
        pipe_out = pipe_to_kitchen[1];
    } else
        throw UnimplementedFeatureException("undefined set_end");
    close(read_end_to_close);
    close(write_end_to_close);
}

OrderPipes& OrderPipes::operator<<(const std::shared_ptr<ACommandPacket> &data)
{
    std::vector<byte_t> serialized_data = data->serialize();

    write(this->pipe_out, serialized_data.data(), serialized_data.size() * sizeof(byte_t));
    return *this;
}

OrderPipes& OrderPipes::operator>>(std::shared_ptr<ACommandPacket> &data)
{
    PacketHeader header(this->pipe_in);
    std::vector<byte_t> serialized_data = header.serialize();
    byte_t byte_read_bufer;

    for (size_t i = 0; i < header.header.size; ++i) {
        read(this->pipe_in, &byte_read_bufer, sizeof(byte_t));
        serialized_data.push_back(byte_read_bufer);
    }
    PacketDeserializer deserializer(serialized_data);
    data = deserializer.packet;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const OrderPipes &pipes)
{
    os << "OrderPipes {\n";
    os << "  end: " << pipes.end << '\n';
    os << "  pipe_to_kitchen: ["
       << pipes.pipe_to_kitchen[0] << ", "
       << pipes.pipe_to_kitchen[1] << "]\n";
    os << "  pipe_to_reception: ["
       << pipes.pipe_to_reception[0] << ", "
       << pipes.pipe_to_reception[1] << "]\n";
    os << "  pipe_in: " << pipes.pipe_in << '\n';
    os << "  pipe_out: " << pipes.pipe_out << '\n';
    os << "}";
    return os;
}
