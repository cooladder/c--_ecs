#include "ECS.hpp"
#include "EntityManager.hpp"
#include "System.hpp"
#include "ComponentManager.hpp"
#include "q.hpp"
#include <iostream>
#include "t.hpp"
int main(){
    EntityManager::init();
    // ComponentManager::init();
    q::init();

    Entity a = EntityManager::getUniqueID();
    Translation data = {0, 1};
    Speed da = {12, 13};
    q::registerEntity(a);
    q::registerComponent<Translation>(a);
    q::registerComponent<Speed>(a);
    q::setComponentData<Translation>(a, data);
    q::setComponentData<Speed>(a, da);
    Translation o = q::findComponentData<Translation>(a);
    Speed ou = q::findComponentData<Speed>(a);

    std::cout << o.position << o.angle << std::endl;
    std::cout << ou.speed << ou.accelaration << std::endl;

    data  = {4, 5};

    o = q::findComponentData<Translation>(a);
    std::cout << o.position << o.angle << std::endl;

    Entity b = EntityManager::getUniqueID();
    q::registerEntity(b);
    q::registerComponent<Translation>(b);
    q::registerComponent<Speed>(b);
    q::setComponentData<Speed>(b, da);
    q::setComponentData<Translation>(b, data);

    o = q::findComponentData<Translation>(b);
    ou = q::findComponentData<Speed>(b);
    std::cout << o.position << o.angle << std::endl;
    std::cout << ou.speed<< ou.accelaration<< std::endl;

    q::removeComponent<Translation>(a);
    q::registerComponent<Translation>(a);
    return 0;
}