
#pragma once

#include <SFML/Graphics.hpp>


class DrawList;


class Entity: public sf::Drawable {
private:

    friend class DrawList;
    DrawList* source; // the drawlist that is drawing this entity

public:

    /**
     * @brief Updates this entity.
     *
     * @param delta the delta time between each frame
     */
    virtual void onUpdate(float delta) {};

    virtual void onKeyPressed(sf::Keyboard::Key key) {};

    virtual void onKeyReleased(sf::Keyboard::Key key) {};
};