#include <SFML/Graphics.hpp>

#include "SceneWindow.hpp"

SceneWindow::SceneWindow(cv::Size resolution_projector) {
	this->window_scene = new sf::RenderWindow(
		sf::VideoMode(
			resolution_projector.width,
			resolution_projector.height
		),
		"Projector",
		sf::Style::Fullscreen
	);
  this->window_scene->clear(sf::Color::Black);
  this->window_scene->display();
	this->window_scene->setFramerateLimit(60);
}

void SceneWindow::drawScene(Scene* scene) {
	this->window_scene->clear(sf::Color::Black);
	scene->draw(*this->window_scene);
	
	this->window_scene->display();
}

const sf::Image SceneWindow::captureFrameScene() {
	return this->window_scene->capture();
}

bool SceneWindow::shouldKeepOpen() {
	bool open = true;
	sf::Event event;
	while (this->window_scene->pollEvent(event)) {
		if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)) {
			open = false;
		}
	}
	if (!open) {
		window_scene->close();
	}
	return open;
}
