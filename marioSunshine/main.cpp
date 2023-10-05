//on linux, compile with
//g++ -std=c++17  main.cpp -o prog -lSDL2 -ldl

//C++ standard libraries
#include <iostream>

//third party library
#include <SDL2/SDL.h>

int main(int argc, char* argv[]){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not be initialized: " << SDL_GetError();
    }
    else {
        std::cout << "SDL video system is ready to go\n";
    }

    SDL_Window* window = nullptr;
    window = SDL_CreateWindow("C++ SDL2 Window",
    300,300,640,480,SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    SDL_Surface* surface = SDL_LoadBMP("./images/waterTexture.bmp");

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface); //BG texture
    SDL_Texture* textureBlend = SDL_CreateTextureFromSurface(renderer,surface); //FG texture
    SDL_SetTextureBlendMode(textureBlend,SDL_BLENDMODE_MOD);
    SDL_FreeSurface(surface); 

    SDL_Rect horizontalFormer;
    horizontalFormer.x = 0;
    horizontalFormer.y = 0;
    horizontalFormer.w = 640;
    horizontalFormer.h = 480;

    SDL_Rect horizontalLatter;
    horizontalLatter.x = -639;
    horizontalLatter.y = 0;
    horizontalLatter.w = 640;
    horizontalLatter.h = 480;

    SDL_Rect verticalFormer;
    verticalFormer.x = 0;
    verticalFormer.y = 0;
    verticalFormer.w = 640;
    verticalFormer.h = 480;

    SDL_Rect verticalLatter;
    verticalLatter.x = 0;
    verticalLatter.y = -480;
    verticalLatter.w = 640;
    verticalLatter.h = 480;

    bool gameIsRunning = true;
    while(gameIsRunning){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                gameIsRunning = false; 
                std::cout << "Goodbye!\n";
            }

            if(event.type == SDL_MOUSEBUTTONDOWN){
                if(event.button.button == SDL_BUTTON_RIGHT){
                    std::cout << "right mouse was clicked\n";
                    SDL_SetTextureBlendMode(textureBlend,SDL_BLENDMODE_MOD);
                }
                else if(event.button.button == SDL_BUTTON_LEFT){
                    SDL_SetTextureBlendMode(textureBlend, SDL_BLENDMODE_ADD);
                    std::cout << "left mouse was clicked\n";
                }
                else {
                    SDL_SetTextureBlendMode(textureBlend, SDL_BLENDMODE_NONE);
                    std::cout << "middle mouse!";
                }
            }
        }

        SDL_SetRenderDrawColor(renderer,0,0,255,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        int w,h;
        SDL_QueryTexture(texture,NULL,NULL,&w,&h);
        SDL_Delay(20);

        horizontalFormer.x++;
        if(horizontalFormer.x > 639){
           horizontalFormer.x = -639; 
        }

        horizontalLatter.x++;
        if(horizontalLatter.x > 639){
            horizontalLatter.x = -639;
        }

        verticalFormer.y++;
        if (verticalFormer.y > 479){
            verticalFormer.y = -480;
        }

        verticalLatter.y++;
        if (verticalLatter.y > 479){
            verticalLatter.y = -480;
        }
        
        SDL_RenderCopy(renderer, texture, NULL, &horizontalFormer);
        SDL_RenderCopy(renderer, texture, NULL, &horizontalLatter);
        SDL_RenderCopy(renderer, textureBlend, NULL, &verticalFormer);
        SDL_RenderCopy(renderer, textureBlend, NULL, &verticalLatter);

        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}