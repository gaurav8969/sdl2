#include <exception>
#include "Collider2D.hpp"

Collider2D::Collider2D(){
    m_collider = new SDL_Rect();
    if(m_collider == nullptr){
        throw std::bad_alloc();
    }
}

Collider2D::~Collider2D(){
    delete m_collider;
    m_collider = nullptr;
}

bool Collider2D::isColliding(const Collider2D * collider){
    //horizontal axis
    int m_xStart = m_collider->x;
    int m_xEnd = m_xStart + m_collider->w;
    int xStart = collider->m_collider->x;
    int xEnd = xStart + collider->m_collider->w;

    int m_xLength = m_collider->w;
    int xLength = collider->m_collider->w;
    int xDistance = std::max(m_xEnd,xEnd) - std::min(m_xStart,xStart);
    
    bool xOverlap = false;
    if ( xDistance <  m_xLength + xLength){
        xOverlap = true;
    }

    //vertical axis
    int m_yStart = m_collider->y;
    int m_yEnd = m_yStart + m_collider->h;
    int yStart = collider->m_collider->y;
    int yEnd = yStart + collider->m_collider->h;

    int m_yLength = m_collider->h;
    int yLength = collider->m_collider->h;
    int yDistance = (std::max(m_yEnd,yEnd) - std::min(m_yStart,yStart));
    
    bool yOverlap = false;
    if ( yDistance <  m_yLength + yLength){
        yOverlap = true;
    }

    return xOverlap && yOverlap;
}

void Collider2D::setPosition(std::pair<int,int> position){
    m_collider->x = position.first;
    m_collider->y = position.second;
}

void Collider2D::setDimensions(std::pair<int,int> dimensions){
    m_collider->w = dimensions.first;
    m_collider->h = dimensions.second;
}

SDL_Rect* Collider2D::getCollider(){
    return m_collider;
}