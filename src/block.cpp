
#include "block.h"

using key = sf::Keyboard::Key;


Vector2f scale(Vector2i vec, int scalar) {

    int x = vec.x * scalar;
    int y = vec.y * scalar;

    return Vector2f(x, y);
}


bool Block::move(int x, int y) {

    pos += Vector2i(x, y);
    updatePosition();
    return true;
    // return false if cannot move to this position
}


void Block::updatePosition() {

    rect->setPosition(scale(pos, BLOCK_SIZE) + offset);
    tri->setPosition(scale(pos, BLOCK_SIZE) + offset);
}

void Block::setPosition(int x, int y) {

    pos = Vector2i(x, y);
    updatePosition();
}

Block::Block(const Vector2f& offset, const Vector2i& pos)
    : pos(pos), offset(offset) {

    rect = new sf::RectangleShape(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));

    tri = new sf::ConvexShape();
    tri->setPointCount(3);
    tri->setPoint(0, sf::Vector2f(0, BLOCK_SIZE));
    tri->setPoint(1, sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
    tri->setPoint(2, sf::Vector2f(BLOCK_SIZE, 0));

    setColor(sf::Color::Cyan);
    updatePosition();
}

void Block::setColor(sf::Color color) {

    sf::Color darker = sf::Color(color.r * 0.8,
                                 color.g * 0.8,
                                 color.b * 0.8, 255);

    rect->setFillColor(color);
    tri->setFillColor(darker);
}

Block::Block(): Block(Vector2f(0, 0), Vector2i(0, 0)) {}



void inline Block::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    target.draw(*rect, states);
    target.draw(*tri, states);
}


void Block::onKeyPressed(sf::Keyboard::Key code) {

    switch(code) {
    case key::D: // RIGHT
        move(+1, 0); break;

    case key::A: // LEFT
        move(-1, 0); break;

    case key::W: // UP
        move(0, -1); break;

    case key::S: // DOWN
        move(0, +1); break;
    }
}
