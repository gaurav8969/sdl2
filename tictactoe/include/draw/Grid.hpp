#ifndef GRID_HPP
#define GRID_HPP

#include "SDL2/SDL.h"

class Grid{
    static int const CIRCLE = 0;
    static int const CROSS = 1;
public:
    //left-corner
    Grid(int cornerX, int cornerY);
    void draw(SDL_Renderer* renderer);
    void fill(SDL_Renderer* renderer);
    void update(int position);
    bool gameOver(){return over;}
    int whoWon(){return won;}
private:
    bool isOver();
    bool isFilled();
    int won= -1;
    //query shape at any some particular row and column
    int query(int row, int column);
    int cornerX = 100, cornerY = 100;
    int board[9];
    int turn = CIRCLE;
    bool over = false;
};

#endif