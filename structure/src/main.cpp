//on linux, compile with
//g++ -std=c++17  -I include/ main.cpp src/*.cpp -o prog -lSDL2 -ldl

//C++ standard libraries
#include <iostream>
#include <string>
#include <memory>
#include <vector>
//third party library
#include <SDL2/SDL.h>

#include "TexturedRectangle.hpp"
#include "ResourceManager.hpp"
#include "SDLApp.hpp"
#include "GameEntity.hpp"
//so the callbacks can access them and work on them
//api users have to use global variables for now, refactor to factory design to circumvent
SDLApp* app; 
GameEntity* sprite1;
GameEntity* sprite2;

void handleEvents();
void handleRender();

int main(int argc, char* argv[]){
    app = new SDLApp("Collision Detection",500,300,640,480);
    sprite1 = new GameEntity(app->getRenderer(),"./assets/animatedSprite.bmp");
    sprite2 = new GameEntity(app->getRenderer(), "./assets/donkeyKong.bmp");
    sprite1->getRect().setPosition(200,200);
    sprite2->getRect().setPosition(100,100);
    
    app->setEventCallback(handleEvents);
    app->setRenderCallback(handleRender);
    app->runLoop();

    //free allocated memory
    delete sprite1;
    delete sprite2;
    delete app;
    return 0;
}

void handleEvents(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            app->stopRunLoop();
            std::cout << "Goodbye!\n";
        }

        int xPos,yPos; //mouse position
        SDL_GetMouseState(&xPos,&yPos);
        sprite2->getRect().setPosition(xPos,yPos);

        if(event.type == SDL_MOUSEBUTTONDOWN){
            if(event.button.button == SDL_BUTTON_LEFT){
                bool colliding = sprite2->isColliding(*sprite1);
                if(colliding){
                    std::cout <<"My function says there is a collision.\n";
                }
                else{
                    std::cout << "My function says there is no collision\n";
                }
            }
        }
    }
}

void handleRender(){
    SDL_SetRenderDrawColor(app->getRenderer(),0,0,255,SDL_ALPHA_OPAQUE);
    SDL_RenderClear(app->getRenderer());
    sprite1->render();
    sprite2->render();
    SDL_RenderPresent(app->getRenderer());
}