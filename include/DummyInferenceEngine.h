#pragma once
#include "IInferenceEngine.h"

class DummyInferenceEngine: public IInferenceEngine{
    public:
        std::vector<DetectionResult> infer() override ;
};