#ifndef SDL_APP_HPP
#define SDL_APP_HPP
#include <functional>
#include "SDL2/SDL.h"

class SDLApp{
    typedef std::function<void(void)> p_eventLoop;
    typedef std::function<void(void)> p_renderLoop;
    
    public:
    SDLApp()= delete;
    SDLApp(const char* title, int x, int y, int w, int h);
    ~SDLApp();

    void setEventCallback(p_eventLoop);
    void setRenderCallback(p_renderLoop);
    void runLoop();
    void stopRunLoop();
    SDL_Renderer* getRenderer();

    private:
    SDL_Renderer* renderer;
    SDL_Window* window;
    p_eventLoop eventLoop;
    p_renderLoop renderLoop;
    bool gameIsRunning = true;

};

#endif