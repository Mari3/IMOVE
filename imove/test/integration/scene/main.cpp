//
// Created by Wouter Posdijk on 25/05/16.
//

#include <sstream>
#include "SFML/Graphics.hpp"
#include "../../../src/Scene/LightTrail/LightTrailConfiguration.h"
#include "../../../src/Scene/LightTrail/LightTrailScene.h"
#include "../../../src/Scene/LightTrail/Repositories/LightsSceneVectorRepositories.h"
#include "../../../src/Scene/Util/Timer.h"

struct Scenario{
    vector<Person> people;
    virtual void update(float dt) = 0;
};

struct StandardScenario : public Scenario {

    void update(float dt) override {
        return;
    }
};

struct MixingFailsScenario : public Scenario {

    float thresh;
    Timer timer;
    bool timerDone = false;

    MixingFailsScenario(const LightTrailConfiguration& config): timer(10.f){
        unsigned int y = config.screenHeight()/2;
        thresh = config.screenWidth()/4.f;
        people.push_back(Person(Vector2(0,y),Participant));
        people.push_back(Person(Vector2(config.screenWidth(),y),Participant));
    }

    void update(float dt) override {
        Vector2 p0loc = people[0].getLocation();
        Vector2 p1loc = people[1].getLocation();
        if(timerDone){
            people[0].setLocation(people[0].getLocation() + Vector2(-20.f * dt, 0));
            people[1].setLocation(people[1].getLocation() + Vector2(20.f * dt, 0));
        }else if(p0loc.x < thresh) {
            people[0].setLocation(people[0].getLocation() + Vector2(20.f * dt, 0));
            people[1].setLocation(people[1].getLocation() + Vector2(-20.f * dt, 0));
        }else{
            if(timer.update(dt)){
                timerDone = true;
            }
        }
    }
};

struct MixingScenario : public Scenario {

    float thresh;

    MixingScenario(const LightTrailConfiguration& config){
        unsigned int y = config.screenHeight()/2;
        thresh = config.screenWidth()/3.f;
        people.push_back(Person(Vector2(0,y),Participant));
        people.push_back(Person(Vector2(config.screenWidth(),y),Participant));
    }

    void update(float dt) override {
        Vector2 p0loc = people[0].getLocation();
        Vector2 p1loc = people[1].getLocation();
        if(p0loc.x < thresh) {
            people[0].setLocation(people[0].getLocation() + Vector2(20.f * dt, 0));
            people[1].setLocation(people[1].getLocation() + Vector2(-20.f * dt, 0));
        }
    }
};

int main(int argc, char** argv){

    srand(static_cast<unsigned int>(time(NULL)));

    LightTrailConfiguration config = LightTrailConfiguration::readFromFile(argv[1]);

    int scenarioCode = 0;
    if(argc == 3){
        istringstream ss(argv[2]);
        ss >> scenarioCode;
    }

    Scenario* scenario;
    if(scenarioCode == 0){
        scenario = new StandardScenario();
    }else if(scenarioCode == 1){
        scenario = new MixingScenario(config);
    }else if(scenarioCode == 2){
        scenario = new MixingFailsScenario(config);
    }

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
        scenario->update(dt);
        scene->updatePeople(scenario->people);
        scene->update(dt);

        window.clear(sf::Color::Black);
        scene->draw(window);


        window.display();
    }

    return 0;
}