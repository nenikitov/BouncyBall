#include <iostream>
#include <SFML/Graphics.hpp>
#include "Ball.h"

int main()
{
    // Generate window
    sf::RenderWindow window(sf::VideoMode(640, 480), "Jumpy Ball");

    // Physics stuff
    const double gravitation = -0.25;
    sf::Clock deltaClock;
    int windowSize[2] = { 640, 480 };

    // Bouncy ball generation
    bool canGenerate = true;
    sf::Color possibleColors[] = {sf::Color::Blue, sf::Color::Cyan, sf::Color::Magenta, sf::Color::Red, sf::Color::White, sf::Color::Yellow};
    std::vector<Ball> balls;
    //Ball ball(16, 1, sf::Color::Red);
    //ball.velocity[0] = 50;

    while (window.isOpen())
    {
        // Event handling
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Key is pressed
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    // Generate new ball info
                    int newBallSize = rand() % 32 + 16;
                    float newBallMass = (float)(rand() / RAND_MAX) * 4.5 + 0.5;
                    sf::Color newBallColor = possibleColors[rand() % sizeof(possibleColors) / sizeof(possibleColors[0])];
                    int newBallPosition[] = { rand() % windowSize[0], rand() % windowSize[1] };
                    float newBallVelocity[] = { (float)(rand() / RAND_MAX) * 2000 - 1000, (float)(rand() / RAND_MAX) * 2000 - 1000 };
                    // Generate the ball
                    Ball newBall(newBallSize, newBallMass, newBallColor, newBallPosition, newBallVelocity);
                    // Put it inside the vector
                    balls.push_back(newBall);
                    // Block generation until the key is released
                    canGenerate = false;
                }
            }
            // Key is released
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Space)
                    canGenerate = true;
            }
            // Window is resized
            if (event.type == sf::Event::Resized)
            {
                sf::FloatRect newSize(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(newSize));

                windowSize[0] = event.size.width;
                windowSize[1] = event.size.height;
            }
            // Window is closed
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Frame update
        // Physics
        sf::Time deltaTime = deltaClock.restart();
        for (int i = 0; i < balls.size(); i++)
            balls[i].Move(gravitation, deltaTime.asSeconds(), windowSize);
        // Rendering
        window.clear();
        for (int i = 0; i < balls.size(); i++)
            window.draw(balls[i].shape);
        window.display();
    }

    return 0;
}