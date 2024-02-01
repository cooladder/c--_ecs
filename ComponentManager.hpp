#pragma once
#include "ECS.hpp"
#include "ComponentArray.hpp"
#include "EntityManager.hpp"
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <cassert>
class ComponentManager
{
private:
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
    template<typename T>
    static std::unordered_map<std::type_index, ComponentArray<T>>& getMap(){
        static std::unordered_map<std::type_index, ComponentArray<T>>* map = 
                                        new std::unordered_map<std::type_index, ComponentArray<T>>();
        return *map;
    };
    ComponentManager(){};
    static void init(){
        std::queue<Entity>* q = &getIdGenerator();
        for(int i = 0; i < MAX_ENTITY; i++)
            q->push(i);
    }

    /// @brief Call this method before setting the data of the component.
    /// @param type The component type
    template<typename T>
    static void registerComponent(){
        std::unordered_map<std::type_index, ComponentArray<T>>* map = &getMap<T>();
        assert(map->find(std::type_index(typeid(T))) == map->end() && !getIdGenerator().empty());
        (*map)[std::type_index(typeid(T))] = ComponentArray<T>();
        getComponentID()[std::type_index(typeid(T))] = getIdGenerator().front();
        getIdGenerator().pop();
    }

    /**
     * Use setComponentData to set data to the entity.
     * IMPORTANT: Remember to register to the given component
     * @param entity the target
     * @param data the component data
    */
    template<typename T>
    static void setComponentData(Entity entity, T data){
        std::unordered_map<std::type_index, ComponentArray<T>> *map = &getMap<T>();
        assert(map->find(std::type_index(typeid(T))) != map->end());
        ComponentArray<T>* arr = &(*map)[std::type_index(typeid(T))];
        arr->setData(entity, data);
        int id = getComponentID()[std::type_index(typeid(T))];
        Signature sig = EntityManager::find(entity);
        sig[id] = 1;
        EntityManager::add(entity, sig);
    }

    /**
     * Use removeComponentData to remove data to the entity.
     * @param entity the target
     * @param data the component data
    */
    template<typename T>
    static void removeComponentData(Entity entity){
        std::unordered_map<std::type_index, ComponentArray<T>> *map = &getMap<T>();
        assert(map->find(std::type_index(typeid(T))) != map->end());
        ComponentArray<T> *arr = &(*map)[std::type_index(typeid(T))];
        arr->remove(entity);
        int id = getComponentID()[std::type_index(typeid(T))];
        Signature sig = EntityManager::find(entity);
        sig[id] = 0;
        EntityManager::add(entity, sig);
    }

    template<typename T>
    static T getComponentData(Entity entity){
        std::unordered_map<std::type_index, ComponentArray<T>> map = getMap<T>();
        assert(map.find(std::type_index(typeid(T))) != map.end());
        ComponentArray<T> arr = map[std::type_index(typeid(T))];
        return arr.find(entity);
    }
};