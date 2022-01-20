#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "map.h"
#include "view.h"
#include "mission.h"
//#include <time.h>

class Player {
private:
	float x, y;
public:
	float w, h, dx, dy, speed;
	int dir, playerScore, playerHealth;
	bool life = true;
	sf::String file;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	Player(sf::String F, int X, int Y, float W, float H) {
		file = F;
		w = W; h = H;
		x = X; y = Y;
		dir = 2, playerScore = 0, playerHealth = 100, speed = 0;
		life = true;
		image.loadFromFile("images/" + file);
		image.createMaskFromColor(sf::Color(102, 128, 230));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(0, 0, w, h));
	}
	void update(float time) {
		switch (dir) {
			case 0: dx = speed; dy = 0; break;
			case 1: dx = -speed; dy = 0; break;
			case 2: dx = 0; dy = speed; break;
			case 3: dx = 0; dy = -speed; break;
		}

		x += dx * time;
		y += dy * time;

		interactionWithMap();

		if (playerHealth <= 0) { life = false; speed = 0; sprite.setColor(sf::Color::Red); }

		speed = 0;
		sprite.setPosition(x, y);
	}
	float getPlayerCoordinateX() { return x; }
	float getPlayerCoordinateY() { return y; }

	void interactionWithMap() {
		for (int i = y / 128; i < (y + h) / 128; i++) {
			for (int j = x / 128; j < (x + w) / 128; j++) {
				if (TileMap[i][j] == '0') {
					if (dy<0) { y = (i + 1) * 128; }
					else if (dy>0) { y = i * 128 - h; }
					if (dx<0) { x = (j + 1) * 128; }
					else if (dx>0) { x = j * 128 - w; }
				}
				else if (TileMap[i][j] == 's') {
					float rx = (j * 128 + 128 * 0.5 - x - w/2);
					float ry = (i * 128 + 128 * 0.5 - y - h/2);
					if (rx*rx + ry * ry < 8192) {
						TileMap[i][j] = ' ';
						playerScore++;
					}
				}
				else if (TileMap[i][j] == 'f') {
					float rx = (j * 128 + 128 * 0.5 - x - w / 2);
					float ry = (i * 128 + 128 * 0.5 - y - h / 2);
					if (rx*rx + ry * ry < 8192) {
						TileMap[i][j] = ' ';
						playerHealth -= 40;
					}
				}
				else if (TileMap[i][j] == 'p') {
					float rx = (j * 128 + 128 * 0.5 - x - w / 2);
					float ry = (i * 128 + 128 * 0.5 - y - h / 2);
					if (rx*rx + ry * ry < 8192 && playerHealth < 120) {
						TileMap[i][j] = ' ';
						playerHealth += 20;
						playerHealth = playerHealth > 120 ? 120 : playerHealth;
					}
				}
			}
		}

	}
};


int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 800), "Window1");
	//View
	view.reset(sf::FloatRect(0, 0, 1280, 800));

	//Font
	sf::Font font;
	font.loadFromFile("fonts/FuturaOlympicMoscow.otf");
	sf::Text text("", font, 20);
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);

	//Map
	sf::Image map_image;
	map_image.loadFromFile("images/map.png");
	sf::Texture map;
	map.loadFromImage(map_image);
	sf::Sprite s_map;
	s_map.setTexture(map);
	
	//Mission
	sf::Image quest_image;
	quest_image.loadFromFile("images/missionbg.png");
	sf::Texture quest_texture;
	quest_texture.loadFromImage(quest_image);
	sf::Sprite s_quest;
	s_quest.setTexture(quest_texture);
	s_quest.setTextureRect(sf::IntRect(0, 0, 512, 512));
	//s_quest.setScale(1,1);
	sf::Text missionText("", font, 40);
	missionText.setFillColor(sf::Color::Black);
	bool showMissionText = true;

	//Player
	Player hero("Rick.png",200,200,125,162);

	//Settings
	sf::Clock clock;
	sf::Clock gameTimeClock;
	int gameTime = 0;
	float currentFrame=0;
	float frameSpeed=0.009;
	float movingSpeed = 0.3;

	while (window.isOpen()) {
		float time = clock.getElapsedTime().asMicroseconds();
		if (hero.life) { gameTime = gameTimeClock.getElapsedTime().asSeconds(); } else { view.rotate(0.01); }
		clock.restart();
		time = time / 1000;
		//std::cout << time << std::endl;
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Tab) {
					switch (showMissionText) {
						case true: {
							std::ostringstream task;
							task << getTextMission(getCurrentMission(hero.getPlayerCoordinateX()));
							missionText.setString("Mission:" + task.str());
							missionText.setPosition(view.getCenter().x - quest_image.getSize().x / 2 + missionText.getCharacterSize(), view.getCenter().y - quest_image.getSize().y / 2 + missionText.getCharacterSize());
							s_quest.setPosition(view.getCenter().x - quest_image.getSize().x / 2, view.getCenter().y - quest_image.getSize().y / 2);
							showMissionText = false;
							break;
						}
						case false: {
							text.setString("");
							showMissionText = true;
							break;
						}
					}
				}
			}
		}

		if (hero.life) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				hero.dir = 1; hero.speed = movingSpeed;
				currentFrame += time * frameSpeed;
				if (currentFrame > 4) { currentFrame -= 4; }
				hero.sprite.setTextureRect(sf::IntRect(int(currentFrame) * 125, 162, 125, 162));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				hero.dir = 0; hero.speed = movingSpeed;
				currentFrame += time * frameSpeed;
				if (currentFrame > 4) { currentFrame -= 4; }
				hero.sprite.setTextureRect(sf::IntRect(125 + int(currentFrame) * 125, 162, -125, 162));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				hero.dir = 3; hero.speed = movingSpeed;
				currentFrame += time * frameSpeed;
				if (currentFrame > 4) { currentFrame -= 4; }
				hero.sprite.setTextureRect(sf::IntRect(int(currentFrame) * 125, 162 + 162, 125, 162));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				hero.dir = 2; hero.speed = movingSpeed;
				currentFrame += time * frameSpeed;
				if (currentFrame > 4) { currentFrame -= 4; }
				hero.sprite.setTextureRect(sf::IntRect(int(currentFrame) * 125, 0, 125, 162));
			}
			//Updating view after player's moves
			getPlayerCoordinateForView(hero.getPlayerCoordinateX(), hero.getPlayerCoordinateY());
		}
		
		//Updating player
		hero.update(time);

		//Moving view by keybords
		viewMap(time);

		//Setting view
		window.setView(view);

		//Cleaning window
		window.clear(sf::Color(127,127,127));

		//Drawing map
		for (int i = 0; i < HEIGHT_MAP; i++) {
			for (int j = 0; j < WIDTH_MAP; j++) {
				//Choosing texture rect for cell
				if (TileMap[i][j] == ' ') { s_map.setTextureRect(sf::IntRect(0, 0, 128, 128)); }
				else if (TileMap[i][j] == 's') { s_map.setTextureRect(sf::IntRect(128, 0, 128, 128)); }
				else if (TileMap[i][j] == '0') { s_map.setTextureRect(sf::IntRect(128*2, 0, 128, 128)); }
				else if (TileMap[i][j] == 'f') { s_map.setTextureRect(sf::IntRect(128*3, 0, 128, 128)); }
				else if (TileMap[i][j] == 'p') { s_map.setTextureRect(sf::IntRect(128*4, 0, 128, 128)); }

				//Setting position for cell
				s_map.setPosition(j * 128, i * 128);

				//Drawing cell
				window.draw(s_map);
			}
		}

		//Setting score text
		std::ostringstream playerScoreString;
		playerScoreString << hero.playerScore;
		text.setString("Crystal dust collected: " + playerScoreString.str());
		text.setPosition(view.getCenter().x - view.getSize().x/2 + text.getCharacterSize()*0.2, view.getCenter().y - view.getSize().y/2 + text.getCharacterSize()*0.2);
		//Drawing score text
		window.draw(text);
		//Setting health text
		std::ostringstream playerHealthString;
		playerHealthString << hero.playerHealth;
		text.setString("Health: " + playerHealthString.str());
		text.setPosition(view.getCenter().x - view.getSize().x / 2 + text.getCharacterSize()*0.2, view.getCenter().y - view.getSize().y / 2 + text.getCharacterSize()*1.4);
		//Drawing health text
		window.draw(text);
		//Setting time text
		std::ostringstream gameTimeString;
		gameTimeString << int(gameTime);
		text.setString("Time: " + gameTimeString.str());
		text.setPosition(view.getCenter().x - view.getSize().x / 2 + text.getCharacterSize()*0.2, view.getCenter().y - view.getSize().y / 2 + text.getCharacterSize()*2.6);
		//Drawing time text
		window.draw(text);

		//Drawing player
		window.draw(hero.sprite);
		if (!hero.life) {
			sf::Text gameOverText("", font, 50);
			gameOverText.setString("YOU DIED");
			gameOverText.setFillColor(sf::Color::Red);
			gameOverText.setPosition(view.getCenter().x, view.getCenter().y);
			gameOverText.rotate(view.getRotation());
			window.draw(gameOverText);
		}

		if (!showMissionText) { window.draw(s_quest); window.draw(missionText); }
		window.display();
	}
	return 0;
}