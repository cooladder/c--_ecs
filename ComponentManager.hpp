#pragma once
#include "ECS.hpp"
#include "ComponentArray.hpp"
#include "EntityManager.hpp"
#include <typeinfo>
#include <typeindex>
#include <set>
#include <unordered_map>
#include <cassert>
class ComponentManager
{
private:
    template<typename T>
    static ComponentArray<T> arr;

    static std::set<std::type_index>& getComponentSet(){
        static std::set<std::type_index> *set = new std::set<std::type_index>;
        return *set;
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
        assert(!getComponentSet().count(std::type_index(typeid(T))) && !getIdGenerator().empty());
        arr<T> = ComponentArray<T>();
        getComponentID()[std::type_index(typeid(T))] = getIdGenerator().front();
        getIdGenerator().pop();
        getComponentSet().insert(std::type_index(typeid(T)));
    }

    /**
     * Use setComponentData to set data to the entity.
     * IMPORTANT: Remember to register to the given component
     * @param entity the target
     * @param data the component data
    */
    template<typename T>
    static void setComponentData(Entity entity, T data){
        assert(getComponentSet().count(std::type_index(typeid(T))));
        arr<T>.setData(entity, data);
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
        assert(getComponentSet().count(std::type_index(typeid(T))) && checkEntityComponent<T>(entity));
        arr<T>.remove(entity);
        int id = getComponentID()[std::type_index(typeid(T))];
        Signature sig = EntityManager::find(entity);
        sig[id] = 0;
        EntityManager::add(entity, sig);
    }

    template<typename T>
    static T getComponentData(Entity entity){
        assert(getComponentSet().count(std::type_index(typeid(T))) && checkEntityComponent<T>(entity));
        return arr<T>.find(entity);
    }

    template<typename T>
    static bool checkEntityComponent(Entity entity){
        int id = getComponentID()[std::type_index(typeid(T))];
        Signature sig = EntityManager::find(entity);
        return sig[id];
    }
};

template<typename T>
ComponentArray<T> ComponentManager::arr = ComponentArray<T>();