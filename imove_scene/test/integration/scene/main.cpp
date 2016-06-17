//
// Created by Wouter Posdijk on 25/05/16.
//

#include <sstream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "../../../src/Scene/LightTrail/Configuration/LightTrailSceneConfiguration.h"
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
    void setType(si::Person::PersonType type){
        this->person_type = type;
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

    MixingFailsScenario(const LightTrailSceneConfiguration& config): timer(10.f){
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

    MixingScenario(const LightTrailSceneConfiguration& config){
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

    ManyScenario(const LightTrailSceneConfiguration &config){
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

    FirstPersonScenario(const LightTrailSceneConfiguration &config) : timer(5.f) {
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

    RestartAlternatingScenario(const LightTrailSceneConfiguration &config) : timer(10.f) {
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

    float height;
    bool done = false, done2 = false;

    BystanderScenario(const LightTrailSceneConfiguration &config, Scene *scene) {
        for(int i=0;i<300;++i)
            scene->update(.1f);
        people.push_back(TestingPerson(0,
                                       si::Location(config.screenWidth()/2,config.screenHeight()+100),
                                       si::Person::PersonType::Bystander,
                                       si::Person::MovementType::Moving
        ));
        height = config.screenHeight();
    }

    void update(float dt) override {
        if(!done) {
            si::Location p0loc = people[0].getLocation();
            if (p0loc.getY() < height) {
                people.clear();
                people.push_back(TestingPerson(0,
                                               p0loc,
                                               si::Person::PersonType::Participant,
                                               si::Person::MovementType::Moving
                ));
            }
            people[0].setLocation(si::Location(p0loc.getX(),p0loc.getY()-20.f*dt));
            if(p0loc.getY() < height/2){
                done = true;
            }
        }else if(!done2){
            si::Location p0loc = people[0].getLocation();
            people[0].setLocation(si::Location(p0loc.getX(),p0loc.getY()+20.f*dt));
            if(p0loc.getY() > height){
                people[0].setType(si::Person::Bystander);
            }
            if(p0loc.getY() > height+120) {
                done2 = true;
                people[0].setType(si::Person::None);
            }
        }
    }

};

struct ColorHoleScenario : public Scenario {

    float thresh;
    Timer timer;

    ColorHoleScenario(const LightTrailSceneConfiguration& config) : timer(20.f) {
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

struct SourceColorScenario : public Scenario {

    float thresh;

    SourceColorScenario(const LightTrailSceneConfiguration& config) {
        people.push_back(TestingPerson(0,
                                       si::Location(20,config.screenHeight()/2),
                                       scene_interface::Person::Participant,
                                       scene_interface::Person::Moving
        ));
        thresh = config.screenHeight()-50;
    }

    void update(float dt) override {
        si::Location p0loc = people[0].getLocation();
        if(p0loc.getY() < thresh){
            people[0].setLocation(si::Location(p0loc.getX(), 20.f * dt + p0loc.getX()));
        }
    }

};

struct StandingStillScenario : public Scenario {

    Timer timer;

    StandingStillScenario(const LightTrailSceneConfiguration& config) : timer (30.f) {
        people.push_back(TestingPerson(0,
                                       si::Location(config.screenWidth()/2,config.screenHeight()/2),
                                       si::Person::Participant,
                                       si::Person::Moving
        ));
    }

    void update(float dt) override {
        if(timer.update(dt)){
            si::Location loc = people[0].getLocation();
            people.clear();
            people.push_back(TestingPerson(0,
                                           loc,
                                           si::Person::Participant,
                                           si::Person::StandingStill
            ));
        }
    }

};

struct ManyBystandersScenario : public Scenario {
    Timer addTimer, removeTimer;
    float x,y;

    unsigned int counter = 1;
    unsigned int removeCounter = 0;

    ManyBystandersScenario(const LightTrailSceneConfiguration& config) : addTimer(10.f,true), removeTimer(30.f,true)
    {
        x = config.screenWidth()/10;
        y = config.screenHeight()+100;
        people.push_back(TestingPerson(counter,
                                       si::Location(counter*x,y),
                                       si::Person::PersonType::Bystander,
                                       si::Person::MovementType::Moving
        ));
        counter++;
    }

    void update(float dt) override {
        if(addTimer.update(dt)){
            people.push_back(TestingPerson(counter,
                                           si::Location(counter*x,y),
                                           si::Person::PersonType::Bystander,
                                           si::Person::MovementType::Moving
            ));
            counter++;
        }
        if(removeTimer.update(dt)){
            people[removeCounter].setType(si::Person::PersonType::None);
            removeCounter++;
            people[removeCounter].setType(si::Person::PersonType::None);
            removeCounter++;
        }
    }
};

namespace SceneIntegration {
    enum ScenarioCode {
        Standard,
        Mixing,
        MixingFails,
        Many,
        FirstPerson,
        RestartAlternating,
        Bystander,
        ColorHole,
        SourceColor,
        StandingStill,
        ManyBystanders
    };
}

int main(int argc, char** argv){

    srand(static_cast<unsigned int>(time(NULL)));

    LightTrailSceneConfiguration config = LightTrailSceneConfiguration::readFromFile(argv[1]);

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
    switch(scenarioCode){
        case SceneIntegration::Standard:
            scenario = new Scenario();
            break;
        case SceneIntegration::Mixing:
            scenario = new MixingScenario(config);
            break;
        case SceneIntegration::MixingFails:
            scenario = new MixingFailsScenario(config);
            break;
        case SceneIntegration::Many:
            scenario = new ManyScenario(config);
            break;
        case SceneIntegration::FirstPerson:
            scenario = new FirstPersonScenario(config);
            break;
        case SceneIntegration::RestartAlternating:
            scenario = new RestartAlternatingScenario(config);
            break;
        case SceneIntegration::Bystander:
            scenario = new BystanderScenario(config,scene);
            break;
        case SceneIntegration::ColorHole:
            scenario = new ColorHoleScenario(config);
            break;
        case SceneIntegration::SourceColor:
            scenario = new SourceColorScenario(config);
            break;
        case SceneIntegration::StandingStill:
            scenario = new StandingStillScenario(config);
            break;
        case SceneIntegration::ManyBystanders:
            scenario = new ManyBystandersScenario(config);
            break;
    }

    sf::RenderWindow window(sf::VideoMode(config.screenWidth(),config.screenHeight()),"Projection");
    window.clear(sf::Color::White);
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

        window.clear(sf::Color::White);
        scene->draw(window);


        window.display();
    }

    return 0;
}
