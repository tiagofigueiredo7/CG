#include "engine/structs/FPS.hpp"

FPS::FPS() {
    timebase = 0.0f;
    frame = 0;
    fps = 0.0f;
    fpsString = "FPS: 0.00";
}

void FPS::updateFPS() {
    frame++;
    float time = glutGet(GLUT_ELAPSED_TIME);
    if (time - timebase > 1000) {
        fps = frame * 1000.0f / (time - timebase);
        timebase = time;
        frame = 0;
        fpsString.clear();
        char buffer[50];
        snprintf(buffer, sizeof(buffer), "FPS: %.2f", fps);
        fpsString = buffer;
    }
}

string FPS::getFPSString() {
    return fpsString;
}