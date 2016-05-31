#include <SFML/Graphics.hpp>

#include "SceneWindow.hpp"

SceneWindow::SceneWindow(cv::Size resolution_projector) {
	this->window_scene = new sf::RenderWindow(
		sf::VideoMode(
			resolution_projector.width,
			resolution_projector.height
		),
		"Projector"
	);
  this->window_scene->clear(sf::Color::Black);
  this->window_scene->display();
}

void SceneWindow::drawScene(Scene* scene) {
	this->window_scene->clear(sf::Color::Black);
	scene->draw(*this->window_scene);
	
	this->window_scene->display();
}

