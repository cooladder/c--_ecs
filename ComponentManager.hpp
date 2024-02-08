#pragma once
#include "ComponentArray.hpp"
#include <set>
#include <unordered_map>
#include <queue>

class ComponentManager
{
private:
    static std::unordered_map<Entity, ComponentArray>& getMap(){
        static std::unordered_map<Entity, ComponentArray>* map = 
                                        new std::unordered_map<Entity, ComponentArray>();
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
    ComponentManager();

    static void init(){
        std::queue<Entity>* q = &getIdGenerator();
        for(int i = 0; i < MAX_ENTITY; i++)
            q->push(i);
    }

    static void registerEntity(Entity entity){
        std::unordered_map<Entity, ComponentArray>* map = &getMap();
        (*map)[entity] = ComponentArray();
    }

    template<typename T>
    static void registerComponent(Entity entity){
        std::unordered_map<Entity, ComponentArray>* map = &getMap();
        ComponentArray *arr = &((*map)[entity]);
        arr->genSpace<T>();
    }

    template<typename T>
    static void setComponentData(Entity entity, T data){
        std::unordered_map<Entity, ComponentArray>* map = &getMap();
        assert(map->find(entity) != map->end());
        ComponentArray *arr = &((*map)[entity]);
        arr->setData<T>(data);
    }

    template<typename T>
    static T findComponentData(Entity entity){
        std::unordered_map<Entity, ComponentArray>* map = &getMap();
        assert(map->find(entity) != map->end());
        ComponentArray *arr = &((*map)[entity]);
        return arr->find<T>();
    }

    static void removeEntity(Entity entity){
        std::unordered_map<Entity, ComponentArray>* map = &getMap();
        assert(map->find(entity) != map->end());
        map->erase(entity);
    }

    template<typename T>
    static void removeComponent(Entity entity){
        std::unordered_map<Entity, ComponentArray>* map = &getMap();
        assert(map->find(entity) != map->end());
        ComponentArray *arr = &((*map)[entity]);
        arr->remove<T>();
    }
};