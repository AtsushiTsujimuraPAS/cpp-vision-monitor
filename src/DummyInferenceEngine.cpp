#include "DummyInferenceEngine.h"

std::vector<DetectionResult>
DummyInferenceEngine::infer()
{
    return {
        {"Cat", 0.05f},
        {"Dog", 0.92f},
        {"Bird", 0.03f}
    };
}