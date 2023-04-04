#pragma once

//#include <SFML/Graphics.hpp>

#include "Object.hpp"

namespace sf {
    class RenderWindow;
}

class Pin;

class Connection : public Object {
public:
    Connection(/* args */);
    ~Connection();

    void setFrom(Pin* from);
    void setTo(Pin* to);

    [[nodiscard]] int getFrom() const;
    [[nodiscard]] int getTo() const;

    void draw(sf::RenderWindow& window);

private:
    Pin* m_from;
    Pin* m_to;
};