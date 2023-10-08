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
 
    SDL_Surface* surface = SDL_LoadBMP("/home/yash/repos/sdl2/template/images/donkeyKong.bmp");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);  
 
    //create a rectangle to draw on
    SDL_Rect rectangle;
    rectangle.x = 10;
    rectangle.y = 10;
    rectangle.w = 400;
    rectangle.h = 400;

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

        SDL_RenderCopy(renderer,texture,NULL,&rectangle);
        //push the frame render to the window
        SDL_RenderPresent(renderer);
    }

    //free allocated memory
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window); 

    SDL_Quit();
    return 0;
}