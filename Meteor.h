#pragma once
#include "settings.h"

class Meteor {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f speed;
	int damage;
public:
	enum MeteorSize { SMALL, AVERAGE, BIG };
	Meteor(std::string fileName, MeteorSize size, sf::Vector2f pos, sf::Vector2f fspeed) {
		texture.loadFromFile(fileName);
		sprite.setTexture(texture);
		if (size == BIG) {
			sprite.setScale(0.4f, 0.4f);
			damage = 30;
		}
		else if (size == AVERAGE) {
			sprite.setScale(0.2f, 0.2f);
			damage = 15;
		}
		else if (size == SMALL) {
			sprite.setScale(0.125f, 0.125f);
			damage = 5;
		}
		sprite.setPosition(pos);
		speed = fspeed;
	}

	void update() {
		sprite.move(speed);
		sf::Vector2f pos = sprite.getPosition();
		if (pos.x<Left_Border || pos.x>Right_Border || pos.y<Top_Border || pos.y>Bottom_Border) {
			setRandomPosition();
		}
	}
	void setRandomPosition() {
		float x = rand() % 301 - 300.f;
		int choice = rand() % 10000;
		if (choice < 5000) x += 1500.f;
		float y = rand() % 301 - 300.f;
		choice = rand() % 10000;
		if (choice < 5000) y += 1200.f;
		float speedx = rand() % 9 - 4.f;
		float speedy = rand() % 9 - 4.f;
		sprite.setPosition(x, y);
	}

	sf::Sprite& getSprite() { return sprite; }
	int getDamage() { return damage; }
	sf::FloatRect getHitBox() { return sprite.getGlobalBounds(); }
};
