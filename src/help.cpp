/*
** EPITECH PROJECT, 2026
** help.cpp
** File description:
** help
*/

#include "epitech_standard_macros.hpp"
#include "help.hpp"
#include <fstream>
#include <iostream>
#include "ThreadSafeOstream.hpp"

void help(void)
{
    std::ifstream infile(help_file_path);
    std::string temp("");
    ThreadSafeOstream safe_cout(std::cout);

    try {
        while (std::getline(infile, temp))
            safe_cout << temp << std::endl;
    } catch(std::ios_base::failure e) {
        throw HelpException(std::string(e.what()));
    }
}
