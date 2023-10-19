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
    void setFrameCap(int framecap);
    int getWindowWidth();
    int getWindowHeight();
    int getMinWindowWidth();
    int getMinWindowHeight();
    double getFramerate();

    private:
    SDL_Renderer* m_renderer;
    SDL_Window* window;
    p_eventLoop eventLoop;
    p_renderLoop renderLoop;
    bool gameIsRunning = true;
    int m_windowWidth;
    int m_windowHeight;
    int m_minWindowWidth;
    int m_minWindowHeight;
    int m_framecap;
    double m_waittime;
    double m_framerate;
    bool isFramerateCapped;
};

#endif