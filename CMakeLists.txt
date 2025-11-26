cmake_minimum_required(VERSION 3.10)
project(piksel LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(OpenGL_GL_PREFERENCE "LEGACY")

#file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR}/bin)

#configure_file(
#  ${CMAKE_SOURCE_DIR}/include/piksel/config.hh.in
#  ${CMAKE_BINARY_DIR}/generated/config.hh
#)

add_library(${PROJECT_NAME} STATIC
    src/glad.c
    src/graphics.cc
    src/window.cc
    src/shader.cc
    src/image.cc
    src/texture.cc
    src/cube_manager.cc
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/third_party/glad/include
        ${CMAKE_SOURCE_DIR}/third_party
        #${CMAKE_BINARY_DIR}/generated
)

# --- GLFW ---
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

target_include_directories(${PROJECT_NAME} PRIVATE ${GLFW_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GLFW_LIBRARIES})

# --- OpenGL ---
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)

# --- Link dependencies ---
# Link against pthread and dl (required by GLFW on Linux)
target_link_libraries(${PROJECT_NAME} PRIVATE pthread dl)

# --- Optional: Compiler warnings ---
target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall -Wextra 
)

option(BUILD_TESTS "Build unit tests" ON)

if (BUILD_TESTS)
include(CTest)

set(TEST_SOURCES
  opengl_test
  chuj_test
)

foreach(name IN LISTS TEST_SOURCES)
  add_executable(${name} tests/${name}.cc)
  target_link_libraries(${name} PRIVATE ${PROJECT_NAME})
  add_test(${name} COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${name})
endforeach()

endif()
