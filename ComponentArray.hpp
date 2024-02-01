#pragma once
#include "ECS.hpp"
#include <array>
#include <stack>
#include <unordered_map>
#include <cassert>
template<typename T>
class ComponentArray
{
private:
    std::array<T, MAX_ENTITY> idToData;
    std::unordered_map<Entity, int> entityToId;
    std::stack<int> idGenerator;
    int end = -1; // the end index
public:
    ComponentArray(){
        for(int i = MAX_ENTITY-1; i >= 0; i--)
            idGenerator.push(i);
    };
    /**
     * Use setData to update or add a new data
    */
    void setData(Entity entity, T data){
        assert(idGenerator.size() != 0);
        if(entityToId.find(entity) != entityToId.end()){
            idToData[entityToId[entity]] = data;
            return;
        }
        int id = idGenerator.top();
        idGenerator.pop();
        entityToId[entity] = id; 
        idToData[id] = data;
        end++;
    };
    /**
     * Use find to get the target entity data.
     * IMPORTANT: You cannot modify data using find method, using setData() instead
     * @param entity the target
    */
    T find(Entity entity){
        assert(entityToId.find(entity) != entityToId.end());
        return idToData[entityToId[entity]];
    };
    /**
     * Remove the given entity and make array packed
    */
    void remove(Entity entity){
        assert(entityToId.find(entity) != entityToId.end());
        int id = entityToId[entity];
        entityToId.erase(entity);
        idToData[id] = idToData[end];
        Entity lastEntity;
        for(auto& it: entityToId)
            if(it.second == end){
                it.second = id;
                break;
            }
        idGenerator.push(end);
        end--;
    };
};