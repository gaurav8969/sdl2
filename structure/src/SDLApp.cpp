//this class wraps around the SDL2 API, so as to not bog down the main function game logic
#include <iostream>
#include <exception>

#include "SDLApp.hpp"
//Third party libraries
#include "SDL2/SDL.h"

SDLApp::SDLApp(const char* title, int x, int y, int w, int h){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not be initialized: " << SDL_GetError();
        throw std::runtime_error("SDL video could not be initialized");
    }
    else {
        std::cout << "SDL video system is ready to go\n";
    }

    window = SDL_CreateWindow(title,x,y,w,h,SDL_WINDOW_SHOWN);
    if(!window){
        throw std::runtime_error("window not created");
    }

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if(!renderer){
        throw std::runtime_error("renderer not created");
    }

}

SDLApp::~SDLApp(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}

void SDLApp::setEventCallback(p_eventLoop func){
    eventLoop = func;
}

void SDLApp::setRenderCallback(p_renderLoop func){
    renderLoop = func;
}

void SDLApp::runLoop(){
    while(gameIsRunning){
        eventLoop();
        renderLoop();
    }
}

void SDLApp::stopRunLoop(){
    gameIsRunning = false;
}

SDL_Renderer* SDLApp::getRenderer(){
    return renderer;
}