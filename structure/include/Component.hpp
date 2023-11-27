#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <bitset>
#include <array>

using ComponentID = std::size_t;

constexpr std::size_t maxComponents{32};

class GameEntity;
struct Component;

using ComponentBitset = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

struct  Component{
public:
    virtual void update(){}
    virtual void init(){}

    virtual ~Component(){}

public:
    GameEntity* m_parent;
};

inline ComponentID getUniqueID() noexcept{
    static ComponentID lastid{0u};
    return lastid++;
}

template<typename T>
inline ComponentID getComponentID() noexcept{
    static ComponentID componentID{getUniqueID()};
    return componentID;
}
#endif