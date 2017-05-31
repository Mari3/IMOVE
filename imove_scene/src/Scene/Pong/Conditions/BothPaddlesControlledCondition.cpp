#include "BothPaddlesControlledCondition.h"
#include <iostream>

BothPaddlesControlledCondition::BothPaddlesControlledCondition(
	std::shared_ptr<Paddle> p1,
	std::shared_ptr<Paddle> p2 /*,
	PongConfiguration config*/
) : p1(p1), p2(p2) /*,config(config)*/ {}

int BothPaddlesControlledCondition::check(float dt, std::vector<Action*> &actions) {
	// If both paddles are being controlled
  if (p1->isControlled == true && p2->isControlled == true) {
		// If the game has already started, launch ball and continue
		if (gameStarted) {
			// launch ball
		} else {
			// start game
			// reset score
			gameStarted = true;
		}
	} else {
		gameStarted = false;
		// possibly add countdown
		// display text
		// do not launch ball
	}

  return 0;
}
