/*
** EPITECH PROJECT, 2026
** PacketHeader.cpp
** File description:
** PacketHeader
*/

#include "packet_serialization_data.hpp"
#include <cstddef>
#include <vector>
#include <cstring>
#include <unistd.h>
#include "epitech_standard_macros.hpp"
#include "plazza_exceptions.hpp"
#include <format>
#include <iostream>

PacketHeader::PacketHeader(size_t size, command_type_t type)
    : header((packet_header_t){size, (byte_t)type}) {}

PacketHeader::PacketHeader(byte_t *serialized_data)
{
    memcpy(&(this->header), serialized_data, PACKET_HEADER_SIZE);
}

PacketHeader::PacketHeader(int pipe_fd)
{
    if (read(pipe_fd, &(this->header), PACKET_HEADER_SIZE) == FAILURE) {
        perror("reading error");
        throw KitchenDispatchError(std::format("could not read from pipe {}", pipe_fd));
    }
}

std::vector<byte_t> PacketHeader::serialize()
{
    std::vector<byte_t> data = {};
    byte_t *header_bytes = reinterpret_cast<byte_t *>(&(this->header.size));

    for (size_t i = 0; i < sizeof(size_t); ++i)
        data.push_back(header_bytes[i]);
    data.push_back(this->header.type);
    return data;
}

size_t PacketHeader::get_size()
{
    return this->header.size;
}

command_type_t PacketHeader::get_type()
{
    return (command_type_t)this->header.type;
}
