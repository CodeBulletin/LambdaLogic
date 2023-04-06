#pragma once

#include "Gate.hpp"


class Nand : public Gate {
public:
    Nand() : Gate("Nand") {
        this->m_gateType = GateType::LOGIC;

        for (int i = 0; i < 2; ++i) {
            Pin pin;
            pin.setType(0);
            this->m_InputPins.push_back(pin);
        }

        Pin pin;
        pin.setType(1);
        this->m_outputPins.push_back(pin);

        this->m_inputPinCount = 2;
        this->m_outputPinCount = 1;

        compute_shape();
    }

    void compute() override {
        this->m_input1 = this->m_InputPins[0].getState();
        this->m_input2 = this->m_InputPins[1].getState();
        this->m_output = !(this->m_input1 && this->m_input2);
        this->m_outputPins[0].setState(this->m_output);
    }

private:
    bool m_output = false;
    bool m_input1 = false;
    bool m_input2 = false;
};
