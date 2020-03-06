
#pragma once

#include "constants.h"
#include "entity.h"

using sf::Vector2i, sf::Vector2f;


class Block: public Entity {
private:

    sf::RectangleShape* rect;
    sf::ConvexShape* tri;
    sf::RectangleShape* outline;

    Vector2i pos;
    Vector2f offset;

    void updatePosition();

public:

    Block();

    Block(const Vector2f& offset, const Vector2i& pos);

    ~Block() {
        delete rect;
        delete tri;
        delete outline;
    }

    Vector2i getPosition() { return pos; }

    void setPosition(int x, int y);

    void setColor(sf::Color);

    bool move(int x, int y);

    void onKeyPressed(sf::Keyboard::Key key) override;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};