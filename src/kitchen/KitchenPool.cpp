/*
** EPITECH PROJECT, 2026
** KitchenPool.cpp
** File description:
** KitchenPool
*/

#include "KitchenPool.hpp"
#include "epitech_standard_macros.hpp"
#include "ThreadSafeOstream.hpp"

/*
    std::mutex kitchen_protector;
    std::vector<std::shared_ptr<KitchenParent>> kitchens;
    std::thread kitchen_manager;
*/

static void cli_interrupt()
{
    std::lock_guard<std::mutex> lock(stream_mutex);
}

void KitchenPool::stop_kitchen_pool()
{
    ThreadSafeOstream thread_safe_cout(std::cout);

    std::lock_guard lock(running_protector);
    cli_interrupt();
    running = false;
}

bool KitchenPool::is_running()
{
    std::lock_guard lock(running_protector);
    return running;
}

int KitchenPool::add_kitchen()
{
    std::shared_ptr<KitchenParent> new_kitchen =
        std::make_shared<KitchenParent>(nb_cooks, multiplier, restock_delay);
    if (new_kitchen->pid == 0)
        return FAILURE;
    kitchens.push_back(new_kitchen);
    return SUCCESS;
}

std::shared_ptr<KitchenParent> KitchenPool::get_least_busy_kitchen()
{
    if (this->kitchens.size() == 0)
        return nullptr;
    return this->kitchens[0]; // todo: return nullptr if no space
}

void KitchenPool::kitchen_manager_job()
{
    while (is_running()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(KITCHEN_UPDATE_FREQ));
    } // pull job, maintain kitchen 'business'
}

std::string KitchenPool::print() // parent
{
    return "kitchenPool {}"; // to implement
}

int KitchenPool::push_job(std::shared_ptr<ACommandPacket>& job)  // parent
{
    std::lock_guard<std::mutex> lock(this->kitchen_protector);
    ThreadSafeOstream safe_cout(std::cout);

    if (job->command_type == STATUS_CMD) {
        safe_cout << this->print() << std::endl;
        return SUCCESS;
    } else if (job->command_type == EXIT_CMD) {
        stop_kitchen_pool();
        return SUCCESS;
    }
    std::shared_ptr<KitchenParent> least_busy_kitchen = get_least_busy_kitchen();
    if (least_busy_kitchen == nullptr) {
        if (add_kitchen() == FAILURE)
            return FAILURE;
        least_busy_kitchen = get_least_busy_kitchen();
    }
    if (least_busy_kitchen == nullptr)
        throw UnimplementedFeatureException("failed to extend kitchens buffer");
    least_busy_kitchen->packet_manager << job;
    return SUCCESS;
}

KitchenPool::~KitchenPool()
{
    stop_kitchen_pool();
    std::this_thread::sleep_for(std::chrono::milliseconds(KITCHENPOOL_TIMEOUT));
}
