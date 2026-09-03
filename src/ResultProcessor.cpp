#include "ResultProcessor.h"
#include <algorithm>

std::vector<DetectionResult> ResultProcessor::process(
    std::vector<DetectionResult>& results
) const {
    std::sort(
        results.begin(), 
        results.end(), 
        [](const auto& lhs, const auto& rhs){
            return lhs.confidence > rhs.confidence;
        }
    );
    return results;
};
