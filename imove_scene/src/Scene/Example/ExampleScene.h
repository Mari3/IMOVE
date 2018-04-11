#ifndef IMOVE_EXAMPLESCENE_H
#define IMOVE_EXAMPLESCENE_H

#include "../Scene.h"
#include "../SceneConfiguration.h"
#include "CircleRepository.h"

class ExampleScene : public Scene{
private:
  void processPeople() override;
  SceneConfiguration sceneConfig;
  CircleRepository* circles;
public:
	ExampleScene(SceneConfiguration config);
	void draw(sf::RenderTarget &target) override;
};

#endif //IMOVE_EXAMPLESCENE_H
