/*
** EPITECH PROJECT, 2026
** PacketDeserializer.hpp
** File description:
** PacketDeserializer
*/

#ifndef PACKETDESERIALIZER_HPP_
    #define PACKETDESERIALIZER_HPP_
    #include "CommandPacket.hpp"

class PacketDeserializer
{
public:
    std::shared_ptr<ACommandPacket>packet;
    PacketDeserializer(std::vector<byte_t>& serialized_data);
};

#endif /* PACKETDESERIALIZER_HPP_ */