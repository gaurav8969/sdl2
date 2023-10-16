#!/bin/sh
g++ -std=c++17  -g -I ./include/ ./src/*.cpp -o ./bin/debug -lSDL2 -ldl