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
    bool isColliding(GameEntity* sprite, size_t collider, size_t collidingWith, bool IsPixelPerfect = false);
    void updatePosition(int,int);
    void updateSpriteSize(int,int);
    void updateColliderSize(size_t, int,int);
    //click inside a sprite boundary to see the details of the clicked pixel
    void checkPixel(int x, int y);

    private:
    SDL_Renderer* m_renderer;
    SDL_Surface* m_surface;
    SDL_Rect m_intersection;
    std::vector<std::unique_ptr<Collider2D>> m_colliderComponents;
    TexturedRectangle* m_sprite;
    std::vector<int>* m_mask;
    int m_w,m_h; //sprite size
    void createMask();
};

#endif