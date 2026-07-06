/*
** EPITECH PROJECT, 2026
** CookWorker.cpp
** File description:
** CookWorker
*/

#include "KitchenChild.hpp"
#include <unistd.h>
#include "pizza_data_t.hpp"
#include <random>
#include <mutex>
#include <iostream>
#include "ThreadSafeOstream.hpp"
#include "ThreadSafeStringstream.hpp"
#include <memory>

std::string CookWorker::print()
{
    ThreadSafeStringstream result_stream;
    std::shared_ptr<PizzaSingle> current_pizza_copy = this->get_current_pizza();

    result_stream << "cook n*" << this->get_id();
    if (current_pizza_copy == nullptr) {
        result_stream << " is idle";
    } else
        result_stream << " is cooking: " << *current_pizza_copy;
    return result_stream.str();
}

void CookWorker::set_current_pizza(std::shared_ptr<PizzaSingle> pizza)
{
    std::lock_guard lock(this->cook_protection);
    if (pizza == nullptr) {
        this->current_pizza = nullptr;
    } else
        this->current_pizza = std::make_unique<PizzaSingle>(*pizza);
}

void CookWorker::set_current_pizza(size_t pizza_type, size_t pizza_size)
{
    std::lock_guard lock(this->cook_protection);
    this->current_pizza = std::make_unique<PizzaSingle>(pizza_type, pizza_size);
}

std::shared_ptr<PizzaSingle> CookWorker::get_current_pizza()
{
    std::lock_guard lock(this->cook_protection);
    if (this->current_pizza == nullptr)
        return nullptr;
    return std::make_shared<PizzaSingle>(*(this->current_pizza));
}

void cook_worker_job(CookWorker &cook_worker_class)
{
    ThreadSafeOstream thread_safe_cerr(std::cerr);

    for (;;) {
        std::shared_ptr<PizzaSingle> new_pizza = cook_worker_class.parent_kitchen.get_pizza_command();
        cook_worker_class.set_current_pizza(new_pizza);
        if (new_pizza == nullptr) {
            if (cook_worker_class.parent_kitchen.is_exiting())
                return;
            continue;
        }
        byte_t recipe = new_pizza->get_recipe();
        new_pizza->cook(recipe, cook_worker_class.parent_kitchen.cellar, cook_worker_class.multiplier);
        cook_worker_class.set_current_pizza(nullptr);
    }
}

CookWorker::CookWorker(KitchenChild& parent_kitchen)
    : cook_protection(), current_pizza(nullptr), parent_kitchen(parent_kitchen),
        multiplier(parent_kitchen.multiplier), id(0),
        cw_thread([this]() { cook_worker_job(*this); })
{
    id = this->cw_thread.get_id();
}

std::thread::id CookWorker::get_id()
{
    return this->id;
}

CookWorker::~CookWorker()
{
    if (cw_thread.joinable())
		cw_thread.join();
}
