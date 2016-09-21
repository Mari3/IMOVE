#include "MoveBallAction.h"

MoveBallAction::MoveBallAction(std::shared_ptr<Ball> ball, PongConfiguration config) : ball(ball), config(config){}

bool MoveBallAction::isDone(std::vector<Action*> &followUp){
	return false;
}

void MoveBallAction::execute(float dt){
	ball->pos.x += ball->velocity.x*dt;
	ball->pos.y += ball->velocity.y*dt;
	if(ball->pos.y > config.screenHeight){
		ball->pos.y = config.screenHeight;
		ball->velocity.y *= -1;
	}else if(ball->pos.y < 0){
		ball->pos.y = 0;
		ball->velocity.y *= -1;
	}
}