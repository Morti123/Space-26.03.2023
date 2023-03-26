#pragma once
#include "settings.h"

class Bullet {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	float speedx, speedy;
public:
	Bullet(sf::Vector2f playerPos, int playerAngle) {
		texture.loadFromFile(Bullets_File_Name);
		sprite.setTexture(texture);
		sprite.setRotation(playerAngle);
		sf::FloatRect bounds = sprite.getLocalBounds();
		sprite.setOrigin(bounds.width / 2, bounds.height / 2);
		sprite.setPosition(playerPos);
		speedx = Bullet_speed * sin(playerAngle * PI / 180);
		speedy = -Bullet_speed * cos(playerAngle * PI / 180);
	}
	void update() {
		sprite.move(speedx, speedy);
	}

	sf::Sprite& getSprite() { return sprite; }
	sf::FloatRect getHitBox() { return sprite.getGlobalBounds(); }
};