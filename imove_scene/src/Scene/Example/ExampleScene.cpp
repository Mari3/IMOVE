#include "ExampleScene.h"

ExampleScene::ExampleScene(SceneConfiguration config): sceneConfig(config), circles(new CircleRepository()) {}

void ExampleScene::draw(sf::RenderTarget &target) {
  target.clear(sf::Color::Black);
  sf::RectangleShape all(sf::Vector2f(sceneConfig.screenWidth,sceneConfig.screenHeight));
	all.setFillColor(sf::Color(0,0,0,0));
	all.setOutlineColor(sf::Color::Red);
	all.setOutlineThickness(5);
	target.draw(all);


  //sf::CircleShape shape(sceneConfig.radius);
  //target.draw(shape);
  circles->for_each([&](std::shared_ptr<Circle> circle) {
      sf::CircleShape c(sceneConfig.radius);
      c.setFillColor(circle->color);
      c.setPosition(circle->location.x, circle->location.y);
      target.draw(c);
  });
}

void ExampleScene::processPeople() {
  if (!peopleQueue.empty()) {
		scene_interface::People newPeople = peopleQueue.front();
		peopleQueue.pop();

		for (unsigned int i = 0; i < newPeople.size(); ++i) {
			scene_interface::Person person = newPeople[i];
			unsigned int id = person.getId();

      if (person.getPersonType() == scene_interface::Person::PersonType::Participant) {
        if(circles->has(id)) {
          std::shared_ptr<Circle> circle = circles->get(id);
          scene_interface::Location newLocation = person.getLocation();
          circle->location.x = newLocation.getX();
          circle->location.y = newLocation.getY();
        } else {
          scene_interface::Location location = person.getLocation();
          circles->add(
            std::shared_ptr<Circle>(
              new Circle(id, Vector2(location.getX(), location.getY()), sf::Color::White)
            )
          );
        }
      } else {
        if(circles->has(id)) {
          std::shared_ptr<Circle> circle = circles->get(id);
          circles->scheduleForRemoval(circle);
        }
      }
		}
	}
  circles->removeAll();
}
