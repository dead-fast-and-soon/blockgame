
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "constants.h"
#include "frameclock.h"
#include "entity.h"
#include "block.h"
#include "board.h"
#include "text.h"
#include "drawlist.h"


int main() {

	sf::RenderWindow window(sf::VideoMode(W_WIDTH, W_HEIGHT), "Game");

	// ========================================================================
	//  Load Resources
	// ========================================================================

	Board board(10, 8);

	board.spawnBlock(0, 0);
	board.spawnBlock(0, 1, true);
	board.spawnBlock(1, 1);

	Text text;

	DrawList draws;

	draws.add(&text);
	draws.add(&board);

	// ========================================================================
	//  Draw Loop
	// ========================================================================

	FrameClock fclock; // keeps track of dtime between frames

	while(window.isOpen()) {

		sf::Event event;
		while(window.pollEvent(event)) {

			//  Window Handler
			// ----------------
			if(event.type == sf::Event::Closed) {
				window.close();
			}

			//  Keyboard Handler
			// ------------------
			if(event.type == sf::Event::KeyPressed) {
				draws.keyPress(event.key.code);
			}

			if(event.type == sf::Event::KeyReleased) {
				draws.keyRelease(event.key.code);
			}
		}

		//  Exit Binding
		// --------------
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {

			window.close();
		}

		// clear buffer
		window.clear();

		// update everything
		draws.update(fclock.delta());

		text.setText("FPS: " + std::to_string(fclock.getAverageFPS()));

		// draw everything
		window.draw(draws);

		// flip buffers
		window.display();

		// calculate delta_time
		fclock.addFrame();
	}

	return 0;
}

