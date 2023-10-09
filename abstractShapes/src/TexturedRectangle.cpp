#include "../include/TexturedRectangle.hpp"

TexturedRectangle::TexturedRectangle(std::string fn, SDL_Renderer* rendererPtr):m_renderer(rendererPtr){
            state = DEFAULT;
            m_surface = SDL_LoadBMP(fn.c_str());
            m_texture = SDL_CreateTextureFromSurface(m_renderer,m_surface);
            SDL_FreeSurface(m_surface);
}

TexturedRectangle::TexturedRectangle(SDL_Surface* surface, SDL_Texture* texture, SDL_Renderer* renderer)
        :m_surface(surface),m_texture(texture),m_renderer(renderer){
            state = ACQUIRED;
}

TexturedRectangle::~TexturedRectangle(){
            if(state == DEFAULT) {
                SDL_DestroyTexture(m_texture);
        }
}

void TexturedRectangle::setRectangleProperties (int x, int y, int w, int h){
    m_rectangle.x = x;
    m_rectangle.y = y;
    m_rectangle.w = w;
    m_rectangle.h = h;
}

void TexturedRectangle::update(){
    
}

void TexturedRectangle::render(){
    SDL_RenderCopy(m_renderer,m_texture,NULL,&m_rectangle);
}