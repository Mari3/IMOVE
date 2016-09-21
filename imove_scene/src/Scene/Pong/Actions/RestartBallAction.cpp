#include "RestartBallAction.h"

RestartBallAction::RestartBallAction(std::shared_ptr<Ball> ball, bool left, PongConfiguration config) :
	ball(ball), left(left), timer(2.f), config(config) {
	ball->velocity.x = 0;
	ball->velocity.y = 0;
	ball->pos.x = config.screenWidth/2;
	ball->pos.y = config.screenHeight/2;
}

bool RestartBallAction::isDone(std::vector<Action*> &followUp) {
	return done;
}

void RestartBallAction::execute(float dt) {
	if(timer.update(dt)){
		if(left){
			ball->velocity.x = -config.ballSpeed;
		}else{
			ball->velocity.x = config.ballSpeed;
		}
		done = true;
	}
}