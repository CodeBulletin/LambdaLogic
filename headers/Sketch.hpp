#pragma once

#include "Simulation.hpp"

class Sketch {
private:
    Simulation m_simulation;
    std::vector<Gate*> m_inputGates;
    std::vector<Gate*> m_outputGates;

    int m_currentObjectID = 0;
public:
    Sketch();
    ~Sketch();

    Simulation& getSimulation();

    void run();
    void draw(sf::RenderWindow& window);
    void addGate(Gate* gate);
    void removeGate(Gate* gate);
};