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

void TexturedRectangle::update(){

}

void TexturedRectangle::render(SDL_Rect* source){
     //textured rectangles have generalized use due to render copy using rectangles
    SDL_RenderCopy(m_renderer,m_texture,source,&m_rectangle);
}