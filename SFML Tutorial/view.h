#pragma once
#include <SFML/Graphics.hpp>
#include "map.h"

sf::View view;

sf::View getPlayerCoordinateForView(float X, float Y) {
	float x = X + 62, y = Y + 81;
	if (x < 640) { x = 640; }
	if (y < 400) { y = 400; }
	if (y > HEIGHT_MAP * 128 - 400) { y = HEIGHT_MAP*128-400; }
	view.setCenter(x, y);
	return view;
}

sf::View viewMap(float time) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		view.move(-0.1*time, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		view.move(0.1*time, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		view.move(0,0.1*time);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		view.move(0,-0.1*time);
	}
	return view;
}