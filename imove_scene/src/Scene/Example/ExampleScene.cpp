#include "ExampleScene.h"

ExampleScene::ExampleScene(SceneConfiguration config): sceneConfig(config), circles(new CircleRepository()) {}

void ExampleScene::draw(sf::RenderTarget &target) {
  // Clear the scene and color it black
  target.clear(sf::Color::Black);
  // Go over each circle in the circles repository and draw it
  circles->for_each([&](std::shared_ptr<Circle> circle) {
      sf::CircleShape c(sceneConfig.radius);
      c.setFillColor(circle->color);
      c.setPosition(circle->location.x, circle->location.y);
      target.draw(c);
  });
}

void ExampleScene::processPeople() {
  // Check if the people have been updated
  if (!peopleQueue.empty()) {
    // Get the updated people and pop the queue
		scene_interface::People newPeople = peopleQueue.front();
		peopleQueue.pop();

		for (unsigned int i = 0; i < newPeople.size(); ++i) {
			scene_interface::Person person = newPeople[i];
			unsigned int id = person.getId();

      // Only if the person is a participant (and is therefore located within the scene)
      // will their circle be updated or created
      if (person.getPersonType() == scene_interface::Person::PersonType::Participant) {
        // If the person was already in the scene and its circle is in the repository
        if(circles->has(id)) {
          // update the circle's location
          std::shared_ptr<Circle> circle = circles->get(id);
          scene_interface::Location newLocation = person.getLocation();
          circle->location.x = newLocation.getX();
          circle->location.y = newLocation.getY();
        } else {
          // create a new circle otherwise
          scene_interface::Location location = person.getLocation();
          circles->add(
            std::shared_ptr<Circle>(
              new Circle(id, Vector2(location.getX(), location.getY()), sf::Color::White)
            )
          );
        }
      } else {
        // If the person left the scene, delete their circle
        if(circles->has(id)) {
          std::shared_ptr<Circle> circle = circles->get(id);
          circles->scheduleForRemoval(circle);
        }
      }
		}
	}
  // Remove circles that were scheduled for removal
  circles->removeAll();
}
