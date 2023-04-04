#include "Connection.hpp"
#include "Pin.hpp"

Connection::Connection() : Object("Connection") {

}

Connection::~Connection() {

}

void Connection::setFrom(Pin *from) {
    this->m_from = from;
}

void Connection::setTo(Pin *to) {
    this->m_to = to;
}

int Connection::getFrom() const {
    return this->m_from->getId();
}

int Connection::getTo() const {
    return this->m_to->getId();
}

void Connection::draw(sf::RenderWindow &window) {
    sf::Vertex line[] = {
            sf::Vertex(this->m_from->getPos(), sf::Color::Red),
            sf::Vertex(this->m_to->getPos(), sf::Color::Red)
    };


    window.draw(line, 2, sf::PrimitiveType::Lines);
}