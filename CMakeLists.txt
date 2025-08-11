cmake_minimum_required(VERSION 3.16)
project(IntegratedController CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# --- Qt Configuration ---
# Find Qt6 components
find_package(Qt6 6.2 REQUIRED COMPONENTS Core Gui Qml Quick)

# Enable automatic Qt features
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# --- SDK Configuration ---
# Define include directories for the SDKs
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/hypersen_sdk
    ${CMAKE_CURRENT_SOURCE_DIR}/zmotion_sdk
)

# Define library directories for the SDKs
link_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/hypersen_sdk
    ${CMAKE_CURRENT_SOURCE_DIR}/zmotion_sdk
)

# --- Executable Definition ---
add_executable(controller
    main.cpp
    # Add other .cpp files here as we create them
)

# --- Linking ---
target_link_libraries(controller
    # Link against Qt modules
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick

    # Link against SDK libraries
    hps_lcf_sdk
    zmotion
    zauxdll
)

# For Windows, if we are using Visual Studio, we might need to handle character sets
if(MSVC)
    add_compile_definitions(UNICODE _UNICODE)
endif()

message(STATUS "Project 'IntegratedController' configured for Qt.")
message(STATUS "Qt6 version: ${Qt6_VERSION}")
