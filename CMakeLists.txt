cmake_minimum_required(VERSION 3.11)
project(PongGame)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate compile_commands.json for better IntelliSense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include FetchContent module to download Raylib
include(FetchContent)

# Fetch Raylib
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.0
)

# Make Raylib available
FetchContent_MakeAvailable(raylib)

# Create executable
add_executable(pong src/main.cpp)

# Link Raylib to our executable
target_link_libraries(pong raylib)

# Copy assets to build directory (optional, for when you add sounds/textures later)
# file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR} OPTIONAL)

# Platform-specific settings
if(WIN32)
    # On Windows, copy required DLLs to output directory
    set_target_properties(pong PROPERTIES
        WIN32_EXECUTABLE FALSE  # Keep console window for debugging
    )
endif()