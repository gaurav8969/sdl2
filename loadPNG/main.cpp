//on linux, compile with
//g++ -std=c++17  main.cpp -o prog -lSDL2 -ldl -lSDL2_image

//C++ standard libraries
#include <iostream>

//third party library
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argc, char* argv[]){;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not be initialized: " << SDL_GetError();
    }
    else {
        std::cout << "SDL video system is ready to go\n";
    }

    int flags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_WEBP;
    int initStatus = IMG_Init(flags); //bit mask
    if ((flags&initStatus) != flags){ //mask operation
        std::cout << "SDL2_Image format not available" << std::endl; //couldn't initialize some formats
    }

    SDL_Window* window = nullptr;
    window = SDL_CreateWindow("C++ SDL2 Window",
    500,300,640,480,SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
 
    SDL_Surface* imageSurface = IMG_Load("/home/yash/Downloads/img/albertCamusAbsurd.jpg");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,imageSurface);
    SDL_FreeSurface(imageSurface);  
 
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

        SDL_RenderCopy(renderer,texture,NULL,NULL);
        //push the frame render to the window
        SDL_RenderPresent(renderer);
    }

    //free allocated memory
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window); 
    IMG_Quit();

    SDL_Quit();
    return 0;
}