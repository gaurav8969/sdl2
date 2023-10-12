#ifndef ANIMATE_SPRITE_HPP
#define ANIMATE_SPRITE_HPP
#include <SDL2/SDL.h>

class AnimateSprite{
    public:
    AnimateSprite();
    ~AnimateSprite();

    void draw(int x,int y,int w,int h); //prepares rect to copy into
    void setFrame(int x, int row, int w, int h, int frameNo); //prepares the frame to be displayed
    void render(SDL_Renderer*, SDL_Texture*);

    private:
    SDL_Rect srcrect; //rectangular portion of texture to copy from during rendercopy
    SDL_Rect dstrect; //rect to copy into
};

#endif