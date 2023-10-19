
//C++ standard libraries
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <random>
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
    app = new SDLApp("Collision Detection",0,0,1280,720);
    sprite1 = new GameEntity(app->getRenderer(),"./assets/redBall.bmp");
    sprite2 = new GameEntity(app->getRenderer(), "./assets/cricketBat.bmp");
    sprite1->getRect().setPosition(200,200);
    sprite2->getRect().setPosition(100,100);
    
    app->setEventCallback(handleEvents);
    app->setRenderCallback(handleRender);
    app->setFrameCap(400);
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
    //dynamic but not concerned with any events, so in render callback
    static double xPos = 0;
    static double yPos = 0;
    static bool right = true;
    static bool down = true;
    static int windowWidth = app->getWindowWidth();
    static int windowHeight = app->getWindowHeight();
    static int minWindowWidth = app->getMinWindowWidth();
    static int minWindowHeight = app->getMinWindowHeight();

    static double time = 1.1 + (windowWidth - minWindowWidth)*0.00030;

    double deltaX = windowWidth/(app->getFramerate() * time);
    if(right){
        xPos = xPos + deltaX;
    }else{
        xPos = xPos - deltaX;
    }

    if(down){
        yPos = yPos + deltaX/2;
    }
    else{
        yPos = yPos - deltaX/2;
    }

    if(xPos >= windowWidth){
        right = false;
    }
    else if(xPos <= 0){
        right = true;
    }


    if(yPos >= windowHeight){
        down = false;
    }
    else if(yPos <= 0){
        down = true;
    }

    sprite1->getRect().setPosition(xPos,yPos);
    sprite1->render();
    sprite2->render();
}