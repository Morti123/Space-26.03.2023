#pragma once
#include "settings.h"
#include "cmath"
#include <list>
#include "Bullet.h"
#include "Textobj.h"

class Player {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	int angle;
	float speed, speedx, speedy;
	std::list<Bullet*> bullets;
	sf::Clock timer;
	int hp = Player_max_hp;
	TextObj hp_text;

public:
	Player() :hp_text(std::to_string(hp), HP_text_pos) {
		texture.loadFromFile(Player_File_Name);
		sprite.setTexture(texture);
		sf::FloatRect bounds = sprite.getLocalBounds();
		sprite.setOrigin(bounds.width / 2, bounds.height / 2);
		sprite.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
		angle = 0;
		speed = 0.f;
		timer.restart();
	}

	void update() {
		if (sprite.getPosition().x <= 0 + Fon_offset) {
			sprite.setPosition(0 + Fon_offset, sprite.getPosition().y);
		}
		if (sprite.getPosition().x >= WINDOW_WIDTH - Fon_offset) {
			sprite.setPosition(WINDOW_WIDTH - Fon_offset, sprite.getPosition().y);
		}
		if (sprite.getPosition().y <= 0 + Fon_offset) {
			sprite.setPosition(sprite.getPosition().x, 0 + Fon_offset);
		}
		if (sprite.getPosition().y >= WINDOW_HEIGHT - Fon_offset) {
			sprite.setPosition(sprite.getPosition().x, WINDOW_HEIGHT - Fon_offset);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			angle -= 3;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			angle += 3;
		}
		sprite.setRotation(angle);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			speed += 0.5f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			speed -= 0.25f;
		}
		if (speed < 0) speed = 0.f;
		else if (speed > 10.f) speed = 10.f;

		speedx = speed * sin(angle * PI / 180);
		speedy = -speed * cos(angle * PI / 180);
		sprite.move(speedx, speedy);
		fire();
		for (auto bullet : bullets) {
			bullet->update();
		}
		hp_text.update("HP:" + std::to_string(hp));
	}

	void fire() {
		int now = timer.getElapsedTime().asMilliseconds();
		if (now > fire_cooldown) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				auto bullet = new Bullet(sprite.getPosition(), angle);
				bullets.push_back(bullet);
				timer.restart();
			}
		}
	}

	void draw(sf::RenderWindow& window) {
		window.draw(sprite);
		for (auto bullet : bullets) {
			window.draw(bullet->getSprite());
		}
		window.draw(sprite);
		hp_text.draw(window);
		if (hp <= 0) {
			window.close();
		}
	}
	void decreaseHp(int damage) { hp -= damage; }
	sf::FloatRect getHitBox() { return sprite.getGlobalBounds(); }
	std::list<Bullet*>* getBullets() { return &bullets; }
};