#include "BothPaddlesControlledCondition.h"
#include <iostream>

BothPaddlesControlledCondition::BothPaddlesControlledCondition(
	std::shared_ptr<Paddle> p1,
	std::shared_ptr<Paddle> p2,
	PongConfiguration config,
	std::shared_ptr<Ball> ball
) : p1(p1), p2(p2),config(config), ball(ball) {}

int BothPaddlesControlledCondition::check(float dt, std::vector<Action*> &actions) {
	// If both paddles are being controlled
  if (p1->isControlled == true && p2->isControlled == true) {
		// If the game has already started, launch ball and continue
		if (!gameStarted) {
			gameStarted = true;
			std::cout << "Game started" << std::endl;
		}

	} else {
		if (gameStarted) {
			if (interactionTimer <= 500) {
				interactionTimer++;

			} else {
				interactionTimer = 0;
				gameStarted = false;
				std::cout << "Game ended" << std::endl;
				actions.push_back(
					static_cast<Action*>(new RestartBallAction(ball,true,config))
				);
				return 1;
			}
		}
		else {
			actions.push_back(
				static_cast<Action*>(new RestartBallAction(ball,true,config))
			);
			return 1;
		}
		// possibly add countdown
		// display text
		// do not launch ball
	}

  return 0;
}
