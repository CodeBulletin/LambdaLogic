#include "Simulation.hpp"

void Simulation::update() {
}

void Simulation::run() {
    this->m_time = this->m_clock.getElapsedTime();
    if (this->m_time.asSeconds() >= this->tick_rate) {
        this->m_clock.restart();
        this->m_ticks++;
        for (int i = 0; i < this->m_update_per_tick; i++) {
            this->update();
        }
    }
}

void Simulation::add_chip(chip &chip) {
    this->m_chips.emplace_back(chip);
}

void Simulation::remove_chip(int chip_id) {
    for (int i = 0; i < this->m_chips.size(); i++) {
        if (this->m_chips[i].get_chip_id() == chip_id) {
            this->m_chips.erase(this->m_chips.begin() + i);
        }
    }
}
