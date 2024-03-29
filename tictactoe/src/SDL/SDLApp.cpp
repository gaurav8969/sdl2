//this class wraps around the SDL2 API, so as to not bog down the main function game logic
#include <iostream>
#include <exception>

//Third party libraries
#include "SDL2/SDL.h"

#include "SDLApp.hpp"
#include "Constants.hpp"

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

    m_renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if(!m_renderer){
        throw std::runtime_error("renderer not created");
    }

    m_windowWidth = w;
    m_windowHeight = h;
    m_minWindowWidth = 480;
    m_minWindowHeight = 360;
    m_framerate = 120; //intial value 
    SDL_SetWindowMinimumSize(window,m_minWindowWidth,m_minWindowHeight);
    isFramerateCapped = false;
}

SDLApp::~SDLApp(){
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(window);
    window = nullptr;
    m_renderer = nullptr;
}

void SDLApp::setEventCallback(p_eventLoop func){
    eventLoop = func;
}

void SDLApp::setRenderCallback(p_renderLoop func){
    renderLoop = func;
}

void SDLApp::runLoop(){
    while(gameIsRunning){
        Uint64 start = SDL_GetTicks();
        eventLoop();

        SDL_SetRenderDrawColor(m_renderer,BACKGROUND_COLOUR.x,BACKGROUND_COLOUR.y,
        BACKGROUND_COLOUR.z,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(m_renderer);
        renderLoop();
        SDL_RenderPresent(m_renderer);
        Uint64 end = SDL_GetTicks();
        double timeElapsed = end - start;
        if(isFramerateCapped && (timeElapsed < m_waittime)){
            SDL_Delay(m_waittime - timeElapsed);
        }
        m_framerate = 1000.0/(SDL_GetTicks()-start); //actual framerate inclusive of the delay
    }
}

void SDLApp::stopRunLoop(){
    gameIsRunning = false;
}

SDL_Renderer* SDLApp::getRenderer(){
    return m_renderer;
}

void SDLApp::setFrameCap(int framecap){
    isFramerateCapped = true;
    m_framecap = framecap;
    m_waittime = 1000.0/framecap;
}

int SDLApp::getWindowWidth(){
    return m_windowWidth;   
}

int SDLApp::getWindowHeight(){
    return m_windowHeight;
}

int SDLApp::getMinWindowWidth(){
    return m_minWindowWidth;
}

int SDLApp::getMinWindowHeight(){
    return m_minWindowHeight;
}

double SDLApp::getFramerate(){
    return m_framerate;
}
