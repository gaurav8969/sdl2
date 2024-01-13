#include <iostream>
#include <string>

#include "Text.hpp"

Text::Text(SDL_Renderer* renderer, int shape){
    if(TTF_Init() == -1){
        std::cout << "Could not initailize SDL2_ttf, error: " << TTF_GetError() << std::endl; 
    }else{
        std::cout << "SDL2_ttf system ready to go!" << std::endl;
    }

    this->renderer = renderer;
    // Load our font file and set the font size
    ourFont = TTF_OpenFont("./assets/fonts/pixelfont.ttf",32);
    // Confirm that it was loaded
    if(ourFont == nullptr){
        std::cout << "Could not load font" << std::endl;
    }
    std::string text;
    if(shape){
        text = "Game Over: Cross won!";
    }else{
        text = "Game Over: Circle won!";
    }

    // Pixels from our text
    SDL_Surface* surfaceText = TTF_RenderText_Solid(ourFont,text.c_str(),{255,255,255});

    // Setup the texture
    textureText = SDL_CreateTextureFromSurface(renderer,surfaceText);

    // Free the surface
    // We are done with it after we have uploaded to
    // the texture
    SDL_FreeSurface(surfaceText); 
}

void Text::render(){
    // Render our text on a rectangle
    SDL_RenderCopy(renderer,textureText,NULL,&rectangle);
}