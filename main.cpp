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
    q::setComponentData<Translation>(a, &data);
    q::setComponentData<Speed>(a, &da);
    Translation o = q::findComponentData<Translation>(a);
    Speed ou = q::findComponentData<Speed>(a);

    std::cout << o.position << o.angle << std::endl;
    std::cout << ou.speed << ou.accelaration << std::endl;

    // data  = {4, 5};

    // o = q::findComponentData<Translation>(a);
    // std::cout << o.position << o.angle << std::endl;
    return 0;
}