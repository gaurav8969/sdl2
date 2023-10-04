//on linux, compile with
//g++ -std=c++17  main.cpp -o prog -lSDL2 -ldl

//C++ standard libraries
#include <iostream>

//third party library
#include <SDL2/SDL.h>

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
    SDL_Surface* surface = SDL_LoadBMP("images/donkeyKong.bmp");
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,239,120,255));

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface); 

    bool gameIsRunning = true;
    while(gameIsRunning){
        SDL_Event event;

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                gameIsRunning = false; 
                std::cout << "Goodbye!\n";
            }
        }
        SDL_Rect uglyRectangle;
        uglyRectangle.x = 200;
        uglyRectangle.y = 200;
        uglyRectangle.w = 400;
        uglyRectangle.h = 400;
        //gives a clear canvas for every frame
        SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        
        //actual drawing
        SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(renderer,5,5,450,400);
        //SDL_RenderDrawRect(renderer,&uglyRectangle);
        //push the texture onto rendering target, eq. to updateWindowSurface for surfaces
        SDL_RenderCopy(renderer, texture, NULL, &uglyRectangle);

        //push the frame render to the window
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window); //free the memory the window pointer addresses
    SDL_Quit();
    return 0;
}