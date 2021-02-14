#include "Ball.h"
#include <SFML\Graphics\Color.hpp>
#include <SFML\System\Time.hpp>
 
Ball::Ball(int size, float mass, sf::Color color, int position[2], float velocity[2])
{
	// Init variables
	this->size = size;
	this->mass = mass;
	this->color = color;
	
	for (int i = 0; i < 2; i++)
	{
		this->position[i] = position[i];
		this->velocity[i] = velocity[i];
	}

	// Generate the shape
	this->shape = sf::CircleShape(size);
	this->shape.setFillColor(this->color);
}

void Ball::Move(float gravitation, float deltaTime, int windowSize[])
{
	// Calculate window borders (because the origin of the sphere is in top right corner)
	int collistionBorders[] = { windowSize[0] - size * 2, windowSize[1] - size * 2 };
	// Apply gravitation
	this->velocity[1] -= gravitation * this->mass;
	// Calculate new positon from velocities
	this->position[0] += this->velocity[0] * deltaTime;
	this->position[1] += this->velocity[1] * deltaTime;
	// Inverse the velocity if ball has colided with a wall
	if (this->position[0] < 0 || this->position[0] > collistionBorders[0])
		this->velocity[0] *= -1;
	if (this->position[1] < 0 || this->position[1] > collistionBorders[1])
		this->velocity[1] *= fmax(-0.75 / mass, -0.75);
	// Cap the position
	this->position[0] = fmin(fmax(0, this->position[0]), collistionBorders[0]);
	this->position[1] = fmin(fmax(0, this->position[1]), collistionBorders[1]);
	// Set new location
	this->shape.setPosition(position[0], position[1]);
}