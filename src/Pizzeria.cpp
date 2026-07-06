/*
** EPITECH PROJECT, 2026
** Pizzeria.cpp
** File description:
** Pizzeria
*/

#include "Pizzeria.hpp"
#include <regex>
#include "plazza_utils.hpp"
#include "epitech_standard_macros.hpp"
#include "plazza_exceptions.hpp"
#include <signal.h>
#include "ctrl_c_handler.hpp"
#include "ThreadSafeOstream.hpp"
#include <poll.h>

void plazza_parse_program_args(int ac, char **av, Pizzeria& pizzeria)
{
    size_t pizzeria_args[3] = {};

    if (ac != DEFAULT_ARGUMENT_COUNT + 1)
        throw ParsingError("invalid program argument count");
    for (size_t i = 1; i < DEFAULT_ARGUMENT_COUNT + 1; ++i) {
        std::string arg(av[i]);
        if (!std::regex_match(arg.begin(), arg.end(), uint_rgx))
            throw ParsingError("program arguments must be unsigned ints");
        std::istringstream parser_stream(arg);
        parser_stream >> pizzeria_args[i - 1];
    }
    pizzeria.multiplier = pizzeria_args[0];
    pizzeria.nb_cooks = pizzeria_args[1];
    pizzeria.restock_delay = pizzeria_args[2];
}

void Pizzeria::pizzeria_manual_destroy()
{
    exit_flag.store(true);
}

bool Pizzeria::is_running()
{
    return !(exit_flag.load());
}

Pizzeria::Pizzeria(int ac, char **av) : kitchens(nullptr), exit_flag(false)
{
    ctrlc_handler = [this](int) {
        this->pizzeria_manual_destroy();
    };
    signal(SIGINT, ctrlc_handler_wrapper);
    plazza_parse_program_args(ac, av, *this);

    kitchens = std::make_unique<KitchenPool>(nb_cooks, multiplier, restock_delay);
}

Pizzeria::~Pizzeria() {}

int Pizzeria::run(void)
{
    std::shared_ptr<ACommandPacket> test_command = nullptr;
    std::shared_ptr<ACommandPacket> result = nullptr;
    ThreadSafeOstream safe_cerr(std::cerr);

    try {
        while (is_running()) {
            pollfd pfd{};
            pfd.fd = STDIN_FILENO;
            pfd.events = POLLIN;
            int has_cmd = poll(&pfd, 1, 100); // 100ms timeout
            if (!(has_cmd > 0 && (pfd.revents & POLLIN)))
                continue;
            try {
                reception_cli.get_command_packet(test_command);
            } catch (CLIerror& error) {
                if (kitchens->is_running() == false) {
                    pizzeria_manual_destroy();
                    return SUCCESS; 
                }
                safe_cerr << error.what() << std::endl;
                return FAILURE;
            } catch (ParsingError& error) {
                safe_cerr << error.what() << std::endl;
                return FAILURE;
            }
            if (kitchens->push_job(test_command) == FAILURE)
                return SUCCESS;
            if (test_command->command_type == EXIT_CMD)
                break;
        }
    } catch (PlazzaException& except) {
        safe_cerr << except.what();
        return FAILURE;
    }
    return SUCCESS;
}
