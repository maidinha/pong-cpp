cmake_minimum_required(VERSION 3.16)
project(pong)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# This assumes the SDL source is available in vendored/SDL
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

# Create your game executable target as usual
add_executable(${CMAKE_PROJECT_NAME} WIN32 
    src/pong.cpp 
    src/game.cpp 
    src/entities.cpp
    src/math.cpp
)

# Link to the actual SDL3 library.
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL3::SDL3)
