//on linux, compile with
//g++ -std=c++17  main.cpp -o prog -lSDL2 -ldl

//C++ standard libraries
#include <iostream>

//third party library
#include <SDL2/SDL.h>
void setPixel(SDL_Surface*, int ,int ,uint8_t ,uint8_t ,uint8_t );
int main(int argc, char* argv[]){
    //create a window data type
    SDL_Window* window = nullptr;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not be initialized: " << SDL_GetError();
    }
    else {
        std::cout << "SDL video system is ready to go\n";
    }

    //Grab the window surface
    SDL_Surface* screen;
    
    window = SDL_CreateWindow("C++ SDL2 Window",
    500,300,640,480,SDL_WINDOW_SHOWN);

    screen = SDL_GetWindowSurface(window);    

    bool gameIsRunning = true;
    while(gameIsRunning){
        SDL_Event event;

        int x,y;
        Uint32 buttons;
        buttons = SDL_GetMouseState(&x,&y);
        //loop below handles the events one by one
        while(SDL_PollEvent(&event)){ //continue till the event queue is empty each time
            if(event.type == SDL_QUIT){
                gameIsRunning = false; //quit the game after this frame is over.
                std::cout << "Goodbye!\n";
            }
            if (event.button.button == SDL_BUTTON_LEFT){
                setPixel(screen,x,y,255,0,0);
                std::cout << "left mouse was pressed (" << x <<","<<y <<")\n";
            }
            if (event.button.button == SDL_BUTTON_RIGHT){
                setPixel(screen,x,y,0,255,0);
                std::cout << "right mouse was pressed (" << x <<","<<y <<")\n";
            }
            if (event.button.button == SDL_BUTTON_MIDDLE){
                setPixel(screen,x,y,0,0,255);
                std::cout << "middle mouse was pressed (" << x <<","<<y <<")\n";
            }
        }
        SDL_UpdateWindowSurface(window);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

//works on any kind of surface
void setPixel(SDL_Surface* surface, int x,int y, uint8_t r, uint8_t g, uint8_t b){
    SDL_LockSurface(surface);
    uint8_t* pixelArray = (uint8_t*)surface->pixels;//typecasting null to access it
    pixelArray[y*surface->pitch + x*surface->format->BytesPerPixel + 0] = b;
    pixelArray[y*surface->pitch + x*surface->format->BytesPerPixel + 1] = g;
    pixelArray[y*surface->pitch + x*surface->format->BytesPerPixel + 2] = r;
    SDL_UnlockSurface(surface);
}