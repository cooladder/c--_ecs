#pragma once
#include "t.hpp"
#include <set>
#include <unordered_map>
#include <queue>

class q
{
private:
    static std::unordered_map<Entity, t>& getMap(){
        static std::unordered_map<Entity, t>* map = 
                                        new std::unordered_map<Entity, t>();
        return *map;
    };

    static std::unordered_map<std::type_index, int>& getComponentID(){
        static std::unordered_map<std::type_index, int>* map = 
                                        new std::unordered_map<std::type_index, int>();
        return *map;
    };

    static std::queue<Entity>& getIdGenerator(){
        static std::queue<Entity>* IDgenerator = new std::queue<Entity>();
        return *IDgenerator;
    };
public:
    q();

    static void init(){
        std::queue<Entity>* q = &getIdGenerator();
        for(int i = 0; i < MAX_ENTITY; i++)
            q->push(i);
    }

    static void registerEntity(Entity entity){
        std::unordered_map<Entity, t>* map = &getMap();
        (*map)[entity] = t();
    }

    template<typename T>
    static void setComponentData(Entity entity, T* data){
        std::unordered_map<Entity, t>* map = &getMap();
        assert(map->find(entity) != map->end());
        t *arr = &((*map)[entity]);
        arr->setData<T>(data);
    }

    template<typename T>
    static T findComponentData(Entity entity){
        std::unordered_map<Entity, t>* map = &getMap();
        assert(map->find(entity) != map->end());
        t *arr = &((*map)[entity]);
        return arr->find<T>();
    }
};
