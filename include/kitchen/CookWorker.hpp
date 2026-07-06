/*
** EPITECH PROJECT, 2026
** CookWorker.hpp
** File description:
** CookWorker
*/

#ifndef COOKWORKER_HPP_
    #define COOKWORKER_HPP_
    #include <thread>
    #include "pizza_data_t.hpp"
    #include "PizzaSingle.hpp"

class KitchenChild;

class CookWorker
{
private:
    std::mutex cook_protection;
    std::shared_ptr<PizzaSingle> current_pizza;
    KitchenChild& parent_kitchen;
    size_t multiplier;
    std::thread::id id;
    std::thread cw_thread;
    friend void cook_worker_job(CookWorker &cook_worker_class);
public:
    std::string print();
    void set_current_pizza(std::shared_ptr<PizzaSingle> pizza);
    void set_current_pizza(size_t pizza_type, size_t pizza_size);
    std::shared_ptr<PizzaSingle> get_current_pizza();
    std::thread::id get_id();
    CookWorker(KitchenChild& parent_kitchen);
    ~CookWorker();
};

#endif /* COOKWORKER_HPP_ */