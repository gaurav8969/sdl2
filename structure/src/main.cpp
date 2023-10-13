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

    int frameNo = 0;
    int frameNo2 = 0;
    bool gameIsRunning = true;


    TexturedRectangle rectangleOne(renderer,"./assets/animatedSprite.bmp");
    TexturedRectangle rectangleSecond(renderer, "./assets/donkeyKong.bmp");
    rectangleOne.setRectangleProperties(100,100,200,200);
    rectangleSecond.setRectangleProperties(200,200,200,200);
    
    while(gameIsRunning){
        SDL_Event event;

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                gameIsRunning = false; 
                std::cout << "Goodbye!\n";
            }
            
            int xPos,yPos; //mouse position
            SDL_GetMouseState(&xPos,&yPos);
            rectangleSecond.setRectanglePosition(xPos,yPos);

            if(event.type == SDL_MOUSEBUTTONDOWN){
                if(event.button.button == SDL_BUTTON_LEFT){
                    bool colliding = rectangleSecond.isColliding(rectangleOne);
                    if(colliding){
                        std::cout <<"My function says there is a collision.\n";
                    }
                    else{
                        std::cout << "My function says there is no collision\n";
                    }
                }
            }
        }
        
        SDL_SetRenderDrawColor(renderer,0,0,255,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        rectangleOne.render();
        rectangleSecond.render();

        SDL_RenderPresent(renderer);
    }

    //free allocated memory
    SDL_DestroyWindow(window); 
    SDL_Quit();
    return 0;
}