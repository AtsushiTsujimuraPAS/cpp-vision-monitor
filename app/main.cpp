#include "Application.h"
#include "DummyInferenceEngine.h"

int main(){
    DummyInferenceEngine engine;
    Application app(engine);
    app.run();
    return 0;
}