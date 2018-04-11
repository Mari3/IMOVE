#ifndef IMOVE_EXAMPLESCENE_H
#define IMOVE_EXAMPLESCENE_H

#include "../Scene.h"
#include "../SceneConfiguration.h"
#include "CircleRepository.h"

class ExampleScene : public Scene{
private:
  // Configuration of parameters used in the scene
  SceneConfiguration sceneConfig;
  // Collection of circles to be drawn
  CircleRepository* circles;
  // Processing of detected people
  void processPeople() override;

public:
  // Constructor
	ExampleScene(SceneConfiguration config);
  // Function to draw the scene
	void draw(sf::RenderTarget &target) override;
};

#endif //IMOVE_EXAMPLESCENE_H
