//
// Created by Wouter Posdijk on 08/06/16.
//

#include <time.h>
#include <cstdlib>
#include <sstream>
#include "../../src/Scene/LightTrail/Configuration/LightTrailConfiguration.h"
#include "../../src/Scene/LightTrail/LightTrailScene.h"
#include "../../src/Scene/LightTrail/Repositories/LightsSceneVectorRepositories.h"

int main(int argc, char* argv[]){
    srand(static_cast<unsigned int>(time(NULL)));

    LightTrailConfiguration config = LightTrailConfiguration::readFromFile(argv[1]);

    int controllercount = 1;
    if(argc == 3){
        std::istringstream ss(argv[2]);
        ss >> controllercount;
    }

    Scene* scene = new LightTrailScene(config,
                                       new LightSourceVectorRepository(),
                                       new LightTrailVectorRepository(),
                                       new GravityPointVectorRepository(),
                                       new ColorHoleVectorRepository(),
                                       new LightPersonMapRepository()
    );

    sf::RenderWindow window(sf::VideoMode(config.screenWidth(),config.screenHeight()),"Projection");
    window.clear(sf::Color::Black);
    window.setFramerateLimit(60);
    window.display();
    sf::Clock clock;

    std::vector<Person> people;
    float xstep = config.screenWidth()/4.f;
    float ystep = config.screenHeight()/4.f;

    switch(controllercount){
        case 1:
            people.push_back(Person(Vector2(xstep,ystep*2),Participant));
            people.push_back(Person(Vector2(xstep*3,ystep*2),Participant));
            break;
        case 2:
            people.push_back(Person(Vector2(xstep,ystep),Participant));
            people.push_back(Person(Vector2(xstep*3,ystep),Participant));
            people.push_back(Person(Vector2(xstep,ystep*3),Participant));
            people.push_back(Person(Vector2(xstep*3,ystep*3),Participant));
            break;
        case 3:
            people.push_back(Person(Vector2(xstep,ystep),Participant));
            people.push_back(Person(Vector2(xstep*3,ystep),Participant));
            people.push_back(Person(Vector2(xstep,ystep*2),Participant));
            people.push_back(Person(Vector2(xstep*3,ystep*2),Participant));
            people.push_back(Person(Vector2(xstep,ystep*3),Participant));
            people.push_back(Person(Vector2(xstep*3,ystep*3),Participant));
            break;
        case 4:
            people.push_back(Person(Vector2(xstep,ystep),Participant));
            people.push_back(Person(Vector2(xstep*2,ystep),Participant));
            people.push_back(Person(Vector2(xstep*3,ystep),Participant));
            people.push_back(Person(Vector2(xstep,ystep*2),Participant));
            people.push_back(Person(Vector2(xstep*3,ystep*2),Participant));
            people.push_back(Person(Vector2(xstep,ystep*3),Participant));
            people.push_back(Person(Vector2(xstep*2,ystep*3),Participant));
            people.push_back(Person(Vector2(xstep*3,ystep*3),Participant));
            break;
    }


    while(window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float dt = clock.restart().asSeconds();

        for(int i=0;i<controllercount;++i){
            float x = sf::Joystick::getAxisPosition(i,sf::Joystick::Axis::X)*3.f*dt;
            float y = sf::Joystick::getAxisPosition(i,sf::Joystick::Axis::Y)*3.f*dt;
            people[2*i].setLocation(people[2*i].getLocation()+Vector2(x,y));

            x = sf::Joystick::getAxisPosition(i,sf::Joystick::Axis::U)*3.f*dt;
            y = sf::Joystick::getAxisPosition(i,sf::Joystick::Axis::V)*3.f*dt;
            people[2*i+1].setLocation(people[2*i+1].getLocation()+Vector2(x,y));
        }

        scene->updatePeople(people);
        scene->update(dt);

        window.clear(sf::Color::Black);
        scene->draw(window);


        window.display();
    }

    return 0;
}