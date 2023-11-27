//not to clutter game entity 
#include "CPhysics.hpp"

CPhysics::CPhysics(){
    m_pos = {0,0};
    m_size = {100,100};
}

/* void CPhysics::updateSize(int w, int h){
    updateColliderSize(0,w,h);
    std::pair<int,int> size = std::make_pair(w,h);
    m_sprite->setDimensions(size);
    m_w = w;
    m_h = h;

    createMask();
} */