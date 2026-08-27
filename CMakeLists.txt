cmake_minimum_required(VERSION 4.3)
project(game_framework)

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
        Game/Skeleton.h
        Engine/src/TileMapComponent.cpp
        Engine/include/TileMapComponent.h
        Engine/include/CSVUtils.h
        Game/TileMap.cpp
        Game/TileMap.h
        Engine/src/MoveComponent.cpp
        Engine/include/MoveComponent.h
        Game/Asteroid.cpp
        Game/Asteroid.h
        Engine/src/Random.cpp
        Engine/include/Random.h
        Engine/src/InputComponent.cpp
        Engine/include/InputComponent.h
        Engine/src/CircleComponent.cpp
        Engine/include/CircleComponent.h
        Game/Laser.cpp
        Game/Laser.h
        Engine/src/AIComponent.cpp
        Engine/include/AIComponent.h
        Engine/src/AIState.cpp
        Engine/include/AIState.h
        Engine/src/NavComponent.cpp
        Engine/include/NavComponent.h
        Game/Tile.cpp
        Game/Tile.h
        Game/Grid.cpp
        Game/Grid.h
        Game/Tower.cpp
        Game/Tower.h
        Game/Enemy.cpp
        Game/Enemy.h
        Game/Bullet.cpp
        Game/Bullet.h
        Engine/src/PhysicsMoveComponent.cpp
        Engine/include/PhysicsMoveComponent.h
        Engine/src/PhysicsInputComponent.cpp
        Engine/include/PhysicsInputComponent.h
        Engine/src/InputSystem.cpp
        Engine/include/InputSystem.h
        Game/Dot.cpp
        Game/Dot.h
        Engine/src/CameraComponent.cpp
        Engine/include/CameraComponent.h
)

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

set(SDLTTF_VENDORED ON)
CPMAddPackage("gh:libsdl-org/SDL_ttf#a1ce367")
list(APPEND LIBS SDL3_ttf::SDL3_ttf)

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})
