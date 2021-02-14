#pragma once
#include <SFML\Graphics\CircleShape.hpp>
class Ball
{
	public:
		int size;
		float mass;
		float position[2] = { 0, 0 };
		float velocity[2] = { 0, 0 };
		sf::Color color;

		sf::CircleShape shape;

		Ball(int size, float mass, sf::Color color, int position[2], float velocity[2]);
		void Move(float gravitation, float deltaTime, int windowSize[]);
};