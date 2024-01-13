cmake_minimum_required(VERSION 3.5)
project(Experiment
        VERSION 0.0.1
        DESCRIPTION "tic-tac-toe using sdl2"
        LANGUAGES CXX)

MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list *.hpp)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()
    
HEADER_DIRECTORIES(header_list)
include_directories(${header_list})

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)
SET(CMAKE_BUILD_TYPE Debug)
SET(EXEC "prog")

#GLOBING
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

add_executable(${EXEC} ${SOURCE_FILES})

find_package(SDL2 REQUIRED)
find_package(SDL2TTF)
include_directories(${SDL2_INCLUDE_DIRS})

target_link_libraries(${EXEC} ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARY})
