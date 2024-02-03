#pragma once
#include "ECS.hpp"
#include <iostream>
#include <cassert>
#include <array>
#include <queue>
class EntityManager 
{
private:
    static std::queue<Entity>& getIdGenerator(){
        static std::queue<Entity>* IDgenerator = new std::queue<Entity>();
        return *IDgenerator;
    };
    static std::array<Signature, MAX_ENTITY>& getSignatureArray(){
        static std::array<Signature, MAX_ENTITY>* arr= new std::array<Signature, MAX_ENTITY>();
        return *arr;
    };
public:
    EntityManager(){};
    static void init(){
        std::queue<Entity>* q = &getIdGenerator();
        for(int i = 0; i < MAX_ENTITY; i++)
            q->push(i);
    }

    /**
     * to initialize the entity, call getUniqueID to get unique identity
     * @return Unique Entity id
    */
    static int getUniqueID(){
        assert(!getIdGenerator().empty());
        int id = getIdGenerator().front();
        getIdGenerator().pop();
        return id;
    }
    /**
     * static add function register the entity into the entityManager
     * @param entity the target
     * @param data the Signature with containg component
    */
    static void add(Entity entity, Signature data = 0){
        assert(entity < MAX_ENTITY);
        getSignatureArray()[entity] = data;
    };
    /**
     * //static remove function removees the entity from the entityManager
     * Use ComponentManager::remove instead
    */
    static void remove(Entity entity){
        assert(getSignatureArray()[entity] != 0);
        getIdGenerator().push(entity);
        getSignatureArray()[entity] = 0;
    };
    /**
     * get the signature of the target entity
     * @return Entity Signature 
    */
    static Signature find(Entity entity){
        // assert(getSignatureArray()[entity] != 0);
        return getSignatureArray()[entity];
    };
};