cmake_minimum_required(VERSION 4.3)
project(clion_game_programming)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

add_executable(${PROJECT_NAME} main.cpp
        include/Game.h
        src/Game.cpp
        include/Constants.h
        include/Actor.h
        src/Actor.cpp
        include/Component.h
        src/Component.cpp
        include/SpriteComponent.h
        src/SpriteComponent.cpp
        include/Math.h
        src/Math.cpp
        include/AnimSpriteComponent.h
        src/AnimSpriteComponent.cpp
        include/BGSpriteComponent.h
        src/BGSpriteComponent.cpp)

file(
        DOWNLOAD
        https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.43.1/CPM.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
        EXPECTED_HASH SHA256=1c40fc102ce9625d7de7eb14f541cab30cc3138dca627f0b0ec40293ce6c2934
)
include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

set(LIBS)

# SDL
CPMAddPackage("gh:libsdl-org/SDL#147a8ee")
list(APPEND LIBS SDL3::SDL3)

CPMAddPackage("gh:libsdl-org/SDL_image#bec9134")
list(APPEND LIBS SDL3_image::SDL3_image)

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})
