#pragma once
#include "SFML/Graphics.hpp"
#include "settings.h"
#include <vector>
#include "meteor.h"
#include "player.h"
#include <list>
#include "Fonobj.h"
#include "Bullet.h"

class Game {
private:
	sf::RenderWindow window;
	std::vector<Meteor*> meteors;
	Player player;
	Fonobj fon;

public:
	void spawnMeteors(size_t n) {
		for (int i = 0; i < n; i++) {
			int num = rand() % 4 + 1;
			std::string fileName = "images\\spaceMeteors_00" + std::to_string(num) + ".png";
			Meteor::MeteorSize size = (Meteor::MeteorSize)(rand() % 3);
			float x = rand() % 1801 - 300.f;
			float y = rand() % 1501 - 300.f;
			float speedx = rand() % 11 - 5.f;
			float speedy = rand() % 11 - 5.f;
			Meteor* m = new Meteor(fileName, size, sf::Vector2f{ x,y }, sf::Vector2f{ speedx, speedy });
			meteors.push_back(m);
		}
	}
	Game() {
		window.create(sf::VideoMode{ (size_t)WINDOW_WIDTH, (size_t)WINDOW_HEIGHT }, WINDOW_TITLE);
		window.setFramerateLimit(FPS);
		spawnMeteors(30);
	}

	void checkEvents() {
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed) window.close();
	}

	void update() {
		for (int i = 0; i < meteors.size(); i++) {
			meteors.at(i)->update();
		}
		fon.update();
		player.update();
	}

	void checkCollisions() {
		sf::FloatRect playerBounds = player.getHitBox();
		for (auto& meteor : meteors) {
			sf::FloatRect meteorBounds = meteor->getHitBox();
			if (meteorBounds.intersects(playerBounds)) {
				meteor->setRandomPosition();
				player.decreaseHp(meteor->getDamage());
			}
		}
		auto bulletsSptites = player.getBullets();
		for (auto& meteor : meteors) {
			sf::FloatRect meteorBounds = meteor->getHitBox();

			for (auto& bullet : *bulletsSptites) {
				sf::FloatRect bulletsBounds =bullet->getHitBox();

				if (meteorBounds.intersects(bulletsBounds)) {
					meteor->setRandomPosition();
				}
			}
		}
	}

	void draw() {
		window.clear();
		window.draw(fon.getSprite());
		for (int i = 0; i < meteors.size(); i++) {
			window.draw(meteors.at(i)->getSprite());
		}
		
		player.draw(window);
		window.display();
	}

	void play() {
		while (window.isOpen()) {
			checkEvents();
			update();
			checkCollisions();
			draw();
		}
	}
};