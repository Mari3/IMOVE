#include "BallHitsPaddleCondition.h"
#include "math.h"

BallHitsPaddleCondition::BallHitsPaddleCondition(std::shared_ptr<Paddle> p1, std::shared_ptr<Paddle> p2,
		std::shared_ptr<Ball> ball, PongConfiguration config) : p1(p1), p2(p2), ball(ball), config(config) {}

int BallHitsPaddleCondition::check(float dt, std::vector<Action*> &actions)
{
	if(ball->pos.x < (p1->x+config.bt/2) && ball->pos.y > (p1->y-config.bt*5) && ball->pos.y < (p1->y+config.bt*5)){
		ball->pos.x = p1->x+config.bt/2;
		float angle = (ball->pos.y-p1->y)/(static_cast<float>(config.bt)*5.f)*static_cast<float>(config.maxAngle)/180.f*M_PI;
		ball->velocity.x = static_cast<float>(config.ballSpeed)*cosf(angle);
		ball->velocity.y = static_cast<float>(config.ballSpeed)*sinf(angle);
	}
	else if(ball->pos.x > (p2->x-config.bt/2) && ball->pos.y > (p2->y-config.bt*5) && ball->pos.y < (p2->y+50)){
		ball->pos.x = p2->x-config.bt/2;
		float angle = (ball->pos.y-p2->y)/(static_cast<float>(config.bt)*5.f)*static_cast<float>(config.maxAngle)/180.f*M_PI;
		ball->velocity.x = -static_cast<float>(config.ballSpeed)*cosf(angle);
		ball->velocity.y = static_cast<float>(config.ballSpeed)*sinf(angle);
	}
	return 0;
}