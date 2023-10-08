//on linux, compile with
//g++ -std=c++17  main.cpp -o prog -lSDL2 -ldl -lttf

//C++ standard libraries
#include <iostream>

//third party library
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

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

    if(TTF_Init() == -1){
        std::cout << "Could not initialize SDL2 ttf, error: " << TTF_GetError() << std::endl;
    }else {
        std::cout << "SDL2_ttf system ready to go!" << std::endl;
    }

    TTF_Font* ourFont = TTF_OpenFont("/home/yash/Downloads/fonts/8bitOperatorPlus8-Regular.ttf",32);
    if(ourFont == nullptr){
        std::cout << "Could not load font" << std::endl;
        exit(1);
    }

    SDL_Surface* surfaceText = TTF_RenderText_Solid(ourFont, "Gaurav Tiwari",{255,255,0});
    SDL_Texture* textureText = SDL_CreateTextureFromSurface(renderer,surfaceText);
    SDL_FreeSurface(surfaceText);  

    //create a rectangle to draw on
    SDL_Rect rectangle;
    rectangle.x = 10;
    rectangle.y = 10;
    rectangle.w = 400;
    rectangle.h = 100;

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

        SDL_RenderCopy(renderer,textureText,NULL,&rectangle);
        //push the frame render to the window
        SDL_RenderPresent(renderer);
    }
    //free allocate memory
    SDL_DestroyTexture(textureText);
    SDL_DestroyWindow(window); 
    TTF_CloseFont(ourFont);

    SDL_Quit();
    return 0;
}