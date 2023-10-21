#ifndef TEXTURED_RECTANGLE_HPP
#define TEXTURED_RECTANGLE_HPP

#include <string>
#include <SDL2/SDL.h>
#include <utility>

#include "AnimateSprite.hpp"

class TexturedRectangle{
    public:
        TexturedRectangle( SDL_Renderer* rendererPtr, const std::string fn);

        //compiler-generated copy constructor works, shallow copy is desired
        ~TexturedRectangle();
        //w,h ordered pair
        void setDimensions(std::pair<int,int>);
        //x,y orderered pair
        void setPosition(std::pair<int,int>);
        void render(SDL_Rect* = nullptr);
        std::pair<int,int> getDimensions();
        std::pair<int,int> getPosition();

    private:
    SDL_Rect m_rectangle;
    SDL_Surface* m_surface;
    SDL_Texture* m_texture;
    SDL_Renderer* m_renderer;

};
#endif