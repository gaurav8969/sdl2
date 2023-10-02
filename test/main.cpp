//on linux, compile with
//g++ -std=c++17  main.cpp glad/src/glad.c -I./glad/include -o prog -lSDL2 -ldl

//C++ standard libraries
#include <iostream>

//third party library
#include <SDL2/SDL.h>
#include <glad/glad.h>
int main(int argc, char* argv[]){
    //create a window data type
    SDL_Window* window;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not be initialized: " << SDL_GetError();
    }
    else {
        std::cout << "SDL video system is ready to go\n";
    }

    //set attributes for opengl window before opening it
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE); //core profile 
                                                                    //instead of compatibility
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1); //refresh twice as often
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24); //store colour in 24 bits
    window = SDL_CreateWindow("C++ SDL2 Window",
    500,300,640,480,SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    
    //create context for our window
    SDL_GLContext context;
    context = SDL_GL_CreateContext(window);

    //Setup our function pointers
    gladLoadGLLoader(SDL_GL_GetProcAddress);

    bool gameIsRunning = true;
    //avoid bad approach shown below, which terminates the program mid-frame
    /* while(gameIsRunning){
        SDL_Event event;
        SDL_PollEvent(&event);
        if(event.type == SDL_QUIT){
            gameIsRunning =  false;
        }
    }*/

    //approach that finishes the current frame first
    while(gameIsRunning){
        glViewport(0,0,640,480);
        SDL_Event event;

        //loop below handles the events one by one
        while(SDL_PollEvent(&event)){ //continue till the event queue is empty each time
            if(event.type == SDL_QUIT){
                gameIsRunning = false; //quit the game after this frame is over.
                std::cout << "Goodbye!\n";
            }
            if(event.type == SDL_KEYDOWN){
                std::cout << "a key has been pressed\n";
                if(event.key.keysym.sym == SDLK_m){
                    std::cout << "The key pressed is M!\n";
                }       
            }
            const Uint8* state = SDL_GetKeyboardState(NULL);
            if(state[SDL_SCANCODE_RIGHT]){
                std::cout << "right arrow key was pressed\n";
            }
        }

        glClearColor(1.0f,0.0f,0.0f,1.0f); //rgba colour-format
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        
        SDL_GL_SwapWindow(window);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}