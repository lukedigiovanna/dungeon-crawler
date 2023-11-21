cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

project(dungeon VERSION 1.0.0)

add_executable(dungeon 
    src/main.cpp
    src/engine/Engine.cpp
    src/engine/GameObject.cpp
    src/engine/Scene.cpp
    src/engine/Window.cpp
    src/engine/components/Component.cpp
    src/engine/components/Camera.cpp
    src/engine/components/Lifetime.cpp
    src/engine/components/RendererComponent.cpp
    src/engine/components/ShapeRenderer.cpp
    src/engine/components/SpriteRenderer.cpp
    src/engine/utils/Math.cpp
    src/engine/utils/Graphics.cpp

    src/game/Scenes.cpp
    src/game/components/Spawner.cpp
)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(
  dungeon PRIVATE
  /Library/Frameworks/SDL2.framework/Versions/A/SDL2
  /Library/Frameworks/SDL2_image.framework/Versions/A/SDL2_image
#   /Library/Frameworks/SDL2_ttf.framework/Versions/A/SDL2_ttf
)

target_include_directories(
  dungeon PRIVATE
  /Library/Frameworks/SDL2.framework/Versions/A/Headers
  /Library/Frameworks/SDL2_image.framework/Versions/A/Headers
#   /Library/Frameworks/SDL2_ttf.framework/Versions/A/Headers
)