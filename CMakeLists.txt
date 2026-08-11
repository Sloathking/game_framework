cmake_minimum_required(VERSION 4.3)
project(clion_game_programming)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

add_executable(${PROJECT_NAME} main.cpp
        Engine/include/Game.h
        Engine/src/Game.cpp
        Engine/include/Constants.h
        Engine/include/Actor.h
        Engine/src/Actor.cpp
        Engine/include/Component.h
        Engine/src/Component.cpp
        Engine/include/SpriteComponent.h
        Engine/src/SpriteComponent.cpp
        Engine/include/Math.h
        Engine/src/Math.cpp
        Engine/include/AnimSpriteComponent.h
        Engine/src/AnimSpriteComponent.cpp
        Engine/include/BGSpriteComponent.h
        Engine/src/BGSpriteComponent.cpp
        Game/Ship.cpp
        Game/Ship.h
        Game/Skeleton.cpp
        Game/Skeleton.h)

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
