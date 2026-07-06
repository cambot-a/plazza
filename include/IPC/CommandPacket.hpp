/*
** EPITECH PROJECT, 2026
** CommandPacket.hpp
** File description:
** CommandPacket
*/

#ifndef COMMANDPACKET_HPP_
    #define COMMANDPACKET_HPP_
    #include "plazza_utils.hpp"
    #include "UnimplementedFeatureException.hpp"
    #include "pizza_data_t.hpp"
    #include "packet_serialization_data.hpp"
    #include <iostream>
    #include "PizzaSingle.hpp"

class ACommandPacket
{
public:
    command_type_t command_type;
    size_t size;
    ACommandPacket(command_type_t command_type, size_t size) : command_type(command_type), size(size) {}
    virtual ~ACommandPacket() {};
    virtual std::string print() const { return ""; };
    virtual std::vector<byte_t> serialize(void) = 0;
    command_type_t get_command_type() { return command_type; }
};

inline std::ostream& operator<<(std::ostream& out, ACommandPacket const& to_print) { return out << to_print.print(); }

class StatusCmd : public ACommandPacket
{
public:
    StatusCmd() : ACommandPacket(STATUS_CMD, 0) {}
    ~StatusCmd() {};
    StatusCmd(std::vector<byte_t>& serialized_data);
    std::string print() const;
    std::vector<byte_t> serialize(void);
};

class ExitCmd : public ACommandPacket
{
public:
    ExitCmd() : ACommandPacket(EXIT_CMD, 0) {}
    ~ExitCmd() {};
    ExitCmd(std::vector<byte_t>& serialized_data);
    std::string print() const;
    std::vector<byte_t> serialize(void);
};

using pizza_command_t = struct pizza_command_s {
    pizza_type_t pizza_type;
    pizza_size_t pizza_size;
    size_t count;
};

class PizzaCmd : public ACommandPacket
{
private:
    size_t pizza_order_matrix[PIZZA_TYPES_COUNT][PIZZA_SIZES_COUNT];
    void add_pizzas(pizza_command_t& command);
public:
    PizzaCmd(std::string arg);
    PizzaCmd(const PizzaCmd& to_copy);
    ~PizzaCmd() {};
    PizzaCmd(std::vector<byte_t>& serialized_data);
    std::shared_ptr<PizzaSingle> pop_pizza();
    std::string print() const;
    std::vector<byte_t> serialize(void);
};

#endif /* COMMANDPACKET_HPP_ */
