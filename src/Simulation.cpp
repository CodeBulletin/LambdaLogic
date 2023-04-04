#include "Simulation.hpp"
#include <algorithm>

void Simulation::update() {
    for (int i = 0; i < this->m_chips.size(); i++) {
        Gate *chip = this->m_chips[i];
        chip->compute();
    }

    for (const auto key : this->m_connections) {
        auto connection = key.second;
        Pin *from = this->m_pins[connection->getFrom()];
        Pin *to = this->m_pins[connection->getTo()];
        to->setState(from->getState());
    }

#ifndef NDEBUG
//    sfh::debug::log("Simulation::update()");
//    for (const auto& chip : this->m_chips) {
//        sfh::debug::log("\tchip: ", chip->getName(), " - id: ", chip->getId());
//        for (int j = 0; j < chip->getInputPinCount(); j++) {
//            sfh::debug::log("\t\tinput pin: ", chip->getInputPins()[j].getId(), " - state: ", chip->getInputPins()[j].getState());
//        }
//        for (int j = 0; j < chip->getOutputPinCount(); j++) {
//            sfh::debug::log("\t\toutput pin: ", chip->getOutputPins()[j].getId(), " - state: ", chip->getOutputPins()[j].getState());
//        }
//    }
#endif
}

void Simulation::run() {
//    this->m_time = this->m_clock.getElapsedTime();
//    if (this->m_time.asSeconds() >= this->tick_rate) {
//        this->m_clock.restart();
        this->m_ticks+=m_updatePerTick;
        for (int i = 0; i < this->m_updatePerTick; i++) {
            this->update();
        }
//    }
}

void Simulation::addChip(Gate *chip) {
    this->m_chips.emplace_back(chip);
    for (int i = 0; i < chip->getInputPinCount(); i++) {
        this->m_pins[chip->getInputPins()[i].getId()] = &(chip->getInputPins()[i]);
        this->m_pinKeys.emplace_back(chip->getInputPins()[i].getId());
    }
    for (int i = 0; i < chip->getOutputPinCount(); i++) {
        this->m_pins[chip->getOutputPins()[i].getId()] = &(chip->getOutputPins()[i]);
        this->m_pinKeys.emplace_back(chip->getOutputPins()[i].getId());
    }
}

void Simulation::removeChip(int chip_id) {
    for (int i = 0; i < this->m_chips.size(); i++) {
        if (this->m_chips[i]->getId() == chip_id) {
            Gate* chip = this->m_chips[i];
            for (int j = 0; j < chip->getInputPinCount(); j++) {
                removePin(chip->getInputPins()[j].getId());
            }
            for (int j = 0; j < chip->getOutputPinCount(); j++) {
                removePin(chip->getOutputPins()[j].getId());
            }
            std::cout << this->m_chips.size() << std::endl;
            this->m_chips.erase(this->m_chips.begin() + i);
            std::cout << this->m_chips.size() << std::endl;
            delete chip;
            return;
        }
    }
}

void Simulation::removePin(int pin_id) {
    for (int i = 0; i < this->m_pinKeys.size(); i++) {
        if (this->m_pinKeys[i] == pin_id) {
            this->m_pinKeys.erase(this->m_pinKeys.begin() + i);
            break;
        }
    }
    this->m_pins.erase(pin_id);
}



void Simulation::createConnection(int from, int to) {
    auto* connection = new Connection();
    connection->setFrom(this->m_pins[from]);
    connection->setTo(this->m_pins[to]);
    this->m_pins[from]->addConnection(connection);
    this->m_pins[to]->addConnection(connection);
    this->m_connections[connection->getId()] = connection;
}

void Simulation::draw(sf::RenderWindow& window) {
    for (const auto& chip : this->m_chips) {
        chip->draw(window);
    }
    for (const auto& key : this->m_connections) {
        auto connection = key.second;
        connection->draw(window);
    }
    for (const auto& conn : this->m_connections) {
        conn.second->draw(window);
    }
}

Object* Simulation::clicked(sf::Vector2f pos) {
    for (const auto& pinid : this->m_pinKeys) {
        auto pin = this->m_pins[pinid];
        if (pin->getRect().getGlobalBounds().contains(pos)) {
            return pin;
        }
    }
    for (const auto& chip : this->m_chips) {
        if (chip->getRect().getGlobalBounds().contains(pos)) {
            return chip;
        }
    }
    return nullptr;
}

Simulation::~Simulation() {
    for (auto& key : this->m_connections) {
        delete key.second;
    }
    for (auto& chip : this->m_chips) {
        delete chip;
    }
}

#ifndef NDEBUG
void Simulation::setPinState(int pin_id, int state) {
    this->m_pins[pin_id]->setState(state);
}
#endif