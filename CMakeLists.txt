# Root CMake for the workspace
cmake_minimum_required(VERSION 3.16)
project(infographie LANGUAGES CXX)

# Enable C++17 globally
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_UI "Build the Qt UI launcher" ON)

# Add console-based graphics samples (MinGW + BGI)
add_subdirectory(code_graphics)

# Add the Qt UI launcher project (optional)
if (BUILD_UI)
    add_subdirectory(UI_luncher_infographie_projects)
endif()
