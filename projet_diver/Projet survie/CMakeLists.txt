cmake_minimum_required(VERSION 3.25)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_BUILD_TYPE Debug) # or Release


include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
)
FetchContent_MakeAvailable(SFML)

add_executable(survie
    src/main.cpp
    src/Calcules.cpp
    src/game.cpp
    src/mob.cpp
)

target_compile_features(survie PRIVATE cxx_std_17)
target_link_libraries(survie PRIVATE sfml-graphics sfml-window sfml-system)

if (WIN32)
    add_custom_command(
        TARGET survie
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:survie>
            $<TARGET_FILE_DIR:survie>
        COMMAND_EXPAND_LISTS
    )
endif()
