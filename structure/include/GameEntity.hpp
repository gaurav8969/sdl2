#ifndef GAME_ENTITY_HPP
#define GAME_ENTITY_HPP

#include <string>
//third party inclusions
#include "SDL2/SDL.h"
#include "TexturedRectangle.hpp"

class GameEntity{
    public:
    GameEntity()=delete;
    GameEntity(SDL_Renderer*,std::string spritepath);
    ~GameEntity();

    void render();
    TexturedRectangle& getRect();
    bool isColliding(GameEntity& sprite);

    private:
    SDL_Renderer* m_renderer;
    TexturedRectangle* m_sprite;
};

#endif