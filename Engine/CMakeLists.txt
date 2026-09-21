add_library(Engine)

target_sources(Engine PRIVATE
        src/Engine.cpp
        include/Engine.h
        src/Renderer.cpp
        include/Renderer.h
        include/Constants.h
        src/Actor.cpp
        src/Actor.cpp
        include/Actor.h
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
        src/CircleComponent.cpp
        include/CircleComponent.h
        src/AIComponent.cpp
        include/AIComponent.h
        src/AIState.cpp
        include/AIState.h
        src/NavComponent.cpp
        include/NavComponent.h
        src/InputSystem.cpp
        include/InputSystem.h
        src/CameraComponent.cpp
        include/CameraComponent.h
        src/SpriteVertexArray.cpp
        include/SpriteVertexArray.h
        src/Shader.cpp
        include/Shader.h
        src/Texture.cpp
        include/Texture.h
        src/VertexArray.cpp
        include/VertexArray.h
        src/Mesh.cpp
        include/Mesh.h
        src/MeshComponent.cpp
        include/MeshComponent.h
        src/FPSCamera.cpp
        include/FPSCamera.h
        src/FollowCamera.cpp
        include/FollowCamera.h
        src/Timer.cpp
        include/Timer.h
)

target_include_directories(Engine
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Engine PRIVATE ${LIBS})
