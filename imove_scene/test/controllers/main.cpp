//
// Created by Wouter Posdijk on 08/06/16.
//

#include <time.h>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include "../../src/Scene/Pong/PongConfiguration.h"
#include "../../src/Scene/Pong/PongScene.h"
#include "../../src/Scene/LightTrail/Repositories/LightsSceneVectorRepositories.h"

namespace si = scene_interface;

class TestingPerson : public si::Person{
private:
    static unsigned int counter;
public:
    TestingPerson(const Vector2 &location) : Person(counter, si::Location(location.x,location.y),
                                                    si::Person::Bystander, si::Person::Moving) {
        counter++;
    }
    void setLocation(const Vector2 &location){
        this->location = si::Location(location.x,location.y);
    }

    void setType(si::Person::PersonType type){
    	this->person_type = type;
	}

    Vector2 getLoc() {
        return Vector2(location.getX(),location.getY());
    }
};
unsigned int TestingPerson::counter = 0;

int main(int argc, char* argv[]){
    srand(static_cast<unsigned int>(time(NULL)));

    PongConfiguration config = PongConfiguration::readFromFile(argv[1]);

    int controllercount = 1;
    if(argc == 3){
        std::istringstream ss(argv[2]);
        ss >> controllercount;
    }

    /*Scene* scene = new LightTrailScene(config,
                                       new LightSourceVectorRepository(),
                                       new LightTrailVectorRepository(),
                                       new GravityPointVectorRepository(),
                                       new ColorHoleVectorRepository(),
                                       new LightPersonMapRepository()
    );*/

    Scene* scene = new PongScene(config);

    sf::RenderWindow window(sf::VideoMode(config.screenWidth+200,config.screenHeight+200),"Projection");
    window.clear(sf::Color::White);
    window.setFramerateLimit(60);
    window.setView(sf::View(sf::FloatRect(-100,-100,config.screenWidth+200,config.screenHeight+200)));
    window.display();
    sf::Clock clock;

    float xstep = config.screenWidth/4.f;
    float ystep = config.screenHeight/4.f;

    std::vector<TestingPerson> people;

    /*switch(controllercount){
        case 1:
            people.push_back(TestingPerson(Vector2(xstep,ystep*2)));
            people.push_back(TestingPerson(Vector2(xstep*3,ystep*2)));
            break;
        case 2:
            people.push_back(TestingPerson(Vector2(xstep,ystep)));
            people.push_back(TestingPerson(Vector2(xstep*3,ystep)));
            people.push_back(TestingPerson(Vector2(xstep,ystep*3)));
            people.push_back(TestingPerson(Vector2(xstep*3,ystep*3)));
            break;
        case 3:
            people.push_back(TestingPerson(Vector2(xstep,ystep)));
            people.push_back(TestingPerson(Vector2(xstep*3,ystep)));
            people.push_back(TestingPerson(Vector2(xstep,ystep*2)));
            people.push_back(TestingPerson(Vector2(xstep*3,ystep*2)));
            people.push_back(TestingPerson(Vector2(xstep,ystep*3)));
            people.push_back(TestingPerson(Vector2(xstep*3,ystep*3)));
            break;
        case 4:
            people.push_back(TestingPerson(Vector2(xstep,ystep)));
            people.push_back(TestingPerson(Vector2(xstep*2,ystep)));
            people.push_back(TestingPerson(Vector2(xstep*3,ystep)));
            people.push_back(TestingPerson(Vector2(xstep,ystep*2)));
            people.push_back(TestingPerson(Vector2(xstep*3,ystep*2)));
            people.push_back(TestingPerson(Vector2(xstep,ystep*3)));
            people.push_back(TestingPerson(Vector2(xstep*2,ystep*3)));
            people.push_back(TestingPerson(Vector2(xstep*3,ystep*3)));
            break;
    }*/

    bool timerDone = false;
    Timer timer(5.f);

    while(window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float dt = clock.restart().asSeconds();

        if(timerDone){
                float xpos = 0, ypos = 0;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                    xpos += 100;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                    xpos -= 100;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                    ypos -= 100;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                    ypos += 100;

                float x = people[0].getLoc().x+xpos*3.f*dt;
                float y = people[0].getLoc().y+ypos*3.f*dt;
                people[0].setLocation(Vector2(x,y));

                if(x > config.screenWidth+110 || x < -110 || y > config.screenHeight+110 || y < -110){
                    people[0].setType(si::Person::None);
                }
                else if(x > config.screenWidth || x < 0 || y > config.screenHeight || y < 0){
                    people[0].setType(si::Person::Bystander);
                }else{
                    people[0].setType(si::Person::Participant);
                }

                xpos = 0; ypos = 0;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    xpos += 100;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    xpos -= 100;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    ypos -= 100;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    ypos += 100;

                x = people[1].getLoc().x+xpos*3.f*dt;
                y = people[1].getLoc().y+ypos*3.f*dt;
        
                if(x > config.screenWidth+110 || x < -110 || y > config.screenHeight+110 || y < -110){
                    people[1].setType(si::Person::None);
                }
                else if(x > config.screenWidth || x < 0 || y > config.screenHeight || y < 0){
                    people[1].setType(si::Person::Bystander);
                }else{
                    people[1].setType(si::Person::Participant);
                }

                people[1].setLocation(Vector2(x,y));

            si::People scenePeople;
            for(auto &person : people){
                scenePeople.push_back(*(&person));
            }

            scene->updatePeople(scenePeople);
        }
        else if(timer.update(dt)){
        
            timerDone = true;
            people.push_back(TestingPerson(Vector2(-100,ystep*2)));
            people.push_back(TestingPerson(Vector2(xstep*3,config.screenHeight+100)));
            
            
        }
        
        scene->update(dt);

        window.clear(sf::Color::White);
        scene->draw(window);
        for(auto &person : people){
            sf::CircleShape circle(4.f);
            circle.setFillColor(sf::Color::Cyan);
            circle.setPosition(person.getLoc().x-2,person.getLoc().y-2);
            window.draw(circle);
        }


        window.display();
    }

    return 0;
}
