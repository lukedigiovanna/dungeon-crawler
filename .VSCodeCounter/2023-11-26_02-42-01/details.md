# Details

Date : 2023-11-26 02:42:01

Directory /Users/lukedigiovanna/Programming/cpp/dungeon-crawler

Total : 66 files,  1452 codes, 136 comments, 444 blanks, all 2032 lines

[Summary](results.md) / Details / [Diff Summary](diff.md) / [Diff Details](diff-details.md)

## Files
| filename | language | code | comment | blank | total |
| :--- | :--- | ---: | ---: | ---: | ---: |
| [CMakeLists.txt](/CMakeLists.txt) | CMake | 51 | 2 | 8 | 61 |
| [README.md](/README.md) | Markdown | 4 | 0 | 2 | 6 |
| [assets/shaders/fs.glsl](/assets/shaders/fs.glsl) | GLSL | 10 | 4 | 8 | 22 |
| [assets/shaders/vs.glsl](/assets/shaders/vs.glsl) | GLSL | 13 | 1 | 7 | 21 |
| [run.sh](/run.sh) | Shell Script | 8 | 0 | 1 | 9 |
| [src/engine/Engine.cpp](/src/engine/Engine.cpp) | C++ | 72 | 21 | 28 | 121 |
| [src/engine/Engine.h](/src/engine/Engine.h) | C++ | 28 | 2 | 11 | 41 |
| [src/engine/GameObject.cpp](/src/engine/GameObject.cpp) | C++ | 52 | 0 | 13 | 65 |
| [src/engine/GameObject.h](/src/engine/GameObject.h) | C++ | 48 | 1 | 12 | 61 |
| [src/engine/Scene.cpp](/src/engine/Scene.cpp) | C++ | 54 | 10 | 18 | 82 |
| [src/engine/Scene.h](/src/engine/Scene.h) | C++ | 27 | 1 | 11 | 39 |
| [src/engine/Window.cpp](/src/engine/Window.cpp) | C++ | 23 | 0 | 6 | 29 |
| [src/engine/Window.h](/src/engine/Window.h) | C++ | 20 | 0 | 4 | 24 |
| [src/engine/components/Camera.cpp](/src/engine/components/Camera.cpp) | C++ | 57 | 9 | 15 | 81 |
| [src/engine/components/Camera.h](/src/engine/components/Camera.h) | C++ | 17 | 0 | 5 | 22 |
| [src/engine/components/Component.cpp](/src/engine/components/Component.cpp) | C++ | 17 | 2 | 6 | 25 |
| [src/engine/components/Component.h](/src/engine/components/Component.h) | C++ | 14 | 1 | 5 | 20 |
| [src/engine/components/Lifetime.cpp](/src/engine/components/Lifetime.cpp) | C++ | 13 | 0 | 6 | 19 |
| [src/engine/components/Lifetime.h](/src/engine/components/Lifetime.h) | C++ | 17 | 1 | 5 | 23 |
| [src/engine/components/Physics.cpp](/src/engine/components/Physics.cpp) | C++ | 14 | 2 | 4 | 20 |
| [src/engine/components/Physics.h](/src/engine/components/Physics.h) | C++ | 11 | 0 | 4 | 15 |
| [src/engine/components/renderers/AnimatedSpriteRenderer.cpp](/src/engine/components/renderers/AnimatedSpriteRenderer.cpp) | C++ | 9 | 0 | 7 | 16 |
| [src/engine/components/renderers/AnimatedSpriteRenderer.h](/src/engine/components/renderers/AnimatedSpriteRenderer.h) | C++ | 11 | 0 | 5 | 16 |
| [src/engine/components/renderers/RendererComponent.cpp](/src/engine/components/renderers/RendererComponent.cpp) | C++ | 21 | 0 | 12 | 33 |
| [src/engine/components/renderers/RendererComponent.h](/src/engine/components/renderers/RendererComponent.h) | C++ | 15 | 0 | 6 | 21 |
| [src/engine/components/renderers/ShapeRenderer.cpp](/src/engine/components/renderers/ShapeRenderer.cpp) | C++ | 8 | 3 | 6 | 17 |
| [src/engine/components/renderers/ShapeRenderer.h](/src/engine/components/renderers/ShapeRenderer.h) | C++ | 15 | 0 | 4 | 19 |
| [src/engine/components/renderers/SpriteRenderer.cpp](/src/engine/components/renderers/SpriteRenderer.cpp) | C++ | 14 | 5 | 5 | 24 |
| [src/engine/components/renderers/SpriteRenderer.h](/src/engine/components/renderers/SpriteRenderer.h) | C++ | 13 | 0 | 3 | 16 |
| [src/engine/managers/AnimationManager.cpp](/src/engine/managers/AnimationManager.cpp) | C++ | 16 | 0 | 4 | 20 |
| [src/engine/managers/AnimationManager.h](/src/engine/managers/AnimationManager.h) | C++ | 12 | 0 | 4 | 16 |
| [src/engine/managers/InputManager.cpp](/src/engine/managers/InputManager.cpp) | C++ | 44 | 0 | 7 | 51 |
| [src/engine/managers/InputManager.h](/src/engine/managers/InputManager.h) | C++ | 18 | 0 | 6 | 24 |
| [src/engine/managers/Managers.h](/src/engine/managers/Managers.h) | C++ | 12 | 2 | 3 | 17 |
| [src/engine/managers/ShaderManager.cpp](/src/engine/managers/ShaderManager.cpp) | C++ | 19 | 0 | 5 | 24 |
| [src/engine/managers/ShaderManager.h](/src/engine/managers/ShaderManager.h) | C++ | 12 | 0 | 4 | 16 |
| [src/engine/managers/SpriteManager.cpp](/src/engine/managers/SpriteManager.cpp) | C++ | 62 | 15 | 8 | 85 |
| [src/engine/managers/SpriteManager.h](/src/engine/managers/SpriteManager.h) | C++ | 17 | 1 | 6 | 24 |
| [src/engine/utils/Animation.cpp](/src/engine/utils/Animation.cpp) | C++ | 39 | 0 | 13 | 52 |
| [src/engine/utils/Animation.h](/src/engine/utils/Animation.h) | C++ | 26 | 0 | 6 | 32 |
| [src/engine/utils/AnimationController.cpp](/src/engine/utils/AnimationController.cpp) | C++ | 1 | 0 | 1 | 2 |
| [src/engine/utils/AnimationController.h](/src/engine/utils/AnimationController.h) | C++ | 10 | 3 | 4 | 17 |
| [src/engine/utils/Graphics.cpp](/src/engine/utils/Graphics.cpp) | C++ | 14 | 0 | 4 | 18 |
| [src/engine/utils/Graphics.h](/src/engine/utils/Graphics.h) | C++ | 12 | 0 | 4 | 16 |
| [src/engine/utils/Math.cpp](/src/engine/utils/Math.cpp) | C++ | 10 | 0 | 3 | 13 |
| [src/engine/utils/Math.h](/src/engine/utils/Math.h) | C++ | 59 | 17 | 26 | 102 |
| [src/engine/utils/Mesh.cpp](/src/engine/utils/Mesh.cpp) | C++ | 51 | 9 | 12 | 72 |
| [src/engine/utils/Mesh.h](/src/engine/utils/Mesh.h) | C++ | 14 | 0 | 3 | 17 |
| [src/engine/utils/Shader.cpp](/src/engine/utils/Shader.cpp) | C++ | 74 | 3 | 15 | 92 |
| [src/engine/utils/Shader.h](/src/engine/utils/Shader.h) | C++ | 19 | 0 | 5 | 24 |
| [src/engine/utils/Sprite.h](/src/engine/utils/Sprite.h) | C++ | 3 | 0 | 2 | 5 |
| [src/engine/utils/Texture.cpp](/src/engine/utils/Texture.cpp) | C++ | 33 | 7 | 9 | 49 |
| [src/engine/utils/Texture.h](/src/engine/utils/Texture.h) | C++ | 15 | 1 | 5 | 21 |
| [src/engine/utils/io.cpp](/src/engine/utils/io.cpp) | C++ | 9 | 1 | 2 | 12 |
| [src/engine/utils/io.h](/src/engine/utils/io.h) | C++ | 3 | 0 | 2 | 5 |
| [src/engine/utils/meshes.cpp](/src/engine/utils/meshes.cpp) | C++ | 19 | 0 | 6 | 25 |
| [src/engine/utils/meshes.h](/src/engine/utils/meshes.h) | C++ | 9 | 0 | 5 | 14 |
| [src/game/components/Shrink.cpp](/src/game/components/Shrink.cpp) | C++ | 10 | 0 | 3 | 13 |
| [src/game/components/Shrink.h](/src/game/components/Shrink.h) | C++ | 10 | 0 | 2 | 12 |
| [src/game/components/Spawner.cpp](/src/game/components/Spawner.cpp) | C++ | 33 | 0 | 10 | 43 |
| [src/game/components/Spawner.h](/src/game/components/Spawner.h) | C++ | 9 | 0 | 2 | 11 |
| [src/game/prefabs.cpp](/src/game/prefabs.cpp) | C++ | 36 | 0 | 6 | 42 |
| [src/game/prefabs.h](/src/game/prefabs.h) | C++ | 7 | 0 | 2 | 9 |
| [src/game/scenes.cpp](/src/game/scenes.cpp) | C++ | 6 | 0 | 2 | 8 |
| [src/game/scenes.h](/src/game/scenes.h) | C++ | 7 | 0 | 2 | 9 |
| [src/main.cpp](/src/main.cpp) | C++ | 26 | 12 | 14 | 52 |

[Summary](results.md) / Details / [Diff Summary](diff.md) / [Diff Details](diff-details.md)