/*
** EPITECH PROJECT, 2026
** packet_serialization_data.hpp
** File description:
** packet_serialization_data
*/

#ifndef PACKET_SERIALIZATION_DATA_HPP_
    #define PACKET_SERIALIZATION_DATA_HPP_
    #include "plazza_utils.hpp"
    #include <cstddef>
    #include <vector>

using command_type_t = enum : byte_t {
    EXIT_CMD = 0,
    STATUS_CMD = 1,
    PIZZA_CMD = 2,
};

using packet_header_t = struct packet_header_s {
    size_t size;
    byte_t type;
};

#define PACKET_HEADER_SIZE (sizeof(size_t) + sizeof(byte_t))

class PacketHeader
{
public:
    packet_header_t header;
    PacketHeader(size_t size, command_type_t type);
    PacketHeader(byte_t *serialized_data);
    PacketHeader(int pipe_stream);
    size_t get_size();
    command_type_t get_type();
    std::vector<byte_t> serialize();
};

#endif /* PACKET_SERIALIZATION_DATA_HPP_ */