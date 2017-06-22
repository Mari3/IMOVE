#ifndef IMOVE_PONGSCENE_H
#define IMOVE_PONGSCENE_H

#include "../Scene.h"
#include "../../../../util/src/Vector2.h"
#include "PongPerson.h"
#include "PongConfiguration.h"

struct Paddle {
	float x, y, y_target, prev_target, velocity;
	bool isControlled, move_up;
};

struct Ball {
	Vector2 pos, velocity;
};

struct Score {
	int player1, player2;
};

class PongScene : public Scene{
private:
	std::shared_ptr<Ball> ball;
	std::shared_ptr<Paddle> p1, p2;
	std::shared_ptr<Score> score;
	PongPersonMapRepository* people;
	sf::Font font;
	PongConfiguration config;
public:
	PongScene(PongConfiguration config);
	void draw(sf::RenderTarget &target) override;
	void processPeople() override;
};

#endif //IMOVE_PONGSCENE_H
