#include "Grid.hpp"
#include "Constants.hpp"
#include "Cross.hpp"
#include "Circle.hpp"

Grid::Grid(int cornerX, int cornerY){
    this->cornerX = cornerX;
    this->cornerY = cornerY;
    memset(board,-1, 9 *sizeof(int));
}

void Grid::draw(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer,GRID_COLOUR.x,GRID_COLOUR.y,
    GRID_COLOUR.z,SDL_ALPHA_OPAQUE);
    
    int verticalLines = 4;
    int horizontalLines = 4;
    int xLength = 3*GRID_SIZE;
    int yLength = xLength;

    int x = 0, y = 0;

    while(x < verticalLines || y < verticalLines){
        if(x < verticalLines){
            int xLine = cornerX + x*GRID_SIZE;
            SDL_RenderDrawLine(renderer, xLine,cornerY,xLine, cornerY + yLength);
            x++;
        }

        if(y < horizontalLines){
            int yLine = cornerY + y*GRID_SIZE;
            SDL_RenderDrawLine(renderer, cornerX, yLine, cornerX + xLength, yLine);
            y++;
        }
    }
}

void Grid::fill(SDL_Renderer* renderer){
    for(int i = 0; i < 9; i++){
        int row = i/3; //integer division
        int column = i%3; //modulo
        if(board[i] == 0){
            Circle::draw(renderer, cornerX+column*GRID_SIZE+2*FIT/3 ,cornerY+row*GRID_SIZE+FIT);
        }else if(board[i] == 1){
            Cross::draw(renderer, cornerX + column*GRID_SIZE +FIT, cornerY + row*GRID_SIZE +FIT);
        }
    }
}

void Grid::update(int position){
    
    if(!over){
        int index = position - 1;
        if(board[index] != -1){return;}
        if(turn == CROSS){
            board[index] = 1;
            turn = CIRCLE;
        }else{
            board[index] = 0;
            turn = CROSS;
        }

        if(isOver()){
            over = true;
        }
    }
    
}

bool Grid::isOver(){
    //checking for column
    for(int column = 0; column < 3; column++){
        int shape = query(0,column);
        if(shape == -1){continue;}

        //negate this if the column fails the check
        bool columnPassing = true;
        for(int row = 1; row < 3; row++){
            if(shape != query(row,column)){
                columnPassing = false;
                break;
            }
        }

        if(columnPassing == true){
            return true;
        }
    }

    //checking for rows
    for(int row = 0; row < 3; row++){
        int shape = query(row,0);
        if(shape == -1){continue;}

        //negate this if the row fails the check
        bool rowPassing = true;
        for(int column = 1; column < 3; column++){
            if(shape != query(row,column)){
                rowPassing = false;
                break;
            }
        }

        if(rowPassing == true){
            return true;
        }
    }

    //checking for diagonals
    int shape = query(1,1); //center element
    if(shape == -1){
        return false;
    }

    //first diagonal
    if(query(0,0) == shape && query(2,2) == shape){
        return true;
    }

    //second diagonal
    if(query(2,0) == shape && query(0,2) == shape){
        return true;
    }

    return false;
}

int Grid::query(int row, int column){
    int index = 3*row + column;
    return board[index];
}