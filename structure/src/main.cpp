//on linux, compile with
//g++ -std=c++17  -I include/ main.cpp src/*.cpp -o prog -lSDL2 -ldl

//C++ standard libraries
#include <iostream>
#include <string>
#include <memory>
#include <vector>
//third party library
#include <SDL2/SDL.h>

#include "../include/TexturedRectangle.hpp"

int main(int argc, char* argv[]){;
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

    TexturedRectangle rectangle2(renderer, "/home/yash/repos/sdl2/abstractShapes/images/waterTexture.bmp");
    rectangle2.setRectangleProperties(300,0,200,200);

    std::vector<std::unique_ptr<TexturedRectangle>>rects;

    for(int i = 0; i < 34; i++){
        std::unique_ptr<TexturedRectangle> rect = std::make_unique<TexturedRectangle>(renderer,"/home/yash/repos/sdl2/abstractShapes/images/waterTexture.bmp");
        rects.push_back(std::move(rect)); //move assignment operator invoked
    }

    int rectPos = 10; 
    for(auto& rect:rects){
        rectPos *= 1.1;
        rect->setRectangleProperties(rectPos,rectPos,rectPos,rectPos*2);
    }

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
        
        //actual drawing
        SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);

        //push the frame render to the window
        for(const auto& rect: rects){
            rect->render();
        }
        SDL_RenderPresent(renderer);
    }

    //free allocated memory
    SDL_DestroyWindow(window); 

    SDL_Quit();
    return 0;
}