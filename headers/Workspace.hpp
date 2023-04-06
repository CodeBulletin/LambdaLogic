#pragma once

#include "Sketch.hpp"

class Workspace {
private:
    std::unordered_map<int, Sketch*> sketches;
    int m_currentSketchID = 0;
public:
    Workspace();
    ~Workspace();

    void addSketch(Sketch* sketch);
    void removeSketch(Sketch* sketch);

    Sketch* getSketch(int id);
};