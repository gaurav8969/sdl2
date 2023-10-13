#include<algorithm>
#include<iostream>

#include "TexturedRectangle.hpp"
#include "ResourceManager.hpp"

TexturedRectangle::TexturedRectangle(SDL_Renderer* rendererPtr, std::string fn):m_renderer(rendererPtr){
            m_surface = ResourceManager::GetInstance().GetSurface(fn); 
            m_texture = SDL_CreateTextureFromSurface(m_renderer,m_surface);
}


TexturedRectangle::~TexturedRectangle(){
    SDL_DestroyTexture(m_texture);
}

void TexturedRectangle::setRectangleProperties (int x, int y, int w, int h){
    m_rectangle.x = x;
    m_rectangle.y = y;
    m_rectangle.w = w;
    m_rectangle.h = h;
}

void TexturedRectangle::setRectanglePosition(int x, int y){
    m_rectangle.x = x;
    m_rectangle.y = y;
}

void TexturedRectangle::getCoordinates(){
    std::cout << "x is " << m_rectangle.x << std::endl;
    std::cout << "y is " << m_rectangle.y << std::endl;
    std::cout << "w is " << m_rectangle.w << std::endl;
    std::cout << "h is " << m_rectangle.h << std::endl;
}

void TexturedRectangle::update(){

}

void TexturedRectangle::render(SDL_Rect* source){
     //textured rectangles have generalized use due to render copy using rectangles
    SDL_RenderCopy(m_renderer,m_texture,source,&m_rectangle);
}

bool TexturedRectangle::isColliding(const TexturedRectangle& rectangle){
    //horizontal axis
    int m_xStart = m_rectangle.x;
    int m_xEnd = m_xStart + m_rectangle.w;
    int xStart = rectangle.m_rectangle.x;
    int xEnd = xStart + rectangle.m_rectangle.w;

    int m_xLength = m_rectangle.w;
    int xLength = rectangle.m_rectangle.w;
    int xDistance = std::max(m_xEnd,xEnd) - std::min(m_xStart,xStart);
    
    bool xOverlap = false;
    if ( xDistance <  m_xLength + xLength){
        xOverlap = true;
    }

    //vertical axis
    int m_yStart = m_rectangle.y;
    int m_yEnd = m_yStart + m_rectangle.h;
    int yStart = rectangle.m_rectangle.y;
    int yEnd = yStart + rectangle.m_rectangle.h;

    int m_yLength = m_rectangle.h;
    int yLength = rectangle.m_rectangle.h;
    int yDistance = (std::max(m_yEnd,yEnd) - std::min(m_yStart,yStart));
    
    bool yOverlap = false;
    if ( yDistance <  m_yLength + yLength){
        yOverlap = true;
    }

    return (xOverlap && yOverlap);
}