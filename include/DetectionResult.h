#pragma once

#include <string>

//　物体検知の結果を表す構造体
struct DetectionResult{
    std::string label;
    float confidence;
};