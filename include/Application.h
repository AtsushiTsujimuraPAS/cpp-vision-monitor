#pragma once

class IInferenceEngine;

class Application{
    public:
        explicit Application(IInferenceEngine& engine);

        void run();

    private:
        IInferenceEngine& engine_;
};