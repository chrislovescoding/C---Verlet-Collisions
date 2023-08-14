#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include "globals.hpp"

class Particle {
private:
    sf::Vector2f _prevPos;
    sf::Vector2f _pos;
    sf::Vector2f _acc;
    int _rad;
    sf::Color _colour;
    sf::CircleShape _circle;

    static std::mt19937 _engine;
public:
    Particle(int width, int height, bool placed = false, float posx = 0.0f, float posy = 0.0f);
    

    // //setters
    void setPos(const sf::Vector2f& newPos);
    void setAcc(const sf::Vector2f& newAcc);
    void setPrevPos(const sf::Vector2f& newPrevPos);

    // //getters
    sf::Vector2f getPos() const;
    sf::Vector2f getAcc() const;
    sf::Vector2f getPrevPos() const;
    int getRad() const;

    //functions
    void show(sf::RenderWindow& window);
    void updatePosition(float dt);
    void accelerate(const sf::Vector2f& acc);
    void constrain(int width, int height);
};
