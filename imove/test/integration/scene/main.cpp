//
// Created by Wouter Posdijk on 25/05/16.
//

#include "opencv2/opencv.hpp"
#include "SFML/Graphics.hpp"
#include "../../../src/scene/LightTrail/LightTrailConfiguration.h"
#include "../../../src/scene/LightTrail/LightTrailScene.h"
#include "../../../src/scene/LightTrail/Repositories/LightsSceneVectorRepositories.h"

int main(int argc, char** argv){

    LightTrailConfiguration config = LightTrailConfiguration::readFromFile(argv[1]);

    sf::RenderWindow window(sf::VideoMode(config.screenWidth(),config.screenHeight()),"Projection");
    window.clear(sf::Color::Black);
    window.display();
    sf::Clock clock;

    Scene* scene = new LightTrailScene(config,
                                       new LightSourceVectorRepository(),
                                       new LightTrailVectorRepository(),
                                       new GravityPointVectorRepository(),
                                       new ColorHoleVectorRepository(),
                                       new LightPersonMapRepository()
    );

    while(window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float dt = clock.restart().asSeconds();
        scene->update(dt);

        window.clear(sf::Color::Black);
        scene->draw(window);


        window.display();
    }

    return 0;
}