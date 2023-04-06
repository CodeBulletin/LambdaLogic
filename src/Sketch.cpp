#include "Sketch.hpp"

Sketch::Sketch() {
    Object::setIdCounter(m_currentObjectID);
}

Sketch::~Sketch() {

}

Simulation &Sketch::getSimulation() {
    return m_simulation;
}

void Sketch::run() {
    m_simulation.run();
}

void Sketch::draw(sf::RenderWindow &window) {
    m_simulation.draw(window);
}

void Sketch::addGate(Gate *gate) {
    m_simulation.addChip(gate);
    if (gate->getGateType() == GateType::INPUT_G) {
        m_inputGates.push_back(gate);
    } else if (gate->getGateType() == GateType::OUTPUT_G) {
        m_outputGates.push_back(gate);
    }
}

void Sketch::removeGate(Gate *gate) {
    if (gate->getGateType() == GateType::INPUT_G) {
        for (int i = 0; i < m_inputGates.size(); i++) {
            Gate* input = m_inputGates[i];
            if (input->getId() == gate->getId()) {
                m_inputGates.erase(m_inputGates.begin() + i);
                break;
            }
        }
    } else if (gate->getGateType() == GateType::OUTPUT_G) {
        for (int i = 0; i < m_outputGates.size(); i++) {
            Gate* input = m_outputGates[i];
            if (input->getId() == gate->getId()) {
                m_inputGates.erase(m_inputGates.begin() + i);
                break;
            }
        }
    }
    m_simulation.removeChip(gate->getId());
}