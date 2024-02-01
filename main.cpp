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
    Entity c = EntityManager::getUniqueID();
    Entity d = EntityManager::getUniqueID();
    EntityManager::add(a);
    EntityManager::add(b);
    EntityManager::add(c);
    EntityManager::add(d);
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
    std::cout << out.position << " " << out.algle << std::endl;
    Speed dout = ComponentManager::getComponentData<Speed>(a);
    std::cout << dout.speed<< " " << dout.accelaration<< std::endl;
    std::cout << EntityManager::find(a) << std::endl;
    std::cout << EntityManager::find(b) << std::endl;
    ComponentManager::removeComponentData<Translation>(a);
    std::cout << EntityManager::find(a) << std::endl;
    std::cout << EntityManager::find(b) << std::endl;

    return 0;
}