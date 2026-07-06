/*
** EPITECH PROJECT, 2026
** ReceptionCli.hpp
** File description:
** ReceptionCli
*/

#ifndef RECEPTIONCLI_HPP_
    #define RECEPTIONCLI_HPP_
    #include "CommandPacket.hpp"
    #include <memory>

class ReceptionCli
{
private:
    std::string user_in;
    std::shared_ptr<ACommandPacket> last_command;
public:
    ReceptionCli() : user_in("") {}
    ~ReceptionCli() {}
    void get_command_packet(
        std::shared_ptr<ACommandPacket>& command_packet);
};

#endif /* RECEPTIONCLI_HPP_ */
