#ifndef CPhysics_HPP
#define CPhysics_HPP

#include <utility>
#include <vector>
#include <memory>

#include <SDL2/SDL.h>

#include "Component.hpp"
#include "CCollider.hpp"

using std::pair;

struct CPhysics:Component{
public:
    CPhysics();

public:
    //sprite x,y coordinates
    pair<int,int> m_pos;
    //sprite size
    pair<int,int> m_size;
    pair<float,float> m_velocity;
};

#endif