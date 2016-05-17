//
// Created by Wouter Posdijk on 11/05/16.
//

#include <SFML/Graphics.hpp>
#include "LightsManager.h"
#include "../scene/LightTrail/LightTrailScene.h"

void LightsManager::run() {

    sf::RenderWindow window(sf::VideoMode(2560,1600),"Lights!");
    window.clear(sf::Color::Black);

    Scene* scene = new LightTrailScene();

    sf::Clock clock;

    while(window.isOpen()){

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //window.clear(sf::Color::Black);


        float dt = clock.restart().asSeconds();
        scene->update(dt);
        scene->draw(window);


        window.display();
    }

}
