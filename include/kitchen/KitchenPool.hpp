/*
** EPITECH PROJECT, 2026
** KitchenPool.hpp
** File description:
** KitchenPool
*/

#ifndef KITCHENPOOL_HPP_
    #define KITCHENPOOL_HPP_
    #include <vector>
    #include <memory>
    #include "KitchenParent.hpp"
    #define KITCHEN_UPDATE_FREQ 1000
    #define KITCHENPOOL_TIMEOUT 2500

class KitchenPool
{
private:
    std::mutex kitchen_protector;
    size_t nb_cooks;
    size_t multiplier;
    size_t restock_delay;
    std::vector<std::shared_ptr<KitchenParent>> kitchens;
    std::mutex running_protector;
    bool running;
    std::thread kitchen_manager;

    void stop_kitchen_pool();
    int add_kitchen();
    std::shared_ptr<KitchenParent> get_least_busy_kitchen();
    void kitchen_manager_job();
public:
    bool is_running();
    KitchenPool(size_t nb_cooks, size_t multiplier, size_t restock_delay)
        : kitchen_protector(), nb_cooks(nb_cooks), multiplier(multiplier),
        restock_delay(restock_delay), kitchens({}), running_protector(), running(true),
        kitchen_manager([this]() { this->kitchen_manager_job(); }) {}
    ~KitchenPool();
    std::string print();
    int push_job(std::shared_ptr<ACommandPacket>& job);
};

#endif /* KITCHENPOOL_HPP_ */