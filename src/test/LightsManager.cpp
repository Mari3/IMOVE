//
// Created by Wouter Posdijk on 11/05/16.
//

#include <SFML/Graphics.hpp>
#include "LightsManager.h"
#include "../scene/LightTrailScene.h"

void LightsManager::run() {

    sf::RenderWindow window(sf::VideoMode(800,600),"Lights!");

    Scene* scene = new LightTrailScene();

    while(window.isOpen()){

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        scene->draw(window);


        window.display();
    }

}

