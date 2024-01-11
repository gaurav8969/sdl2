cmake_minimum_required(VERSION 3.5)
project(Experiment
        VERSION 0.0.1
        DESCRIPTION "First attempt at cmake"
        LANGUAGES CXX)  

SET(CMAKE_BUILD_TYPE Debug)

SET(EXEC "prog")

#GLOBING
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

add_executable(${EXEC} ${SOURCE_FILES})
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${EXEC} ${SDL2_LIBRARIES})

target_compile_features(${EXEC} PRIVATE cxx_std_20)
target_include_directories(prog PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)