cmake_minimum_required(VERSION 3.15)

project(
    CppVisionMonitor
    LANGUAGES CXX
)

add_executable(
    VisionMonitor
    app/main.cpp
    src/Application.cpp
    src/DummyInferenceEngine.cpp
    src/ResultProcessor.cpp
)

target_include_directories(
    VisionMonitor
    PRIVATE include
)

target_compile_features(
    VisionMonitor
    PRIVATE cxx_std_17
)