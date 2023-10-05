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
    SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_ADD);
    SDL_FreeSurface(surface); 


    SDL_Rect uglyRectangle;
    uglyRectangle.x = 200;
    uglyRectangle.y = 200;
    uglyRectangle.w = 400;
    uglyRectangle.h = 400;

    SDL_Rect prettyRectangle;
    prettyRectangle.x = 200;
    prettyRectangle.y = 200;
    prettyRectangle.w = 400;
    prettyRectangle.h = 400;

    bool gameIsRunning = true;
    while(gameIsRunning){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                gameIsRunning = false; 
                std::cout << "Goodbye!\n";
            }

            if(event.type == SDL_MOUSEMOTION){ //update position every frame of game loop
                prettyRectangle.x = event.motion.x;
                prettyRectangle.y = event.motion.y;
            }

            if(event.type == SDL_MOUSEBUTTONDOWN){
                if(event.button.button == SDL_BUTTON_RIGHT){
                    uglyRectangle.x = 0;
                    uglyRectangle.y = 0;
                    std::cout << "right mouse was clicked\n";
                    SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_ADD);
                }
                else if(event.button.button == SDL_BUTTON_LEFT){
                    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_MOD);
                    std::cout << "left mouse was clicked\n";
                }
            }
            if(event.type == SDL_MOUSEBUTTONUP){
                SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_NONE);
            }
        }

        //gives a clear canvas for every frame
        SDL_SetRenderDrawColor(renderer,0,0,255,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        
        //actual drawing
        SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(renderer,5,5,450,400);
        //SDL_RenderDrawRect(renderer,&uglyRectangle);

        //push the texture onto rendering target, eq. to updateWindowSurface for surfaces
        SDL_RenderCopy(renderer, texture, NULL, &uglyRectangle);
        SDL_RenderCopy(renderer, texture, NULL, &prettyRectangle);
        //push the frame render to the window
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window); //free the memory the window pointer addresses
    SDL_Quit();
    return 0;
}