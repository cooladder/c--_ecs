#pragma once
#include "ECS.hpp"
#include <array>
#include <cassert>
class System
{
private:
    std::array<Entity, MAX_ENTITY> arr;
    int end = 0;
public:
    System();
    void addEntity(Entity entity){
        assert(end < MAX_ENTITY);
        arr[end] = entity;
        end++;
    };
    virtual void update()=0;
};