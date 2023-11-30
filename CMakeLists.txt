cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

project(dungeon VERSION 1.0.0)

add_executable(dungeon
  src/engine/glad.c 
  src/engine/stb_image.h
  
  src/main.cpp
  src/engine/Engine.cpp
  src/engine/GameObject.cpp
  src/engine/Scene.cpp
  src/engine/Window.cpp
  src/engine/components/Component.cpp
  src/engine/components/Camera.cpp
  src/engine/components/Lifetime.cpp
  src/engine/components/Physics.cpp
  src/engine/components/renderers/RendererComponent.cpp
  src/engine/components/renderers/ShapeRenderer.cpp
  src/engine/components/renderers/SpriteRenderer.cpp
  src/engine/components/renderers/AnimatedSpriteRenderer.cpp
  src/engine/managers/AnimationManager.cpp
  src/engine/managers/ShaderManager.cpp
  src/engine/managers/SpriteManager.cpp
  src/engine/managers/InputManager.cpp
  src/engine/utils/Math.cpp
  src/engine/utils/Graphics.cpp
  src/engine/utils/Animation.cpp
  src/engine/utils/AnimationController.cpp
  src/engine/utils/io.cpp
  src/engine/utils/Mesh.cpp
  src/engine/utils/meshes.cpp
  src/engine/utils/Shader.cpp
  src/engine/utils/Texture.cpp

  src/game/scenes.cpp
  src/game/prefabs.cpp
  src/game/components/Spawner.cpp
  src/game/components/Shrink.cpp
)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

if (WIN32)
  target_link_libraries(dungeon PRIVATE 
    "${CMAKE_SOURCE_DIR}/dependencies/lib/libSDL2.a"
    imm32
    version
    setupapi
    winmm
  )

  target_include_directories(
    dungeon PRIVATE
    dependencies/include
    dependencies/include/SDL2
  )

  # set_target_properties(dungeon PROPERTIES LINK_FLAGS "-mwindows")
else()
  target_link_libraries(
    dungeon PRIVATE
    /Library/Frameworks/SDL2.framework/Versions/A/SDL2
  )

  target_include_directories(
    dungeon PRIVATE
    /Library/Frameworks/SDL2.framework/Versions/A/Headers
    dependencies/include
  )
endif()
