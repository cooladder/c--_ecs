#include "ECS.hpp"
#include "EntityManager.hpp"
#include "System.hpp"
#include "ComponentManager.hpp"
#include <iostream>
int main(){

    ComponentManager::init();
    EntityManager::init();

    Entity a = EntityManager::getUniqueID();
    Translation trans = {1, 2};
    Speed speed = {1, 13};
    Test test = {5};
    ComponentManager::registerEntity(a);
    ComponentManager::registerComponent<Translation>(a);
    ComponentManager::registerComponent<Speed>(a);
    ComponentManager::registerComponent<Test>(a);
    ComponentManager::setComponentData<Translation>(a, trans);
    ComponentManager::setComponentData<Speed>(a, speed);
    ComponentManager::setComponentData<Test>(a, test);

    std::cout << ComponentManager::findComponentData<Test>(a).tt << std::endl;
    std::cout << ComponentManager::findComponentData<Translation>(a).angle<< std::endl;
    std::cout << ComponentManager::findComponentData<Speed>(a).accelaration<< std::endl;

    // ComponentManager::removeEntity(a);
    // std::cout << ComponentManager::findComponentData<Test>(a).tt << std::endl;   // report missing entity

    ComponentManager::removeComponent<Speed>(a);
    // std::cout << ComponentManager::findComponentData<Speed>(a).speed << std::endl;   // report missing component 
    std::cout << ComponentManager::findComponentData<Test>(a).tt << std::endl;
    std::cout << ComponentManager::findComponentData<Translation>(a).angle<< std::endl;

    // Modify component
    trans = {12, 15};
    ComponentManager::setComponentData<Translation>(a, trans);
    std::cout << ComponentManager::findComponentData<Test>(a).tt << std::endl;
    std::cout << ComponentManager::findComponentData<Translation>(a).angle<< std::endl;

    return 0;
}