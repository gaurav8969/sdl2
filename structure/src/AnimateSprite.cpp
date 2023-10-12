#include "AnimateSprite.hpp"

AnimateSprite::AnimateSprite(){}
AnimateSprite::~AnimateSprite(){}

void AnimateSprite::draw(int x, int y, int w, int h){
    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = w;
    dstrect.h = h;
}

void AnimateSprite::setFrame(int x, int row, int w, int h, int frameNo){ //loop{setFrame()} animates along a row
//row starts from 0, w&h are dimensions of sprites, frameNo is the frame to display, start from 0
    srcrect.x = x + w*frameNo;
    srcrect.y = row*h; //start row  from 0
    srcrect.w = w;
    srcrect.h = h;
}

void AnimateSprite::render(SDL_Renderer* renderer, SDL_Texture* texture){
    SDL_RenderCopy(renderer,texture,&srcrect,&dstrect);
}