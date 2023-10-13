#include <string>
#include <SDL2/SDL.h>

#include "AnimateSprite.hpp"

class TexturedRectangle{
    public:
        TexturedRectangle( SDL_Renderer* rendererPtr, std::string fn);

        //compiler-generated copy constructor works, shallow copy is desired

        ~TexturedRectangle();

        void setRectangleProperties(int, int, int, int);
        void setRectanglePosition(int, int); //helps debug
        void update();
        void render(SDL_Rect* = nullptr);
        bool isColliding(const TexturedRectangle&);
        void getCoordinates();

    private:
    SDL_Rect m_rectangle;
    SDL_Surface* m_surface;
    SDL_Texture* m_texture;
    SDL_Renderer* m_renderer;

};