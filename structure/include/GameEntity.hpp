#ifndef GAME_ENTITY_HPP
#define GAME_ENTITY_HPP

#include <string>
#include <vector>
#include <memory>
//third party inclusions
#include "SDL2/SDL.h"
#include "TexturedRectangle.hpp"
#include "Collider2D.hpp"

class GameEntity{
    public:
    GameEntity()=delete;
    GameEntity(SDL_Renderer*,std::string spritepath);
    ~GameEntity();

    void addCollider(int xOffset, int yOffset, int width, int height);
    void render();
    //index of collider of this object and collider of the other GameEntity object in collision
    bool isColliding(GameEntity* sprite,size_t collider,size_t  collidingWith);
    //Collider2D* getCollider(size_t);
    //update constituent components like collider and sprite
    void updatePosition(int,int);
    void updateSpriteSize(int,int);
    void updateColliderSize(size_t, int,int);

    private:
    SDL_Renderer* m_renderer;
    std::vector<std::unique_ptr<Collider2D>> m_colliderComponents;
    TexturedRectangle* m_sprite;
};

#endif