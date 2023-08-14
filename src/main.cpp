#include <SFML/Graphics.hpp>
#include "Particle.hpp"
#include <cmath>
#include <vector>
#include "globals.hpp"
#include <iostream>
#include <omp.h>
#include <sstream>

void updatePositions(std::vector<Particle>& particles, float dt){
    for (auto& p : particles){
        p.updatePosition(dt);
    }
}

void constrainParticles(std::vector<Particle>& particles, const int width, const int height){
    for (auto& p : particles){
        p.constrain(width, height);
    }
}

void applyGravity(std::vector<Particle>& particles, const sf::Vector2f& gravity){
    for (auto& p : particles){
        p.accelerate(gravity);
    }
}

void solveCollisions(std::vector<Particle>& particles) {
    for (size_t i = 0; i < particles.size(); ++i){  
        for (size_t j = i + 1; j < particles.size(); ++j){
            Particle& p1 = particles[i];
            Particle& p2 = particles[j];

            sf::Vector2f dp = p1.getPos() - p2.getPos();
            float distanceSquared = (dp.x*dp.x) + (dp.y*dp.y);
        
            float radiiSum = p1.getRad() + p2.getRad();

            if (distanceSquared < radiiSum * radiiSum) {
                float distance = std::sqrt(distanceSquared);
                sf::Vector2f n = dp / distance;
                float d = radiiSum - distance;

                sf::Vector2f correction = n * d * 0.5f;
                p1.setPos(p1.getPos() + correction);
                p2.setPos(p2.getPos() - correction);
            }
        }
    }
}
void solveCollisionsParallel(std::vector<Particle>& particles) {
    #pragma omp parallel for
    for (size_t i = 0; i < particles.size(); ++i) {
        for (size_t j = i + 1; j < particles.size(); ++j) {
            Particle& p1 = particles[i];
            Particle& p2 = particles[j];

            sf::Vector2f dp = p1.getPos() - p2.getPos();
            float distanceSquared = (dp.x*dp.x) + (dp.y*dp.y);

            float radiiSum = p1.getRad() + p2.getRad();

            if (distanceSquared < radiiSum * radiiSum) {
                float distance = std::sqrt(distanceSquared);
                sf::Vector2f n = dp / distance;
                float d = radiiSum - distance;

                sf::Vector2f correction = n * d * 0.5f;

                #pragma omp critical
                {
                    p1.setPos(p1.getPos() + correction);
                    p2.setPos(p2.getPos() - correction);
                }
            }
        }
    }
}

void showParticles(std::vector<Particle>& particles, sf::RenderWindow& window) {
    for (auto& p : particles){
        p.show(window);
    }
}


int main() {
    const int width = 1000;
    const int height = 1000;

    int numOfBalls;

    std::cout << "Enter the number of balls which you'd like: ";
    std::cin >> numOfBalls;

    std::vector<Particle> particles;
    
    for (int i = 0; i < numOfBalls; ++i){
        particles.emplace_back(width, height);
    }

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(width, height), "Verlet Collision", sf::Style::Default, settings);
    sf::Clock clock;

    sf::Font font;
    if (!font.loadFromFile("..\\assets\\fonts\\Roboto-Regular.ttf")) {
        std::cerr << "Couldn't load font";
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24); 
    text.setFillColor(sf::Color::Green);
    text.setPosition(sf::Vector2f(0.0f, 0.0f));

    const int substeps = 6;

    const sf::Vector2f gravity(0.0f, 0.004235f);

    int frameCountFrameRate = 0;
    float lastTimeFrameRate = 0.0f;
    float lastTimePlaceBall = 100.0f;

    const float frameRateDisplayInterval = 100.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color(0, 0, 0));

        sf::Time elapsedTime = clock.restart();
        float dt = elapsedTime.asSeconds()*1000;
        float subdt = dt/substeps;
        lastTimePlaceBall += dt;
        lastTimeFrameRate += dt;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && lastTimePlaceBall >= 100.0f) {
            lastTimePlaceBall = 0.0f;

            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            float x = static_cast<float>(mousePos.x);
            float y = static_cast<float>(mousePos.y);
            particles.push_back(Particle(width, height, true, x, y));

            std::cout << particles.size() << '\n';
        }   

        if (lastTimeFrameRate >= frameRateDisplayInterval)
        {
            // std::cout << std::to_string(frameCountFrameRate);
            text.setString(std::to_string(static_cast<int>(floor(1/(dt/1000)))));
            lastTimeFrameRate -= frameRateDisplayInterval;
        }


        // std::cout << dt;

        for (int i = 0; i < substeps; ++i) {
            applyGravity(particles, gravity);
            constrainParticles(particles, width, height);
            solveCollisionsParallel(particles);
            updatePositions(particles, subdt);
        }

        showParticles(particles, window);
        
        window.draw(text);
        window.display();
    }

    return 0;
}

