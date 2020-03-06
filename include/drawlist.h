
/**
 * @file drawlist.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2020-03-05
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <SFML/Graphics.hpp>
#include "entity.h"

using sf::Drawable, sf::RenderTarget, sf::RenderStates;

/**
 * @brief A class that manages a list of drawables and entities.
 * Draw and update calls will go through this class.
 *
 */
class DrawList: public sf::Drawable {
private:

	std::vector<Drawable*> drawables;
	std::vector<Entity*> entities;

public:

	void add(Drawable* drawable) {
		drawables.push_back(drawable);
	}

	void add(Entity* entity) {
		entities.push_back(entity);
		entity->source = this; // set the source
	}

	/**
	 * @brief Removes the given drawable from the draw list.
	 *
	 * @param drawable the drawable to remove
	 */
	void remove(Drawable* drawable) {

		auto it = std::remove(drawables.begin(), drawables.end(), drawable);
		drawables.erase(it, drawables.end());
	}

	/**
	 * @brief Removes the given entity from the draw list.
	 *
	 * @param drawable the entity to remove
	 */
	void remove(Entity* entity) {

		auto it = std::remove(entities.begin(), entities.end(), entity);
		entities.erase(it, entities.end());
	}

    void draw(RenderTarget& target, RenderStates states) const override {

		// draw all drawables
		for(auto it = drawables.begin(); it != drawables.end(); it++)
			target.draw(**it, states);

		// then draw all entities
		for(auto it = entities.begin(); it != entities.end(); it++)
			target.draw(**it, states);
	}

	void update(float delta) {

		for(auto it = entities.begin(); it != entities.end(); it++)
			(**it).onUpdate(delta);
	}

	void keyPress(sf::Keyboard::Key code) {

		for(auto it = entities.begin(); it != entities.end(); it++)
			(**it).onKeyPressed(code);
	}

	void keyRelease(sf::Keyboard::Key code) {

		for(auto it = entities.begin(); it != entities.end(); it++)
			(**it).onKeyReleased(code);
	}
};