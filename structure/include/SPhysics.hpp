#ifndef SPhysics_HPP
#define SPhysics_HPP

#include <stdexcept>

#include "System.hpp"
#include "GameEntity.hpp"

class Physics:System{
    void jump();
    bool isColliding(GameEntity* f_entity, GameEntity* s_entity,size_t m_collider, size_t collider, bool isPixelPerfect);
};

#endif