/*
** EPITECH PROJECT, 2026
** PacketDeserializer.cpp
** File description:
** PacketDeserializer
*/

#include "PacketDeserializer.hpp"

PacketDeserializer::PacketDeserializer(std::vector<byte_t>& serialized_data)
{
    PacketHeader header(serialized_data.data());

    switch (header.get_type())
    {
    case STATUS_CMD:
        this->packet = std::make_shared<StatusCmd>(serialized_data);
        break;
    case EXIT_CMD:
        this->packet = std::make_shared<ExitCmd>(serialized_data);
        break;
    case PIZZA_CMD:
        this->packet = std::make_shared<PizzaCmd>(serialized_data);
        break;
    default:
        throw UnimplementedFeatureException("unrecognized command");
    }
}