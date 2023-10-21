#include<algorithm>
#include<iostream>

#include "TexturedRectangle.hpp"
#include "ResourceManager.hpp"

TexturedRectangle::TexturedRectangle
(SDL_Renderer* rendererPtr, const std::string fn):m_renderer(rendererPtr){
    m_surface = ResourceManager::GetInstance().GetSurface(fn); 
    m_texture = SDL_CreateTextureFromSurface(m_renderer,m_surface);
    m_rectangle.x = 100;
    m_rectangle.y = 100;
    m_rectangle.w = 100;    
    m_rectangle.h = 100;
}

TexturedRectangle::~TexturedRectangle(){
    SDL_DestroyTexture(m_texture);
}

void TexturedRectangle::setDimensions (std::pair<int,int>dimensions){
    m_rectangle.w = dimensions.first;
    m_rectangle.h = dimensions.first;
}

void TexturedRectangle::setPosition(std::pair<int,int>position){
    m_rectangle.x = position.first;
    m_rectangle.y = position.second;
}

void TexturedRectangle::render(SDL_Rect* source){
     //textured rectangles have generalized use due to render copy using rectangles
    SDL_RenderCopy(m_renderer,m_texture,source,&m_rectangle);
}

std::pair<int,int> TexturedRectangle::getDimensions(){
    return std::make_pair(m_rectangle.x,m_rectangle.y);
}

std::pair<int,int> TexturedRectangle::getPosition(){
    return std::make_pair(m_rectangle.x,m_rectangle.y);
}