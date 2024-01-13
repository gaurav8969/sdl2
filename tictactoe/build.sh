#!/bin/sh
g++ -std=c++17  -I ./include/ -I ./include/draw -I ./include/SDL ./src/*.cpp ./src/draw/*.cpp ./src/SDL/*.cpp -o ./build/prog -lSDL2 -ldl -lSDL2_ttf