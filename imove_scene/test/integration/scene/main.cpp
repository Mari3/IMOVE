//
// Created by Wouter Posdijk on 25/05/16.
//

#include <sstream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "../../../src/Scene/LightTrail/LightTrailConfiguration.h"
#include "../../../src/Scene/LightTrail/LightTrailScene.h"
#include "../../../src/Scene/LightTrail/Repositories/LightsSceneVectorRepositories.h"
#include "../../../src/Scene/Util/Timer.h"

namespace si = scene_interface;

class TestingPerson : public si::Person{

public:
    TestingPerson(unsigned int id, const scene_interface::Location &location, PersonType person_type,
                  MovementType movement_type) : Person(id, location, person_type, movement_type) { }
    void setLocation(const si::Location &location){
        this->location = location;
    }
};

struct Scenario{
    std::vector<TestingPerson> people;
    virtual void update(float dt) {};
};

struct MixingFailsScenario : public Scenario {

    float thresh;
    Timer timer;
    bool timerDone = false;

    MixingFailsScenario(const LightTrailConfiguration& config): timer(10.f){
        unsigned int y = config.screenHeight()/2;
        thresh = config.screenWidth()/4.f;
        people.push_back(TestingPerson(0,si::Location(0,y),si::Person::PersonType::Participant,si::Person::MovementType::Moving));
        people.push_back(TestingPerson(1,si::Location(config.screenWidth(),y),si::Person::PersonType::Participant,si::Person::MovementType::Moving));
    }

    void update(float dt) override {
        si::Location p0loc = people[0].getLocation();
        si::Location p1loc = people[1].getLocation();
        //Vector2 p1loc = people[1].getLocation();
        if(timerDone){
            people[0].setLocation(si::Location(-20.f * dt + p0loc.getX(), p0loc.getY()));
            people[1].setLocation(si::Location(20.f * dt + p1loc.getX(), p1loc.getY()));
        }else if(p0loc.getX() < thresh) {
            people[0].setLocation(si::Location(20.f * dt + p0loc.getX(), p0loc.getY()));
            people[1].setLocation(si::Location(-20.f * dt + p1loc.getX(), p1loc.getY()));
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
        thresh = 340.f;
        people.push_back(TestingPerson(0,si::Location(0,y),si::Person::PersonType::Participant,si::Person::MovementType::Moving));
        people.push_back(TestingPerson(1,si::Location(config.screenWidth(),y),si::Person::PersonType::Participant,si::Person::MovementType::Moving));
    }

    void update(float dt) override {
        si::Location p0loc = people[0].getLocation();
        si::Location p1loc = people[1].getLocation();
        if(p1loc.getX()-p0loc.getX() > 320.f) {
            people[0].setLocation(si::Location(20.f * dt + p0loc.getX(), p0loc.getY()));
            people[1].setLocation(si::Location(-20.f * dt + p1loc.getX(), p1loc.getY()));
        }
    }
};

struct ManyScenario : public Scenario {

    ManyScenario(const LightTrailConfiguration &config){
        util::Range xRange(0,config.screenWidth());
        util::Range yRange(0,config.screenHeight());
        for(int i=0;i<10;++i){
            people.push_back(TestingPerson(i,si::Location(xRange.drawRandom(),yRange.drawRandom()),
                                           si::Person::PersonType::Participant,
                                           si::Person::MovementType::Moving
            ));
        }
    }

};

struct FirstPersonScenario : public Scenario {

    Timer timer;
    bool timerDone = false;
    bool timer2Done = false;
    float sh;

    FirstPersonScenario(const LightTrailConfiguration &config) : timer(5.f) {
        sh = config.screenHeight();
    }

    void update(float dt) override {
        if(!timerDone){
            if(timer.update(dt)){
                people.push_back(TestingPerson(0,
                                               si::Location(0,sh/2.f),
                                               si::Person::PersonType::Participant,
                                               si::Person::MovementType::Moving
                ));
                timerDone = true;
                timer.restart(20.f);
            }
        }else{
            si::Location p0loc = people[0].getLocation();
            people[0].setLocation(si::Location(20.f * dt + p0loc.getX(), p0loc.getY()));
            if(!timer2Done && timer.update(dt)){
                people.push_back(TestingPerson(1,
                                               si::Location(50,sh/2.f),
                                               si::Person::PersonType::Participant,
                                               si::Person::MovementType::StandingStill
                ));
                timer2Done = true;
            }
        }
    }

};

struct RestartAlternatingScenario : public Scenario {

    Timer timer;
    bool timerDone = false;
    bool timer2Done = false;
    float sh;

    RestartAlternatingScenario(const LightTrailConfiguration &config) : timer(10.f) {
        sh = config.screenHeight();
    }

    void update(float dt) override {
        if(!timerDone){
            if(timer.update(dt)){
                people.push_back(TestingPerson(0,
                                               si::Location(0,sh/2.f),
                                               si::Person::PersonType::Participant,
                                               si::Person::MovementType ::Moving
                ));
                timerDone = true;
                timer.restart(15.f);
            }
        }else if(!timer2Done){
            si::Location p0loc = people[0].getLocation();
            people[0].setLocation(si::Location(20.f * dt + p0loc.getX(), p0loc.getY()));
            if(timer.update(dt)){
                people.clear();
                people.push_back(TestingPerson(0,
                                               si::Location(0,0),
                                               si::Person::PersonType ::None,
                                               si::Person::MovementType ::Moving
                ));
                timer2Done = true;
            }
        }
    }

};

struct BystanderScenario : public Scenario {

    BystanderScenario(const LightTrailConfiguration &config, Scene *scene) {
        for(int i=0;i<300;++i)
            scene->update(.1f);
        people.push_back(TestingPerson(0,
                                       si::Location(config.screenWidth()/2,config.screenHeight()+100),
                                       si::Person::PersonType::Bystander,
                                       si::Person::MovementType::Moving
        ));
        people.push_back(TestingPerson(1,
                                       si::Location(config.screenWidth()/4,config.screenHeight()/2),
                                       si::Person::PersonType::Participant,
                                       si::Person::MovementType::StandingStill));
    }

};

struct ColorHoleScenario : public Scenario {

    float thresh;
    Timer timer;

    ColorHoleScenario(const LightTrailConfiguration& config) : timer(20.f) {
        srand(36);
        unsigned int y = config.screenHeight()/4*3;
        thresh = 340.f;
        people.push_back(TestingPerson(0,
                                       si::Location(config.screenWidth()/2,20),
                                       si::Person::PersonType::Participant,
                                       si::Person::MovementType::StandingStill
        ));
        people.push_back(TestingPerson(1,
                                       si::Location(0,y),
                                       si::Person::PersonType::Participant,
                                       si::Person::MovementType::Moving
        ));
        people.push_back(TestingPerson(2,
                                       si::Location(config.screenWidth(),y),
                                       si::Person::PersonType::Participant,
                                       si::Person::MovementType::Moving
        ));
    }

    void update(float dt) override {
        si::Location p0loc = people[1].getLocation();
        si::Location p1loc = people[2].getLocation();
        if(p1loc.getX()-p0loc.getX() > 320.f || timer.update(dt)) {
            if(p1loc.getX()-p0loc.getX() > 320.f) {
                people[1].setLocation(si::Location(20.f * dt + p0loc.getX(), p0loc.getY()));
                people[2].setLocation(si::Location(-20.f * dt + p1loc.getX(), p1loc.getY()));
            }
        }
    }

};

int main(int argc, char** argv){

    srand(static_cast<unsigned int>(time(NULL)));

    LightTrailConfiguration config = LightTrailConfiguration::readFromFile(argv[1]);

    int scenarioCode = 0;
    if(argc == 3){
    	std::istringstream ss(argv[2]);
        ss >> scenarioCode;
    }

    Scene* scene = new LightTrailScene(config,
                                       new LightSourceVectorRepository(),
                                       new LightTrailVectorRepository(),
                                       new GravityPointVectorRepository(),
                                       new ColorHoleVectorRepository(),
                                       new LightPersonMapRepository()
    );

    Scenario* scenario;
    if(scenarioCode == 0){
        scenario = new Scenario();
    }else if(scenarioCode == 1){
        scenario = new MixingScenario(config);
    }else if(scenarioCode == 2){
        scenario = new MixingFailsScenario(config);
    }else if(scenarioCode == 3){
        scenario = new ManyScenario(config);
    }else if(scenarioCode == 4){
        scenario = new FirstPersonScenario(config);
    }else if(scenarioCode == 5){
        scenario = new RestartAlternatingScenario(config);
    }else if(scenarioCode == 6){
        scenario = new BystanderScenario(config,scene);
    }else if(scenarioCode == 7){
        scenario = new ColorHoleScenario(config);
    }

    sf::RenderWindow window(sf::VideoMode(config.screenWidth(),config.screenHeight()),"Projection");
    window.clear(sf::Color::Black);
    window.setFramerateLimit(60);
    window.display();
    sf::Clock clock;

    while(window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float dt = clock.restart().asSeconds();
        scenario->update(dt);
        si::People people;
        for(auto &person : scenario->people){
            people.push_back(*(&person));
        }
        scene->updatePeople(people);
        scene->update(dt);

        window.clear(sf::Color::Black);
        scene->draw(window);


        window.display();
    }

    return 0;
}
