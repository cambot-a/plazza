/*
** EPITECH PROJECT, 2026
** CommandPacket.cpp
** File description:
** CommandPacket
*/

#include "CommandPacket.hpp"
#include "plazza_exceptions.hpp"
#include <stdbool.h>
#include <regex>
#include <string>
#include <iostream>
#include <sstream>
#include <cstring>
#include <format>

void PizzaCmd::add_pizzas(pizza_command_t &command)
{
    this->pizza_order_matrix[command.pizza_type][command.pizza_size] += command.count;
}

static void str_to_pizza(std::string to_convert, pizza_command_t& dest)
{
    std::string pizza_type;
    std::string pizza_size;
    std::istringstream my_stream(to_convert);
    std::string pizza_count_str;

    my_stream >> pizza_type;
    my_stream >> pizza_size;
    my_stream >> pizza_count_str;
    pizza_count_str.erase(0, 1);
    dest = (pizza_command_t){
        str_to_pizza_type(pizza_type),
        str_to_pizza_size(pizza_size),
        stoul(pizza_count_str),
    };
}

PizzaCmd::PizzaCmd(std::string arg)
    : ACommandPacket(PIZZA_CMD, PIZZA_TYPES_COUNT * PIZZA_SIZES_COUNT * sizeof(size_t))
{
    pizza_command_t command_container = {};

    if (!std::regex_match(arg.begin(), arg.end(), pizza_regex))
        throw ParsingError(std::format("pizza regex tested false : '{}'", arg));

    std::istringstream pizza_ss(arg);
    std::string single_pizza_command;

    for (size_t pizza_type = 0; pizza_type <= FANTASIA; ++pizza_type)
        for (size_t pizza_size = 0; pizza_size <= PIZZA_XXL; ++pizza_size)
            this->pizza_order_matrix[pizza_type][pizza_size] = 0;
    while(std::getline(pizza_ss, single_pizza_command, ';'))
    {
        str_to_pizza(single_pizza_command, command_container);
        this->add_pizzas(command_container);
    }
}

StatusCmd::StatusCmd(std::vector<byte_t>&) : ACommandPacket(STATUS_CMD, 0) {}

ExitCmd::ExitCmd(std::vector<byte_t>&) : ACommandPacket(EXIT_CMD, 0) {}

PizzaCmd::PizzaCmd(std::vector<byte_t>& serialized_data)
    : ACommandPacket(PIZZA_CMD, PIZZA_TYPES_COUNT * PIZZA_SIZES_COUNT * sizeof(size_t))
{
    size_t pizza_type;
    size_t pizza_size;
    byte_t pizza_count_buffer[sizeof(size_t)];

    for (size_t pizza_type = 0; pizza_type <= FANTASIA; ++pizza_type)
        for (size_t pizza_size = 0; pizza_size <= PIZZA_XXL; ++pizza_size)
            this->pizza_order_matrix[pizza_type][pizza_size] = 0;
    for (size_t i = 0; i < PIZZA_TYPES_COUNT * PIZZA_SIZES_COUNT; ++i) {
        pizza_type = i / PIZZA_SIZES_COUNT;
        pizza_size = i % PIZZA_SIZES_COUNT;
        for (size_t j = 0; j < sizeof(size_t); ++j)
            pizza_count_buffer[j] = serialized_data[PACKET_HEADER_SIZE + i * sizeof(size_t) + j];
        this->pizza_order_matrix[pizza_type][pizza_size] = *(size_t *)pizza_count_buffer;
    }
}

PizzaCmd::PizzaCmd(const PizzaCmd& to_copy)
    : ACommandPacket(PIZZA_CMD, PIZZA_TYPES_COUNT * PIZZA_SIZES_COUNT * sizeof(size_t))
{
    memcpy(this->pizza_order_matrix, to_copy.pizza_order_matrix, sizeof(to_copy.pizza_order_matrix));
}

/*
PizzaCmd::PizzaCmd(size_t pizza_type, size_t pizza_size)
    : ACommandPacket(PIZZA_CMD, PIZZA_TYPES_COUNT * PIZZA_SIZES_COUNT * sizeof(size_t))
{
    for (size_t pizza_type = 0; pizza_type <= FANTASIA; ++pizza_type)
        for (size_t pizza_size = 0; pizza_size <= PIZZA_XXL; ++pizza_size)
            this->pizza_order_matrix[pizza_type][pizza_size] = 0;
    this->pizza_order_matrix[pizza_type][pizza_size] = 1;
}
*/

std::string StatusCmd::print() const
{
    std::string result = std::format("StatusCmd size({}), type(STATUS_CMD:{})",
        this->size, STATUS_CMD == this->command_type);

    return result;
}

std::string ExitCmd::print() const
{
    std::string result = std::format("ExitCmd size({}), type(EXIT_CMD:{})",
        this->size, EXIT_CMD == this->command_type);

    return result;
}

std::vector<byte_t> StatusCmd::serialize(void)
{
    std::vector<byte_t> data = {};
    PacketHeader header(0, this->command_type);

    return header.serialize();
}

std::string PizzaCmd::print() const
{
    std::string result = std::format("PizzaCmd size({}), type(PIZZA_CMD:{})\n",
        this->size, PIZZA_CMD == this->command_type);

    result += "\t\t";
    for (size_t pizza_size = 0; pizza_size <= PIZZA_XXL; ++pizza_size)
        result += std::string(pizza_size_as_str[pizza_size]) + "\t";
    result += "\n";
    for (size_t pizza_type = 0; pizza_type <= FANTASIA; ++pizza_type) {
        result += std::string(pizza_recipes[pizza_type].name) + " \t";
        for (size_t pizza_size = 0; pizza_size <= PIZZA_XXL; ++pizza_size)
            result += std::format("{}\t", this->pizza_order_matrix[pizza_type][pizza_size]);
        result += "\n";
    }
    result.pop_back();
    return result;
}

std::vector<byte_t> ExitCmd::serialize(void)
{
    std::vector<byte_t> data = {};
    PacketHeader header(0, this->command_type);

    return header.serialize();
}

static void serialize_pizza_type(size_t *sized_list, std::vector<byte_t>& dest)
{
    byte_t *data_buffer = (byte_t *)sized_list;

    for (size_t i = 0; i < PIZZA_SIZES_COUNT * sizeof(size_t); ++i)
        dest.push_back(data_buffer[i]);
}

std::vector<byte_t> PizzaCmd::serialize(void)
{
    PacketHeader header(this->size, this->command_type);
    std::vector<byte_t> data = header.serialize();

    for (size_t i = 0; i < PIZZA_TYPES_COUNT; ++i)
        serialize_pizza_type(this->pizza_order_matrix[i], data);
    return data;
}

std::shared_ptr<PizzaSingle> PizzaCmd::pop_pizza()
{
    for (size_t pizza_type = 0; pizza_type <= FANTASIA; ++pizza_type) {
        for (size_t pizza_size = 0; pizza_size <= PIZZA_XXL; ++pizza_size) {
            if (this->pizza_order_matrix[pizza_type][pizza_size] >= 1) {
                this->pizza_order_matrix[pizza_type][pizza_size] -= 1;
                return std::make_shared<PizzaSingle>(pizza_type, pizza_size);
            }
        }
    }    
    return nullptr;
}
