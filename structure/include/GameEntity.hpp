#ifndef GAME_ENTITY_HPP
#define GAME_ENTITY_HPP

#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <cassert>

//header file inclusions
#include "SDL2/SDL.h"
#include "CResources.hpp"
#include "CCollider.hpp"
#include "Component.hpp"
#include "CPhysics.hpp"

using Group = std::size_t;
constexpr std::size_t maxGroups{32};
using groupBitset = std::bitset<maxGroups>;

class GameEntity{
public:
    GameEntity()=default;
    ~GameEntity()=default;

    void render();
    
    template <typename T, typename... TArgs>
    T& addComponent(TArgs&&... args){
        T* c(new T(std::forward<TArgs>(args)...));
        componentBitset[getComponentID<T>()] = true;
        componentArray[getComponentID<T>()] = c;

        c->init();
        m_components.emplace_back(std::move(std::make_unique(c)));
        c->m_entity = this;
        return *c;

    }

    //memory will be released by unique ptrs when entity is destroyed
    template <typename T>
    void removeEntity(){
        componentArray[getComponentID<T>()] = nullptr;
        componentBitset[getComponentID<T>()] = false;
    }

    template <typename T>
    bool hasComponent(){
        return componentBitset[getComponentID<T>()];
    }

    template <typename T>
    T& getComponent(){
        assert(this->hasComponent<T>());
        auto ptr{componentArray[getComponentID<T>()]};
        return *reinterpret_cast<T*>(ptr);
    }

public:    
    ComponentBitset componentBitset;
    ComponentArray componentArray;//stores raw pointers for general use

private:
    std::vector<std::unique_ptr<Component>> m_components; //unique pointers for memory management

};

#endif