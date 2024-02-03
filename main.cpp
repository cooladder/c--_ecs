#include "ECS.hpp"
#include "EntityManager.hpp"
#include "System.hpp"
#include "ComponentManager.hpp"
#include <iostream>
int main(){
    EntityManager::init();
    ComponentManager::init();

    Entity a = EntityManager::getUniqueID();
    Entity b = EntityManager::getUniqueID();
    EntityManager::add(a);
    EntityManager::add(b);
    ComponentManager::registerComponent<Translation>();
    ComponentManager::registerComponent<Speed>();
    Translation dataA = {0, 1};
    Translation dataB = {2, 3};
    Speed dataC = {4, 5};
    Speed dataD = {6, 7};
    ComponentManager::setComponentData<Translation>(a, dataA);
    ComponentManager::setComponentData<Translation>(b, dataB);
    ComponentManager::setComponentData<Speed>(a, dataC);
    ComponentManager::setComponentData<Speed>(b, dataD);

    Translation out = ComponentManager::getComponentData<Translation>(a);
    Speed dout = ComponentManager::getComponentData<Speed>(b);
    std::cout << out.position << " " << out.algle << std::endl;
    std::cout << dout.accelaration<< " " << dout.speed<< std::endl;
    // EntityManager::remove(a);

    // Entity c = EntityManager::getUniqueID();
    // EntityManager::add(c);
    // ComponentManager::setComponentData<Translation>(b, dataB);
    // ComponentManager::setComponentData<Speed>(a, dataC);

    // Translation o = ComponentManager::getComponentData<Translation>(c);
    // std::cout << o.position << " " << o.algle << std::endl;

    return 0;
}