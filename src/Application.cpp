#include "Application.h"
#include <iostream>
#include "DummyInferenceEngine.h"
#include "ResultProcessor.h"

Application::Application(IInferenceEngine& engine)
    : engine_(engine)
    {}

void Application::run(){
    auto results = engine_.infer();
    ResultProcessor processor;
    results = processor.process(
        results
    );

    std::cout << "Vision Monitor Started" << std::endl;
    for(const auto& result: results){
        std::cout << "label: " << result.label << ", confidence: " << result.confidence << "\n";
    }
}