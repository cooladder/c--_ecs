#pragma once
#include "ECS.hpp"
#include <array>
#include <unordered_map>
#include <stack>
#include <cassert>
#include <typeinfo>
#include <typeindex>

class ComponentArray 
{
private:
    std::array<void*, MAX_COMPONENTS> idToData;
    std::unordered_map<std::type_index, int> componentToId;
    std::stack<int> idGenerator;
    int end = -1;
public:
    ComponentArray(){
        for(int i = MAX_COMPONENTS-1; i >= 0; i--)
            idGenerator.push(i);
    };

    template<typename T>
    void genSpace(){
        assert(!idGenerator.empty() && componentToId.find(std::type_index(typeid(T))) == componentToId.end());
        int id = idGenerator.top();
        idGenerator.pop();
        componentToId[std::type_index(typeid(T))] = id; 
        idToData[id] = new T;
        end++;
    }

    template<typename T>
    void setData(T data){
        assert(componentToId.find(std::type_index(typeid(T))) != componentToId.end());
        *(T*)idToData[componentToId[std::type_index(typeid(T))]] = data;
    }

    template<typename T>
    T find(){
        assert(componentToId.find(std::type_index(typeid(T))) != componentToId.end());
        return *(T*)idToData[componentToId[std::type_index(typeid(T))]];
    }

    template<typename T>
    void remove(){
        assert(componentToId.find(std::type_index(typeid(T))) != componentToId.end());
        int id = componentToId[std::type_index(typeid(T))];
        componentToId.erase(std::type_index(typeid(T)));
        free(idToData[id]);
        idToData[id] = idToData[end];
        Entity lastEntity;
        for(auto& it: componentToId)
            if(it.second == end){
                it.second = id;
                break;
            }
        idGenerator.push(end);
        end--;
    }
};