cmake_minimum_required(VERSION 3.0.0)
project(przyciski_souls_3)


find_package(OpenGL REQUIRED)
add_subdirectory(glm)
add_subdirectory(glfw)

file(GLOB_RECURSE SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(game ${SRC})
target_include_directories(game PUBLIC
    src
    glfw/include
    glm
)

target_link_libraries(game
    glm_shared
    glfw
    OpenGL::GL
    ${CMAKE_DL_LIBS}
)