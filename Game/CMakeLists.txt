#add_library(Game)
target_sources(
        ${PROJECT_NAME} PRIVATE
            Code/Ship.cpp
            Code/Ship.h
            Code/Skeleton.cpp
            Code/Skeleton.h
            Code/TileMap.cpp
            Code/TileMap.h
            Code/Asteroid.cpp
            Code/Asteroid.h
            Code/Laser.cpp
            Code/Laser.h
            Code/Tile.cpp
            Code/Tile.h
            Code/Grid.cpp
            Code/Grid.h
            Code/Tower.cpp
            Code/Tower.h
            Code/Enemy.cpp
            Code/Enemy.h
            Code/Bullet.cpp
            Code/Bullet.h
            Code/Dot.cpp
            Code/Dot.h
)
#target_include_directories(Game INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})