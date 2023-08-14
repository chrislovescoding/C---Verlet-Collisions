#include "Particle.hpp"
#include <random>
#include <iostream>

std::random_device rd;                  
std::mt19937 Particle::_engine(rd());

Particle::Particle(int width, int height, bool placed, float posx, float posy) : _rad(12), _circle(_rad) {
    std::uniform_real_distribution<float> x(_rad, static_cast<float>(width) - _rad);
    std::uniform_real_distribution<float> y(_rad, static_cast<float>(height) - _rad);
    std::uniform_int_distribution<int> rgb(0, 255);

    
    if (placed){
        _pos = sf::Vector2f(posx, posy);
    } else{
        _pos = sf::Vector2f(x(_engine), y(_engine));
    }
    
    // std::cout << _pos.x << ", " << _pos.y << '\n';
    _prevPos = _pos;
    _acc = sf::Vector2f(0,0);

    // std::cout << "hi";
    _colour = sf::Color(rgb(_engine), rgb(_engine), rgb(_engine));

    _circle.setOrigin(_rad, _rad);
    _circle.setFillColor(_colour);
    _circle.setOutlineColor(_colour);
}

//setters
void Particle::setPos(const sf::Vector2f& newPos) {
    _pos = newPos;
}
void Particle::setAcc(const sf::Vector2f& newAcc) {
    _acc = newAcc;
}
void Particle::setPrevPos(const sf::Vector2f& newPrevPos) {
    _prevPos = newPrevPos;
}

// //getters
sf::Vector2f Particle::getPos() const {
    return _pos;
}
sf::Vector2f Particle::getAcc() const {
    return _acc;
}
sf::Vector2f Particle::getPrevPos() const {
    return _prevPos;
}
int Particle::getRad() const {
    return _rad;
}

//functions

void Particle::show(sf::RenderWindow& window) {
    window.draw(_circle);
}

void Particle::updatePosition(float dt) {
    sf::Vector2f newPos = _pos + (_pos - _prevPos) + (_acc * dt * dt);
    _prevPos = _pos;
    _pos = newPos;
    _acc = sf::Vector2f(0, 0);
   
   _circle.setPosition(_pos);
}

void Particle::accelerate(const sf::Vector2f& acc) {
    _acc += acc;
}

void Particle::constrain(const int width, const int height) {
    if (_pos.x < _rad){
        _pos.x = _rad;
    } else if (_pos.x > width - _rad) {
        _pos.x = width - _rad;
    }
    if (_pos.y < _rad){
        _pos.y = _rad;
    } else if (_pos.y > height - _rad) {
        _pos.y = height - _rad;
    }
}
