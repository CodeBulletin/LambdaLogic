#pragma once

#include <SFML/Graphics.hpp>

#include "Gate.hpp"

#ifndef NDEBUG
#include "sfhelper/sfh_debug.hpp"
#endif

class Simulation {
private:
    void removePin(int pin_id);

public:
    Simulation(/* args */) = default;
    ~Simulation();

    void run();
    void addChip(Gate *chip);
    void removeChip(int chip_id);
    void update();
    void createConnection(int from, int to);
    void draw(sf::RenderWindow& window);
    Object* clicked(sf::Vector2f pos);

private:
    long long m_ticks = 0;
    double m_tickRate = 1.0;
    int m_updatePerTick = 1;
    sf::Clock m_clock;
    sf::Time m_time;
    std::vector<Gate*> m_chips;
    std::unordered_map<int, Pin*> m_pins;
    std::unordered_map<int, Connection*> m_connections;
    std::vector<int> m_pinKeys;

    // For debugging
#ifndef NDEBUG
    void setPinState(int, int);
#endif
};
