cmake_minimum_required(VERSION 3.15)

project(
    cpp-vision-monitor
    LANGUAGES CXX
)

add_executable(
    VisionMonitor
    app/main.cpp
)

target_compile_features(
    VisionMonitor
    PRIVATE cxx_std_17
)