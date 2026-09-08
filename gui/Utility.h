#pragma once

//#include <cmath>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>


template<typename T>
void centerOrigin(T& obj)
{
	sf::FloatRect bounds = obj.getLocalBounds();
	obj.setOrigin({bounds.size.x / 2, bounds.size.y / 2});
}
