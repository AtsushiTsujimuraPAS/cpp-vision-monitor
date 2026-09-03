#pragma once

#include <vector>
#include "DetectionResult.h"

class ResultProcessor{
    public:
        std::vector<DetectionResult> process(std::vector<DetectionResult>& results) const;
};
