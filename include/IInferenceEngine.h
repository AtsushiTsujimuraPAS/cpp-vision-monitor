#pragma once

#include <vector>
#include "DetectionResult.h"

class IInferenceEngine{
public:
    virtual ~IInferenceEngine() = default;
    virtual std::vector<DetectionResult> infer() = 0;
};