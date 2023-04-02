#pragma once

#include <SFML/Graphics.hpp>

#include "Gate.hpp"

class Simulation {
private:
    long long m_ticks = 0;
    double tick_rate = 1.0;
    int m_update_per_tick = 1;
    sf::Clock m_clock;
    sf::Time m_time;
    std::vector<Gate> m_chips;

public:
    Simulation(/* args */) = default;
    ~Simulation() = default;

    void run();
    void add_chip(Gate& chip);
    void remove_chip(int chip_id);
    void update();
};
