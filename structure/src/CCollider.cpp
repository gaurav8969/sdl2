#include <exception>
#include <stdexcept>
#include <algorithm>

#include "CCollider.hpp"

Collider::Collider(){
    
}

void Collider::updateColliderSize(int w, int h){
    colliderRect.w = w;
    colliderRect.h = h;
}
