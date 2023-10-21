#ifndef GAME_ENTITY_HPP
#define GAME_ENTITY_HPP

#include <string>
//third party inclusions
#include "SDL2/SDL.h"
#include "TexturedRectangle.hpp"
#include "Collider2D.hpp"

class GameEntity{
    public:
    GameEntity()=delete;
    GameEntity(SDL_Renderer*,std::string spritepath);
    ~GameEntity();

    void render();
    TexturedRectangle& getRect();
    bool isColliding(GameEntity* sprite);
    //update constituent components like collider and sprite
    void updatePosition(int,int);
    void updateSize(int,int); 

    private:
    SDL_Renderer* m_renderer;
    Collider2D* m_colliderComponent;
    TexturedRectangle* m_sprite;
};

#endif