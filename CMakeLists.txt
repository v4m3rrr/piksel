cmake_minimum_required(VERSION 3.19)
project(piksel VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(MSVC)

else()
set(LSAN_SUPPRESSIONS_FILE "${CMAKE_CURRENT_SOURCE_DIR}/suppressions.supp")
set(LSAN_ENV_VAR "LSAN_OPTIONS=suppressions=${LSAN_SUPPRESSIONS_FILE}")
endif()
set(OpenGL_GL_PREFERENCE "LEGACY")

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/include/piksel/config.hh.in
  ${CMAKE_CURRENT_BINARY_DIR}/generated/piksel/config.hh
)

add_library(${PROJECT_NAME} STATIC  
    src/graphics.cc
    src/window.cc
    src/shader.cc
    src/image.cc
    src/texture.cc
    src/camera.cc
    src/mesh.cc
    src/color.cc
    src/model.cc
    src/wireframe.cc
    src/liner.cc
    src/object.cc
    src/vehicle_model.cc
    src/gui_object.cc
    src/gui_manager.cc
)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
  message(STATUS "Assuming raspberry Pi detected")
  target_compile_definitions(${PROJECT_NAME} PUBLIC -DRASPBERRY_PI)
endif()

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated>
    $<INSTALL_INTERFACE:include>
)

# --- GLFW ---
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)

# --- OpenGL ---
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)

# --- glm ---
find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

# --- glad ---
find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)

# --- stb ---
find_package(Stb REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${Stb_INCLUDE_DIR})

# --- imgui ---
find_package(imgui CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)

if(MSVC)

else()
# --- Link dependencies ---
# Link against pthread and dl (required by GLFW on Linux)
target_link_libraries(${PROJECT_NAME} PRIVATE pthread dl)

# --- Optional: Compiler warnings ---
target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall -Wextra 
)
endif()

option(BUILD_TESTS "Build unit tests" ON)

if (BUILD_TESTS)
include(CTest)

set(TEST_SOURCES
  gfx_test
  imgui_test
)

foreach(name IN LISTS TEST_SOURCES)
  add_executable(${name} tests/${name}.cc)
  if(MSVC)

  else()
    #target_link_options(${name} PUBLIC -fsanitize=address,undefined,leak)
    #target_compile_options( ${name} PUBLIC
    #  -fsanitize=address,undefined,leak)
  endif()
  target_link_libraries(${name} PRIVATE ${PROJECT_NAME})
  add_test(NAME ${name} COMMAND ${name})
  if(MSVC)

  else()
    #set_tests_properties(${name} PROPERTIES
    #  ENVIRONMENT "${LSAN_ENV_VAR}")
  endif()
endforeach()

endif()

# Install the library
install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

# Install the public headers
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.hh"
)

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/generated/piksel/
    DESTINATION include/piksel
    FILES_MATCHING PATTERN "*.hh"
)

install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION lib/cmake/${PROJECT_NAME}
)

include(CMakePackageConfigHelpers)

# 1. Configure the Config file (Fills in @PACKAGE_INIT@ etc.)
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/pikselConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/pikselConfig.cmake"
    INSTALL_DESTINATION lib/cmake/piksel
)

# 2. Generate a Version file
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/pikselConfigVersion.cmake"
    VERSION ${PROJECT_VERSION} # Make sure project(piksel VERSION x.x.x) is set, or hardcode 0.1.0
    COMPATIBILITY SameMajorVersion
)

# 3. Install the Config and Version files
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/pikselConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/pikselConfigVersion.cmake"
    DESTINATION lib/cmake/piksel
)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/shaders/
    DESTINATION share/piksel/shaders
    FILES_MATCHING
    PATTERN "*"
)
