#include <iostream>
#include <string>
#include "PongScene.h"
#include "Conditions/PersonEnteredZoneCondition.h"
#include "Conditions/ScoredCondition.h"
#include "Conditions/BallHitsPaddleCondition.h"
#include "Actions/MoveBallAction.h"
#include "Conditions/BothPaddlesControlledCondition.h"

PongScene::PongScene(PongConfiguration config)
:
ball(new Ball()),
p1(new Paddle()),
p2(new Paddle()),
score(new Score()),
people(new PongPersonMapRepository()),
config(config)
 {
	//initialize

	if(!font.loadFromFile("imove_scene/res/pong/ARCADECLASSIC.TTF")){
		std::cerr << "Error loading font" << std::endl;
	}

	ball->pos.x = config.screenWidth/2;
	ball->pos.y = config.screenHeight/2;
	ball->velocity.x = config.ballSpeed;

	p1->x = config.controlRange;
	p1->y = config.screenHeight/2;
	p2->x = config.screenWidth-config.controlRange;
	p2->y = config.screenHeight/2;

	conditions.push_back(std::unique_ptr<Condition>(
		static_cast<Condition*>(new PersonEnteredZoneCondition(people,p1,p2,config))
	));
	conditions.push_back(std::unique_ptr<Condition>(
		static_cast<Condition*>(new BallHitsPaddleCondition(p1,p2,ball,config))
	));
	conditions.push_back(std::unique_ptr<Condition>(
		static_cast<Condition*>(new ScoredCondition(ball,score,config))
	));
  conditions.push_back(std::unique_ptr<Condition>(
    static_cast<Condition*>(new BothPaddlesControlledCondition(p1,p2,config,ball))
  ));


	actions.push_back(std::unique_ptr<Action>(
		static_cast<Action*>(new MoveBallAction(ball,config))
	));
}

void PongScene::draw(sf::RenderTarget &target) {
	target.clear(sf::Color::Black);

	sf::RectangleShape p1Shape(sf::Vector2f(config.bt,config.bt*10));
	p1Shape.setPosition(sf::Vector2f(p1->x-config.bt/2,p1->y-config.bt*5));
	sf::RectangleShape p2Shape(sf::Vector2f(config.bt,config.bt*10));
	p2Shape.setPosition(sf::Vector2f(p2->x,p2->y-config.bt*5));
	target.draw(p1Shape);
	target.draw(p2Shape);

	sf::RectangleShape ballShape(sf::Vector2f(config.bt,config.bt));
	ballShape.setPosition(sf::Vector2f(ball->pos.x-config.bt/2,ball->pos.y-config.bt/2));
	target.draw(ballShape);

	sf::Text score1(std::to_string(score->player1),font,150);
	score1.setPosition(config.screenWidth/2-130,config.screenHeight-20);
  score1.rotate(180);
	sf::Text score2(std::to_string(score->player2),font,150);
	score2.setPosition(config.screenWidth/2+220,config.screenHeight-20);
  score2.rotate(180);
	target.draw(score1);
	target.draw(score2);

	for(unsigned int i=config.bt/2;i<config.screenHeight;i+=config.bt*2){
		ballShape.setPosition(config.screenWidth/2-config.bt/2,i);
		target.draw(ballShape);
	}

  sf::RectangleShape borderTop(sf::Vector2f(config.screenWidth,10));
  target.draw(borderTop);
  sf::RectangleShape borderBottom(sf::Vector2f(config.screenWidth,10));
  borderBottom.setPosition(0, config.screenHeight-12);
  target.draw(borderBottom);

	sf::RectangleShape all(sf::Vector2f(config.screenWidth,config.screenHeight));
	all.setFillColor(sf::Color(0,0,0,0));
	all.setOutlineColor(sf::Color::Red);
	all.setOutlineThickness(5);
	target.draw(all);
}

void PongScene::processPeople(){
	if(!peopleQueue.empty()) {
		scene_interface::People newPeople = peopleQueue.front();
		peopleQueue.pop();

		for(unsigned int i=0; i < newPeople.size(); ++i){
			scene_interface::Person person = newPeople[i];
			unsigned int id = person.getId();

			if(people->has(id)) {
				std::shared_ptr<PongPerson> pPerson = people->get(id);
				scene_interface::Location llocation = person.getLocation();
                pPerson->location.x = llocation.getX();
				pPerson->location.y = llocation.getY();
                pPerson->person_type = person.getPersonType();
			} else {
				scene_interface::Location llocation = person.getLocation();
				people->add(
					std::shared_ptr<PongPerson>(
						new PongPerson(id, Vector2(llocation.getX(), llocation.getY()),
						person.getPersonType())
					)
				);
			}
		}
	}
}
