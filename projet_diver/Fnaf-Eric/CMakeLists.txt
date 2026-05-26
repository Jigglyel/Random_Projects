cmake_minimum_required(VERSION 3.25)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
add_compile_options(-g)
#import la bibliothèque SFML depuis un repo github
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
set(SFML_USE_SYSTEM_DEPS FALSE)
FetchContent_MakeAvailable(SFML)

#importe la bibliothèque SFML depuis le repo github SFML
add_executable(Fnaf
    ./src/Button.cpp
    ./src/Fnaf.cpp
    ./src/Animatronic.cpp
    ./src/Game.cpp
    ./src/TextureManager.cpp
    ./src/Renderer.cpp
    ./src/Walker.cpp
    ./src/Raphael.cpp
    ./src/Lucas.cpp
    ./src/soeur.cpp
    ./src/Freddy.cpp
    ./src/SoundManager.cpp
    ./src/FontManager.cpp
)
target_link_libraries(Fnaf PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
target_compile_features(Fnaf PRIVATE cxx_std_17)

