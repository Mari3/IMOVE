#include "ScoredCondition.h"
#include "../Actions/RestartBallAction.h"

ScoredCondition::ScoredCondition(
	std::shared_ptr<Ball> ball, std::shared_ptr<Score> score, PongConfiguration config) :
ball(ball), score(score), config(config) {}

int ScoredCondition::check(float dt, std::vector<Action*> &actions)
{
	if(ball->pos.x > config.screenWidth-config.controlRange){
		score->player1++;
		actions.push_back(
			static_cast<Action*>(new RestartBallAction(ball,true,config))
		);
		return 1;
	}
	if(ball->pos.x < config.controlRange){
		score->player2++;
		actions.push_back(
			static_cast<Action*>(new RestartBallAction(ball,false,config))
		);	
		return 1;
	}
	return 0;
}