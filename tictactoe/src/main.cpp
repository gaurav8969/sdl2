#include <iostream>

#include "SDLApp.hpp"
#include "Circle.hpp"
#include "Cross.hpp"
#include "Grid.hpp"
#include "Constants.hpp"
#include "Text.hpp"

void handleEvents();
void handleRender();
Cross* cross;
Circle* circle;
Grid* grid;
SDLApp* app;
Text* text;

int over = -1;

int main(){
    cross = new Cross();
    circle = new Circle();    
    grid = new Grid(245,135);

    app = new SDLApp("Tic-Tac-Toe", 400,300,800,640);
    app->setFrameCap(120);
    app->setEventCallback(handleEvents);
    app->setRenderCallback(handleRender);
    app->runLoop();

    delete cross;
    delete circle;
    delete grid;
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

        const Uint8* state = SDL_GetKeyboardState(NULL);
        if(state[SDL_SCANCODE_1]){
            grid->update(1);
        }else if(state[SDL_SCANCODE_2]){
            grid->update(2);
        }else if(state[SDL_SCANCODE_3]){
            grid->update(3);
        }else if(state[SDL_SCANCODE_4]){
            grid->update(4);
        }else if(state[SDL_SCANCODE_5]){
            grid->update(5);
        }else if(state[SDL_SCANCODE_6]){
            grid->update(6);
        }else if(state[SDL_SCANCODE_7]){
            grid->update(7);
        }else if(state[SDL_SCANCODE_8]){
            grid->update(8);
        }else if(state[SDL_SCANCODE_9]){
            grid->update(9);
        }

    }
}

void handleRender(){
    grid->draw(app->getRenderer());
    grid->fill(app->getRenderer());
    if(grid->gameOver()){
        if(over < 0){
            //must be the turn of whoever lost, so  we flip it to get the winner
            int shape = grid->whoWon();
            text = new Text(app->getRenderer(), shape);
            std::cout << "Is over!" << std::endl;
            over++;
        }
        text->render();
    }
}