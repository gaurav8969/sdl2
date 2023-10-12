//on linux, compile with
//g++ -std=c++17  -I include/ main.cpp src/*.cpp -o prog -lSDL2 -ldl

//C++ standard libraries
#include <iostream>
#include <string>
#include <memory>
#include <vector>
//third party library
#include <SDL2/SDL.h>

#include "TexturedRectangle.hpp"
#include "ResourceManager.hpp"
#include "AnimateSprite.hpp"

int main(int argc, char* argv[]){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not be initialized: " << SDL_GetError();
    }
    else {
        std::cout << "SDL video system is ready to go\n";
    }

    SDL_Window* window = nullptr;
    window = SDL_CreateWindow("C++ SDL2 Window",
    500,300,640,480,SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    //Don't call delete on surface, managed by resource manager
    SDL_Surface* surface = ResourceManager::GetInstance().GetSurface("./assets/animatedSprite.bmp"); 
    /*^^for the above image path, remember that for compiled binaries, all relative paths are so
    to the dir you run the executable from, in our case it is the directory of the build script*/
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    AnimateSprite sprite;
    AnimateSprite sprite2;
    sprite.draw(0,0,250,250);
    sprite2.draw(200,200,250,250);

    int frameNo = 0;
    int frameNo2 = 0;
    bool gameIsRunning = true;
    while(gameIsRunning){
        SDL_Event event;

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                gameIsRunning = false; 
                std::cout << "Goodbye!\n";
            }
        }

        //gives a clear canvas for every frame
        SDL_SetRenderDrawColor(renderer,0,0,255,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
    
        //new drawing colour
        SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);

        sprite.setFrame(0,1,144,144,frameNo++); //sprite1
        if(frameNo > 4){
            frameNo = 0;
        }

        sprite2.setFrame(0,2,144,144,frameNo2++); //sprite2
        if(frameNo2 > 5){
            frameNo2 = 0;
        }

        sprite.render(renderer,texture);
        sprite2.render(renderer,texture);
        SDL_Delay(100);

        //push the frame render to the window
        SDL_RenderPresent(renderer);
    }

    //free allocated memory
    SDL_DestroyWindow(window); 

    SDL_Quit();
    return 0;
}