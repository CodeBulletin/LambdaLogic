# Specify the minimum required version of CMake
cmake_minimum_required(VERSION 3.12.0)

# Set the name of the project and project version
project(LambdaLogic)
set(PROJECT_DESCRIPTION "Cross Platform Logic Simulator with C++ and SFML")
set(PROJECT_VERSION "0.1.0")
set(ExecutableName "LambdaLogic")

# Set the C++ standard and disable any extensions
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include CTest and enable testing
include(CTest)
enable_testing()

# Set CPack properties for the project
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

# Include CPack
include(CPack)

# Copy the Assets directory to the build directory
file(COPY Assets DESTINATION ${CMAKE_BINARY_DIR})

# Add the src directory to the build
add_subdirectory(src)

# Set the output directory for the executable
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Create the executable and specify the source files
add_executable(${ExecutableName} ./src/main.cpp src/Pin.cpp src/Gate.cpp src/Simulation.cpp headers/Simulation.hpp src/Connection.cpp headers/Connection.hpp)

# Add include directories for the executable
target_include_directories(${ExecutableName} PRIVATE ./headers/ "${IMGUI_DIR}" "${sfml_SOURCE_DIR}/include")

# Link the executable against the necessary libraries
target_link_libraries(${ExecutableName} PRIVATE ImGui-SFML::ImGui-SFML sfml-graphics sfml-window sfml-system)

# Set properties for the executable
set_target_properties(${ExecutableName} PROPERTIES
    DESCRIPTION "${PROJECT_DESCRIPTION}"
    VERSION "${PROJECT_VERSION}"
)
