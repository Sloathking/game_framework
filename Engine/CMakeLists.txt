add_library(Engine)

target_sources(Engine PRIVATE
        src/Engine.cpp
        include/Engine.h
        include/Constants.h
        src/Actor.cpp
        include/Actor.h
        src/Actor2D.cpp
        include/Actor2D.h
        src/Component.cpp
        include/Component.h
        src/SpriteComponent.cpp
        include/SpriteComponent.h
        src/Math.cpp
        include/Math.h
        src/AnimSpriteComponent.cpp
        include/AnimSpriteComponent.h
        src/BGSpriteComponent.cpp
        include/BGSpriteComponent.h
        src/Tile.cpp
        include/Tile.h
        src/TileMapComponent.cpp
        include/TileMapComponent.h
        include/CSVUtils.h
        src/MoveComponent.cpp
        include/MoveComponent.h
        src/Random.cpp
        include/Random.h
        src/InputComponent.cpp
        include/InputComponent.h
        src/CircleComponent.cpp
        include/CircleComponent.h
        src/AIComponent.cpp
        include/AIComponent.h
        src/AIState.cpp
        include/AIState.h
        src/NavComponent.cpp
        include/NavComponent.h
        src/PhysicsMoveComponent.cpp
        include/PhysicsMoveComponent.h
        src/PhysicsInputComponent.cpp
        include/PhysicsInputComponent.h
        src/InputSystem.cpp
        include/InputSystem.h
        src/CameraComponent.cpp
        include/CameraComponent.h
        src/VertexArray.cpp
        include/VertexArray.h
        src/Shader.cpp
        include/Shader.h
        src/Texture.cpp
        include/Texture.h
)

target_include_directories(Engine
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Engine PRIVATE ${LIBS})
