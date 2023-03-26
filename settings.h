#pragma once
#include <SFML/Graphics.hpp>

const float WINDOW_WIDTH = 1200;
const float WINDOW_HEIGHT = 900;
const std::string WINDOW_TITLE = "SFML Asteroids P53122";
const float FPS = 60.f;

const std::string Player_File_Name = "images\\spaceShips_008.png";
const float PI = 3.14159265358;

const sf::Vector2f FonStartPos{ 0, 0 };
const std::string Fon_File_Name = "images\\Fon (3).jpg";
const float Fon_offset = 50.f;

const float Top_Border = -300.f;
const float Bottom_Border = 1200.f;
const float Left_Border = -300.f;
const float Right_Border = 1500.f;

const std::string Bullets_File_Name = "images\\spaceMissiles_006.png";
const float Bullet_speed = 15.f;

const int fire_cooldown = 200.f;
const int Player_max_hp = 100;
const int CHAR_SIZE = 48;
const sf::Vector2f HP_text_pos(0.f, 0.f);
