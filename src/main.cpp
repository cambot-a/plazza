/*
** EPITECH PROJECT, 2026
** oop.arcade
** File description:
** src/main.cpp
*/

#include "help.hpp"
#include "Pizzeria.hpp"
#include "epitech_standard_macros.hpp"
#include "ThreadSafeOstream.hpp"
#include <iostream>
#include <cstring>

int main(int ac, char *av[]) {
    ThreadSafeOstream safe_cerr(std::cerr);

    if (ac == 1) {
        safe_cerr << "not enough program arguments" << std::endl;
        return FAILURE;
    }
    try {
        std::string first_arg(av[1]);
        if (ac == 2 && std::regex_match(first_arg.begin(), first_arg.end(), help_regx)) {
            help();
            return EXIT_SUCCESS;
        }
    } catch (HelpException& e) {
        safe_cerr << e.what() << std::endl;
        return EXIT_84;
    }
    try {
        Pizzeria new_pizzeria(ac, av);
        return new_pizzeria.run();
    } catch (PlazzaException& e) {
        safe_cerr << e.what() << std::endl;
        return EXIT_84;
    }
}
