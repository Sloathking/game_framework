add_library(Game)

target_sources( Game PRIVATE
        Code/Game.cpp
        Code/Game.h
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

target_include_directories(Game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Code)

target_link_libraries(Game PRIVATE ${LIBS})

target_link_libraries(Game PUBLIC Engine)
