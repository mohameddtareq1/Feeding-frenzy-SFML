#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "menu.h"
#include <string>
#include <Windows.h>

using namespace std;
using namespace sf;


void windoww(RenderWindow& window, SoundBuffer& mousedownbuffer, Sound& mousedownsound, SoundBuffer& mouseoverbuffer, Sound& mouseoversound, SoundBuffer& introbuffer, Sound& introsound, SoundBuffer& stagebuffer, Sound& stagesound, Music& music);
void instructions(RenderWindow& window, SoundBuffer& mousedownbuffer, Sound& mousedownsound, SoundBuffer& mouseoverbuffer, Sound& mouseoversound, SoundBuffer& introbuffer, Sound& introsound, SoundBuffer& stagebuffer, Sound& stagesound, Music& music);
void credits(RenderWindow& window, SoundBuffer& mousedownbuffer, Sound& mousedownsound, SoundBuffer& mouseoverbuffer, Sound& mouseoversound, SoundBuffer& introbuffer, Sound& introsound, SoundBuffer& stagebuffer, Sound& stagesound, Music& music);
void Levels(RenderWindow& window, SoundBuffer& mousedownbuffer, Sound& mousedownsound, SoundBuffer& mouseoverbuffer, Sound& mouseoversound, SoundBuffer& introbuffer, Sound& introsound, SoundBuffer& stagebuffer, Sound& stagesound, Music& music);
void Level1(RenderWindow& window, SoundBuffer& mousedownbuffer, Sound& mousedownsound, SoundBuffer& mouseoverbuffer, Sound& mouseoversound, SoundBuffer& introbuffer, Sound& introsound, SoundBuffer& stagebuffer, Sound& stagesound, Music& music);
void Level2(RenderWindow& window, SoundBuffer& mousedownbuffer, Sound& mousedownsound, SoundBuffer& mouseoverbuffer, Sound& mouseoversound, SoundBuffer& introbuffer, Sound& introsound, SoundBuffer& stagebuffer, Sound& stagesound, Music& music);
void Level3(RenderWindow& window, SoundBuffer& mousedownbuffer, Sound& mousedownsound, SoundBuffer& mouseoverbuffer, Sound& mouseoversound, SoundBuffer& introbuffer, Sound& introsound, SoundBuffer& stagebuffer, Sound& stagesound, Music& music);

void Level4(RenderWindow& window, SoundBuffer& mousedownbuffer, Sound& mousedownsound, SoundBuffer& mouseoverbuffer, Sound& mouseoversound, SoundBuffer& introbuffer, Sound& introsound, SoundBuffer& stagebuffer, Sound& stagesound, Music& music);
void endgame(RenderWindow& window, SoundBuffer& mousedownbuffer, Sound& mousedownsound, SoundBuffer& mouseoverbuffer, Sound& mouseoversound, SoundBuffer& introbuffer, Sound& introsound, SoundBuffer& stagebuffer, Sound& stagesound, Music& music);
void congratulation(RenderWindow& window, SoundBuffer& mousedownbuffer, Sound& mousedownsound, SoundBuffer& mouseoverbuffer, Sound& mouseoversound, SoundBuffer& introbuffer, Sound& introsound, SoundBuffer& stagebuffer, Sound& stagesound, Music& music);
void playerMovement(Vector2f&, Vector2f&, float, float, float, float, float);

void playerScreenCollision(Sprite&, const unsigned, const unsigned);

void playerAndEnemyCollision(Sprite& playerSprite, Sprite& enemySprite, float& playerScore, float enemyScore, bool& deathStatus, int positionInVector, vector<Sprite>& spriteVector,
	vector <Vector2f>& velocityVector, vector <Vector2f>& directionVector, vector<int>& directionRandVector, vector<int>& currentFrameVector, vector <Clock>& clockVector,
	vector<float>& timeVector, bool& eating, int& currentFrameEating, Vector2f direction, Clock& clockEating, float timeEating, Sound& eatingSound, int& frenzyRow, int& frenzyColumn,
	bool& ateInLastSeconds, Clock& frenzyClock, Sound& frenzygreen, Sound& frenzyred, Sound& gulp, int& leaderboardscore, int& frenzymulti, Sprite& chomp, int& eatingNum)
{
	if (playerSprite.getGlobalBounds().intersects(enemySprite.getGlobalBounds()))
	{
		if (playerScore >= enemyScore)
		{
			//ENEMY DESPAWN
			spriteVector.erase(spriteVector.begin() + positionInVector);
			velocityVector.erase(velocityVector.begin() + positionInVector);
			directionVector.erase(directionVector.begin() + positionInVector);
			directionRandVector.erase(directionRandVector.begin() + positionInVector);
			currentFrameVector.erase(currentFrameVector.begin() + positionInVector);
			clockVector.erase(clockVector.begin() + positionInVector);
			timeVector.erase(timeVector.begin() + positionInVector);

			if (enemyScore == 0)
			{
				playerScore += 0.3;
				leaderboardscore += (10 * frenzymulti);
				if (eatingNum < 30) {
					eatingNum += 1;
				}
				else {
					eatingNum = 30;
				}
				gulp.play();
				int chompCol = (rand() % 5) - 2;
				chomp.setTextureRect(IntRect(74 * chompCol, 0, 74, 61));
				chomp.setPosition(playerSprite.getPosition().x, playerSprite.getPosition().y);
			}
			else if (enemyScore == 10)
			{
				playerScore += 0.6;
				leaderboardscore += (20 * frenzymulti);
				gulp.play();
				int chompCol = (rand() % 5) - 2;
				chomp.setTextureRect(IntRect(114 * chompCol, 61, 114, 93));
				chomp.setPosition(playerSprite.getPosition().x, playerSprite.getPosition().y);
			}
			else
			{
				playerScore += 0.9;
				leaderboardscore += (30 * frenzymulti);
				gulp.play();
				int chompCol = (rand() % 5) - 2;
				chomp.setTextureRect(IntRect(171 * chompCol, 154, 171, 139));
				chomp.setPosition(playerSprite.getPosition().x, playerSprite.getPosition().y);
			}
			eatingSound.play();
			eating = true;
			currentFrameEating = 0;

			//FRENZY ANIMATION
			frenzyClock.restart();
			ateInLastSeconds = true;

			if (frenzyColumn == 0)
			{
				frenzyColumn++;
				frenzyRow = 0;
			}
			else if (frenzyColumn == 1) {
				frenzyRow++;
				if (frenzyRow == 6)
					frenzygreen.play();
			}
			else if (frenzyColumn == 2) {
				frenzyRow++;
				if (frenzyRow == 6)
					frenzyred.play();
			}
			if (frenzyRow > 6)
			{
				frenzyColumn++;
				frenzyRow = 0;
			}
			if (frenzyColumn > 2)
			{
				frenzyColumn = 2;
				frenzyRow = 6;
			}
		}
		else if (playerScore < enemyScore)
		{
			deathStatus = true;
			playerScore = 0;
		}
	}
	if (eating)
	{
		timeEating = clockEating.getElapsedTime().asMilliseconds();
		if (timeEating >= 80)
		{
			if (direction.x == 1)
			{

				playerSprite.setTextureRect(IntRect(currentFrameEating * playerSprite.getLocalBounds().width + playerSprite.getLocalBounds().width, 0, -playerSprite.getLocalBounds().width, playerSprite.getLocalBounds().height));
				currentFrameEating++;
				clockEating.restart();
				if (currentFrameEating > 5)
				{
					currentFrameEating = 0;
					eating = false;
				}
			}
			else if (direction.x == -1)
			{

				playerSprite.setTextureRect(IntRect(currentFrameEating * playerSprite.getLocalBounds().width, 0, playerSprite.getLocalBounds().width, playerSprite.getLocalBounds().height));
				currentFrameEating++;
				clockEating.restart();

				if (currentFrameEating > 5)
				{
					currentFrameEating = 0;
					eating = false;
				}
			}
		}
	}
}

void enemyAndEnemyCollision(Sprite&, Sprite&, int, int, int, int, vector<Sprite>&, vector<Sprite>&, vector <Vector2f>&, vector <Vector2f>&, vector <Vector2f>&, vector <Vector2f>&, vector<int>&, vector<int>&, vector<int>&,
	vector<int>&, vector <Clock>&, vector <Clock>&, vector<float>& ime1, vector<float>&, bool&, bool&, int&, Vector2f, Clock&, float, int, bool&, int&, Vector2f, Clock&, float, int);

void enemyMovement(Vector2f& enemyVelocity, Vector2f& enemyDirection, int& directionRandomizer, float dt, float enemyMaxVel, float enemyAccel,
	float enemyResist, float movementMultiplier, Sprite& sprite, const unsigned WINDOW_WIDTH = 1920, const unsigned WINDOW_HEIGHT = 1080)
{
	if (sprite.getPosition().y > WINDOW_HEIGHT - 100)
		directionRandomizer = 0;
	if (sprite.getPosition().y < 160)
		directionRandomizer = 1;
	if (sprite.getPosition().x > WINDOW_WIDTH - 50)
		directionRandomizer = 2;
	if (sprite.getPosition().x < 50)
		directionRandomizer = 3;

	//enemy's movement
	//North
	if (directionRandomizer == 0)
	{
		enemyDirection.y = -1.f;

		if (enemyVelocity.y > -enemyMaxVel)
			enemyVelocity.y += enemyAccel * enemyDirection.y * dt * movementMultiplier;
	}
	//South
	if (directionRandomizer == 1)
	{
		enemyDirection.y = 1.f;

		if (enemyVelocity.y < enemyMaxVel)
			enemyVelocity.y += enemyAccel * enemyDirection.y * dt * movementMultiplier;
	}
	//West
	if (directionRandomizer == 2)
	{
		enemyDirection.x = -1.f;

		if (enemyVelocity.x > -enemyMaxVel)
			enemyVelocity.x += enemyAccel * enemyDirection.x * dt * movementMultiplier;
	}
	//East
	if (directionRandomizer == 3)
	{
		enemyDirection.x = 1.f;

		if (enemyVelocity.x < enemyMaxVel)
			enemyVelocity.x += enemyAccel * enemyDirection.x * dt * movementMultiplier;
	}
	//Northern-East
	if (directionRandomizer == 4)
	{
		enemyDirection.y = -1.f;

		if (enemyVelocity.y > -enemyMaxVel)
			enemyVelocity.y += enemyAccel * enemyDirection.y * dt * movementMultiplier;

		enemyDirection.x = 1.f;

		if (enemyVelocity.x < enemyMaxVel)
			enemyVelocity.x += enemyAccel * enemyDirection.x * dt * movementMultiplier;
	}
	//Northern-West
	if (directionRandomizer == 5)
	{
		enemyDirection.y = -1.f;
		enemyDirection.x = -1.f;

		if (enemyVelocity.y > -enemyMaxVel)
			enemyVelocity.y += enemyAccel * enemyDirection.y * dt * movementMultiplier;

		if (enemyVelocity.x > -enemyMaxVel)
			enemyVelocity.x += enemyAccel * enemyDirection.x * dt * movementMultiplier;
	}
	//Southern-West
	if (directionRandomizer == 6)
	{
		enemyDirection.y = 1.f;
		enemyDirection.x = -1.f;

		if (enemyVelocity.y < enemyMaxVel)
			enemyVelocity.y += enemyAccel * enemyDirection.y * dt * movementMultiplier;

		if (enemyVelocity.x > -enemyMaxVel)
			enemyVelocity.x += enemyAccel * enemyDirection.x * dt * movementMultiplier;
	}
	//Southern-East
	if (directionRandomizer == 7)
	{
		enemyDirection.y = 1.f;
		enemyDirection.x = 1.f;

		if (enemyVelocity.y < enemyMaxVel)
			enemyVelocity.y += enemyAccel * enemyDirection.y * dt * movementMultiplier;

		if (enemyVelocity.x < enemyMaxVel)
			enemyVelocity.x += enemyAccel * enemyDirection.x * dt * movementMultiplier;
	}
	//enemy's resistance
	//UP
	if (enemyVelocity.y > 0.f)
	{
		enemyVelocity.y -= enemyResist * dt * movementMultiplier;

		if (enemyVelocity.y < 0.f)
			enemyVelocity.y = 0;
	}
	//DOWN
	else if (enemyVelocity.y < 0.f)
	{
		enemyVelocity.y += enemyResist * dt * movementMultiplier;

		if (enemyVelocity.y > 0.f)
			enemyVelocity.y = 0;
	}
	//LEFT
	else if (enemyVelocity.x < 0.f)
	{
		enemyVelocity.x += enemyResist * dt * movementMultiplier;

		if (enemyVelocity.x > 0.f)
			enemyVelocity.x = 0;
	}
	//RIGHT
	if (enemyVelocity.x > 0.f)
	{
		enemyVelocity.x -= enemyResist * dt * movementMultiplier;

		if (enemyVelocity.x < 0.f)
			enemyVelocity.x = 0;
	}
}

void enemyBehavior(Sprite&, Sprite&, Vector2f&, Vector2f&, float, float, float, float, float);

void animation(Sprite& Sprite, int& currentFrame, int row, int frameMax, Vector2f velocity, Vector2f direction, Clock& clock, float& time, float loopTime = 60)
{
	time = clock.getElapsedTime().asMilliseconds();
	if (time >= loopTime)
	{
		if (velocity.x > 1)
		{
			Sprite.setTextureRect(IntRect(currentFrame * Sprite.getLocalBounds().width + Sprite.getLocalBounds().width, row * Sprite.getLocalBounds().height, -Sprite.getLocalBounds().width, Sprite.getLocalBounds().height));
			currentFrame++;
			clock.restart();
			if (currentFrame >= frameMax)
				currentFrame = 0;
		}
		else if (velocity.x < -1)
		{
			Sprite.setTextureRect(IntRect(currentFrame * Sprite.getLocalBounds().width, row * Sprite.getLocalBounds().height, Sprite.getLocalBounds().width, Sprite.getLocalBounds().height));
			currentFrame++;
			clock.restart();
			if (currentFrame >= frameMax)
				currentFrame = 0;
		}
		else if (velocity.x <= 0.25 && velocity.x > 0)
		{
			Sprite.setTextureRect(IntRect(Sprite.getLocalBounds().width, row * Sprite.getLocalBounds().height, -Sprite.getLocalBounds().width, Sprite.getLocalBounds().height));
			currentFrame = 0;
		}
		else if (velocity.x >= -0.25 && velocity.x < 0)
		{
			Sprite.setTextureRect(IntRect(Sprite.getLocalBounds().width, row * Sprite.getLocalBounds().height, Sprite.getLocalBounds().width, Sprite.getLocalBounds().height));
			currentFrame = 0;
		}
	}
}

struct Entity
{
	float score;
	int rowMotion, rowTurn, maxFrameMotion, maxFrameTurn, maxFrameEat;
	float maxVel, accel, resist;
	Vector2f velocity, direction;
	Sprite sprite;
	Texture texture;
};

int pagenumber = 0;
int counter = 0;
int pausenumber = 5;
int highScoreInFile;
int leaderboardScore = 0;
int levelnumber = 0;

/*
* *******************************
* -------------------------------
* mainmenu           |        0
* play(Levels)       |        1
* Options            |        2
* Instructions       |        3
* Exit               |        4
* Level one          |        5
* Level two          |        6
* Level three        |        7
* Level Four         |        8
* Endgame            |        9
* Congratulation     |        10
*/


int main()
{
	Music music;
	music.openFromFile("Resources/music/mainmenu.ogg");
	SoundBuffer mousedownbuffer, mouseoverbuffer, introbuffer, stagebuffer; Sound mousedownsound, mouseoversound, introsound, stagesound;
	RenderWindow window(VideoMode(1600, 1200), "Main Menu", Style::Fullscreen);
	music.play();
	mousedownbuffer.loadFromFile("Resources/sounds/mouseDown.ogg");
	mouseoverbuffer.loadFromFile("Resources/sounds/mouseOver.ogg");
	introbuffer.loadFromFile("Resources/sounds/stageIntro.ogg");
	stagebuffer.loadFromFile("Resources/sounds/stageClear.ogg");

	mousedownsound.setBuffer(mousedownbuffer);
	mouseoversound.setBuffer(mouseoverbuffer);
	introsound.setBuffer(introbuffer);
	stagesound.setBuffer(stagebuffer);
	//pagenumber = 11;
	//congratulation(window, mousedownbuffer, mousedownsound, mouseoverbuffer, mouseoversound, introbuffer, introsound, stagebuffer, stagesound, music);
	windoww(window, mousedownbuffer, mousedownsound, mouseoverbuffer, mouseoversound, introbuffer, introsound, stagebuffer, stagesound, music);
	return 0;
}

void windoww(RenderWindow& window, SoundBuffer& mousedownbuffer, Sound& mousedownsound, SoundBuffer& mouseoverbuffer, Sound& mouseoversound, SoundBuffer& introbuffer, Sound& introsound, SoundBuffer& stagebuffer, Sound& stagesound, Music& music)
{


	Image icon;
	icon.loadFromFile("Resources/Backgrounds/Icon.png");

	menu menu(window.getSize().x, window.getSize().y);
	menu.menuu[0].setString("Play");
	menu.menuu[0].setPosition(Vector2f(730, 350));
	menu.menuu[0].setCharacterSize(70);

	menu.menuu[1].setString("Instructions");
	menu.menuu[1].setPosition(Vector2f(600, 490));
	menu.menuu[1].setCharacterSize(70);

	menu.menuu[2].setString("Credits");
	menu.menuu[2].setPosition(Vector2f(670, 630));
	menu.menuu[2].setCharacterSize(70);

	menu.menuu[3].setString("Exit");
	menu.menuu[3].setPosition(Vector2f(720, 760));
	menu.menuu[3].setCharacterSize(70);



	Texture t2;
	t2.loadFromFile("Resources/Backgrounds/backgroundf.jpg");
	Sprite background2;
	background2.setTexture(t2);

	Font font1;
	font1.loadFromFile("Resources/Fonts/scrubland.regular.ttf");


	View view;
	view.reset(FloatRect(0, 0, 1600, 900));
	window.setView(view);
	while (true)
	{
		if (pagenumber == 0)
		{

			while (window.isOpen())
			{

				Event event;
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed)
						window.close();
					if (event.type == Event::KeyReleased)
					{
						if (event.key.code == Keyboard::Up)
						{
							mousedownsound.play();
							menu.moveup();
							break;
						}
						if (event.key.code == Keyboard::Down)
						{
							mousedownsound.play();
							menu.movedown();
							break;
						}

						if (event.key.code == Keyboard::Return)
						{
							mouseoversound.play();

							if (menu.getselecteditem() == 0)
							{
								pagenumber = 1;
							}
							else if (menu.getselecteditem() == 1)
							{
								pagenumber = 2;
							}
							else if (menu.getselecteditem() == 2)
							{
								pagenumber = 3;
							}
							else if (menu.getselecteditem() == 3)
							{
								pagenumber = 4;
							}


						}


					}
				}

				window.clear();
				if (pagenumber != 0)
				{
					break;
				}
				window.draw(background2);
				menu.draw(window);
				window.display();

			}
			if (pagenumber == 1)
			{
				Levels(window, mousedownbuffer, mousedownsound, mouseoverbuffer, mouseoversound, introbuffer, introsound, stagebuffer, stagesound, music);
			}
			if (pagenumber == 2)
			{
				instructions(window, mousedownbuffer, mousedownsound, mouseoverbuffer, mouseoversound, introbuffer, introsound, stagebuffer, stagesound, music);
			}
			if (pagenumber == 3)
			{
				credits(window, mousedownbuffer, mousedownsound, mouseoverbuffer, mouseoversound, introbuffer, introsound, stagebuffer, stagesound, music);
			}
			if (pagenumber == 4)
			{
				window.close();
				music.stop();
			}
		}
	}
}
void instructions(RenderWindow& window, SoundBuffer& mousedownbuffer, Sound& mousedownsound, SoundBuffer& mouseoverbuffer, Sound& mouseoversound, SoundBuffer& introbuffer, Sound& introsound, SoundBuffer& stagebuffer, Sound& stagesound, Music& music)
{
	Sprite optionsbackgroundsprite;
	Texture optionsbackgroundtexture;
	optionsbackgroundtexture.loadFromFile("Resources/backgrounds/insbackground.jpeg");
	optionsbackgroundsprite.setTexture(optionsbackgroundtexture);
	View view(FloatRect(0, 0, 1000, 1000));
	window.setView(view);
	Text ins, ins1, ins2, ins3, ins4, ins5, ins6;
	Font font;
	font.loadFromFile("Resources/Fonts/Five.otf");
	ins.setFont(font);
	ins.setPosition(Vector2f(150, 20));
	ins.setCharacterSize(50);
	ins.setFillColor(Color(1, 150, 32));
	ins.setString("Welcome to Feeding frenzy!");

	ins1.setFont(font);
	ins1.setCharacterSize(35);
	ins1.setFillColor(Color::Blue);
	ins1.setString("The player starts as a tiny fish trying to survive but");
	ins1.setPosition(Vector2f(50, 200));

	ins2.setFont(font);
	ins2.setCharacterSize(35);
	ins2.setFillColor(Color::Blue);
	ins2.setString("hunted ,  in  an  unknown  underwater world full of ");
	ins2.setPosition(Vector2f(50, 300));

	ins3.setFont(font);
	ins3.setCharacterSize(35);
	ins3.setFillColor(Color::Blue);
	ins3.setString("killer predators.");
	ins3.setPosition(Vector2f(50, 400));

	ins4.setFont(font);
	ins4.setCharacterSize(35);
	ins4.setFillColor(Color::Blue);
	ins4.setString("the player must collect score , avoid been eaten and");
	ins4.setPosition(Vector2f(50, 500));

	ins5.setFont(font);
	ins5.setCharacterSize(35);
	ins5.setFillColor(Color::Blue);
	ins5.setString("enjoy plaing");
	ins5.setPosition(Vector2f(50, 600));

	ins5.setFont(font);
	ins5.setCharacterSize(35);
	ins5.setFillColor(Color::Blue);
	ins5.setString("Made by: Eraky , mounir and tarek");
	ins5.setPosition(Vector2f(50, 800));

	menu menu(1200, window.getSize().y);
	menu.menuu[0].setString(" ");
	menu.menuu[1].setString(" ");
	menu.menuu[2].setCharacterSize(30);
	menu.menuu[2].setPosition(Vector2f(400, 950));
	menu.menuu[2].setString("Press Enter to escape to the Main Menu");
	menu.menuu[2].setFillColor(Color(1, 150, 32));
	menu.menuu[2].setFont(font);
	while (true)
	{
		if (pagenumber == 2)
		{
			while (window.isOpen())
			{
				Event event;
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed)
					{
						window.close();
					}
					if (event.type == Event::KeyReleased)
					{

						if (event.key.code == Keyboard::Escape)
						{
							mouseoversound.play();
							pagenumber = 0;
						}

					}
				}

				window.clear();
				if (pagenumber != 2)
				{
					break;
				}
				window.draw(optionsbackgroundsprite);
				menu.draw(window);
				window.draw(ins);
				window.draw(ins1);
				window.draw(ins2);
				window.draw(ins3);
				window.draw(ins4);
				window.draw(ins5);
				window.draw(ins6);
				window.display();
			}
			if (pagenumber == 0)
			{
				windoww(window, mousedownbuffer, mousedownsound, mouseoverbuffer, mouseoversound, introbuffer, introsound, stagebuffer, stagesound, music);
			}
		}
	}

}
void credits(RenderWindow& window, SoundBuffer& mousedownbuffer, Sound& mousedownsound, SoundBuffer& mouseoverbuffer, Sound& mouseoversound, SoundBuffer& introbuffer, Sound& introsound, SoundBuffer& stagebuffer, Sound& stagesound, Music& music)
{
	Sprite creditssprite;
	Texture creditstexture;
	creditstexture.loadFromFile("Resources/backgrounds/insbackground.jpeg");
	creditssprite.setTexture(creditstexture);

	View view(FloatRect(0, 0, 1000, 1000));
	window.setView(view);

	Font font;
	font.loadFromFile("Resources/Fonts/scrubland.regular.ttf");

	Text credit, credit1, credit2, credit3, credit4, credit5, credit6, credit7, credit8, credit9;
	credit.setFont(font);
	credit.setCharacterSize(90);
	credit.setFillColor(Color(1, 150, 32));
	credit.setPosition(Vector2f(350, 30));
	credit.setString("Credits");

	credit1.setFont(font);
	credit1.setCharacterSize(90);
	credit1.setFillColor(Color(1, 150, 32));
	credit1.setPosition(Vector2f(300, 120));
	credit1.setString("FCIS ASU");

	credit2.setFont(font);
	credit2.setCharacterSize(90);
	credit2.setFillColor(Color(1, 150, 32));
	credit2.setPosition(Vector2f(100, 220));
	credit2.setString("Gen_32");


	credit3.setFont(font);
	credit3.setCharacterSize(50);
	credit3.setFillColor(Color(1, 150, 32));
	credit3.setPosition(Vector2f(100, 350));
	credit3.setString("Mohamed Monier Tag-Eldeen");

	credit4.setFont(font);
	credit4.setCharacterSize(50);
	credit4.setFillColor(Color(1, 150, 32));
	credit4.setPosition(Vector2f(100, 390));
	credit4.setString("2022170389");

	credit5.setFont(font);
	credit5.setCharacterSize(50);
	credit5.setFillColor(Color(1, 150, 32));
	credit5.setPosition(Vector2f(100, 450));
	credit5.setString("Mohamed Tareq EL-Husien");

	credit6.setFont(font);
	credit6.setCharacterSize(50);
	credit6.setFillColor(Color(1, 150, 32));
	credit6.setPosition(Vector2f(100, 490));
	credit6.setString("2022170373");

	credit7.setFont(font);
	credit7.setCharacterSize(50);
	credit7.setFillColor(Color(1, 150, 32));
	credit7.setPosition(Vector2f(100, 550));
	credit7.setString("Mohamed Tareq Mohamed");

	credit8.setFont(font);
	credit8.setCharacterSize(50);
	credit8.setFillColor(Color(1, 150, 32));
	credit8.setPosition(Vector2f(100, 590));
	credit8.setString("2022170374");

	credit9.setFont(font);
	credit9.setCharacterSize(40);
	credit9.setFillColor(Color(1, 150, 32));
	credit9.setPosition(Vector2f(180, 800));
	credit9.setString("Press enter to escape to Main menu");



	while (true)
	{
		if (pagenumber == 3)
		{
			while (window.isOpen())
			{
				Event event;
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed)
						window.close();

					if (event.type == Event::KeyPressed)
					{
						if (event.key.code == Keyboard::Escape)
						{
							pagenumber = 0;
						}




					}
					window.clear();
					if (pagenumber != 3)
					{
						break;
					}
					window.draw(creditssprite);
					window.draw(credit);
					window.draw(credit1);
					window.draw(credit2);
					window.draw(credit3);
					window.draw(credit4);
					window.draw(credit5);
					window.draw(credit6);
					window.draw(credit7);
					window.draw(credit8);
					window.draw(credit9);
					window.display();

				}
				if (pagenumber == 0)
				{
					windoww(window, mousedownbuffer, mousedownsound, mouseoverbuffer, mouseoversound, introbuffer, introsound, stagebuffer, stagesound, music);
				}

			}



		}

	}






}
void Levels(RenderWindow& window, SoundBuffer& mousedownbuffer, Sound& mousedownsound, SoundBuffer& mouseoverbuffer, Sound& mouseoversound, SoundBuffer& introbuffer, Sound& introsound, SoundBuffer& stagebuffer, Sound& stagesound, Music& music)
{

	Font font;
	font.loadFromFile("Resources/Fonts/scrubland.regular.ttf");
	menu menu(window.getSize().x, window.getSize().y);
	menu.menuu[0].setString("1 | Humble Beginnings");
	menu.menuu[0].setPosition(Vector2f(335, 320));
	menu.menuu[0].setCharacterSize(55);
	menu.menuu[0].setFont(font);
	menu.menuu[0].setOutlineColor(Color::Black);
	menu.menuu[0].setOutlineThickness(2);
	menu.menuu[1].setString("2 | Time Bounded");
	menu.menuu[1].setFont(font);
	menu.menuu[1].setPosition(Vector2f(335, 450));
	menu.menuu[1].setCharacterSize(55);
	menu.menuu[2].setString("3 | Wasteland");
	menu.menuu[2].setPosition(Vector2f(335, 580));
	menu.menuu[2].setFont(font);
	menu.menuu[2].setCharacterSize(55);
	menu.menuu[3].setString("4 | Into the Abyss");
	menu.menuu[3].setPosition(Vector2f(335, 710));
	menu.menuu[3].setFont(font);
	menu.menuu[3].setCharacterSize(55);

	RectangleShape textBackground;
	textBackground.setSize(Vector2f(610, 470));
	textBackground.setFillColor(Color(0, 0, 0, 100));
	textBackground.setPosition(Vector2f(310, 315));
	textBackground.setOutlineColor(Color::White);
	textBackground.setOutlineThickness(2);

	Text bottom_info;
	bottom_info.setFont(font);
	bottom_info.setCharacterSize(30);
	bottom_info.setFillColor(Color::Yellow);
	bottom_info.setString("Press Escape to return to main menu");
	bottom_info.setPosition(Vector2f(700, 1040));
	bottom_info.setOutlineColor(Color::Black);
	bottom_info.setOutlineThickness(1.5);

	Text you;
	you.setFont(font);
	you.setCharacterSize(60);
	you.setFillColor(Color(255, 165, 0, 255));
	you.setString("YOU");
	you.setPosition(Vector2f(1580, 420));
	you.setOutlineColor(Color::Black);
	you.setOutlineThickness(2);

	bool colorLoop = false;
	Clock colorLoopClock;
	float colorLoopTimer;


	//LEVEL PREVIEW
	int selectedLevel = 0;

	Clock dt_clock, directionRandomizerClock;
	float dt, directionRandomizerTime;

	//Background
	Texture backgroundTexture[3];
	backgroundTexture[0].loadFromFile("Resources/Backgrounds/background.jpg");
	backgroundTexture[1].loadFromFile("Resources/Backgrounds/background2.jpg");
	backgroundTexture[2].loadFromFile("Resources/Backgrounds/Untitled-1.jpg");
	Sprite background[3];
	background[0].setTexture(backgroundTexture[0]);
	background[1].setTexture(backgroundTexture[1]);
	background[2].setTexture(backgroundTexture[2]);

	//Level 1 and 2
	//Minnow
	Entity minnow[12];
	Texture minnowTexture;
	minnowTexture.loadFromFile("Resources/Sprites/Minnow.png");
	int Minnow_currentFrame[12] = {};
	int Minnow_directionRand[12];
	Clock Minnow_clock[12];
	float Minnow_time[12];
	for (int i = 0; i < 12; i++)
	{
		minnow[i] = { 0, 0, 1, 14, 5, 0, 3.75f, 0.375f, 0.05f };
		minnow[i].sprite.setTexture(minnowTexture);
		minnow[i].sprite.setTextureRect(IntRect(66, 0, -66, 49));
		minnow[i].sprite.setPosition(Vector2f(rand() % 1854, rand() % 1031));
		Minnow_directionRand[i] = rand() % 8;
	}
	//Surgeonfish Orange
	Entity surgeonOrange[6];
	Texture surgeonOrangeTexture;
	surgeonOrangeTexture.loadFromFile("Resources/Sprites/Surgeonfish.png");
	int surgeonOrange_currentFrame[6] = {};
	int surgeonOrange_directionRand[6];
	Clock surgeonOrange_clock[6];
	float surgeonOrange_time[6];
	for (int i = 0; i < 6; i++)
	{
		surgeonOrange[i] = { 10, 1, 2, 13, 4, 5, 3.f, 0.3f, 0.16875f };
		surgeonOrange[i].sprite.setTexture(surgeonOrangeTexture);
		surgeonOrange[i].sprite.setTextureRect(IntRect(171, 0, -171, 106));
		surgeonOrange[i].sprite.setPosition(Vector2f(rand() % 1749, rand() % 974));
		surgeonOrange_directionRand[i] = rand() % 8;
	}
	//Dory green
	Entity doryGreen[2];
	Texture doryGreenTexture;
	doryGreenTexture.loadFromFile("Resources/Sprites/John Dory.png");
	int doryGreen_currentFrame[2] = {};
	int doryGreen_directionRand[2];
	Clock doryGreen_clock[2];
	float doryGreen_time[2];
	for (int i = 0; i < 2; i++)
	{
		doryGreen[i] = { 20, 1, 2, 14, 4, 6, 2.25f, 0.225f, 0.1875f };
		doryGreen[i].sprite.setTexture(doryGreenTexture);
		doryGreen[i].sprite.setTextureRect(IntRect(181, 0, -181, 181));
		doryGreen[i].sprite.setPosition(Vector2f(rand() % 1739, rand() % 899));
		doryGreen[i].sprite.setScale(1.3, 1.3);
		doryGreen_directionRand[i] = rand() % 8;
	}
	//Level 4
	//Surgeonfish Red
	Entity surgeonRed[12];
	Texture surgeonRedTexture;
	surgeonRedTexture.loadFromFile("Resources/Sprites/Surgeonfish2.png");
	int surgeonRed_currentFrame[12] = {};
	int surgeonRed_directionRand[12];
	Clock surgeonRed_clock[12];
	float surgeonRed_time[12];
	for (int i = 0; i < 12; i++)
	{
		surgeonRed[i] = { 0, 1, 2, 13, 5, 0, 3.75f, 0.375f, 0.05f };
		surgeonRed[i].sprite.setTexture(surgeonRedTexture);
		surgeonRed[i].sprite.setTextureRect(IntRect(171, 0, -171, 106));
		surgeonRed[i].sprite.setPosition(Vector2f(rand() % 1749, rand() % 974));
		surgeonRed[i].sprite.setScale(0.6, 0.6);
		surgeonRed_directionRand[i] = rand() % 8;
	}
	//Dory blue
	Entity doryBlue[6];
	Texture doryBlueTexture;
	doryBlueTexture.loadFromFile("Resources/Sprites/John_Dory2.png");
	int doryBlue_currentFrame[6] = {};
	int doryBlue_directionRand[6];
	Clock doryBlue_clock[6];
	float doryBlue_time[6];
	for (int i = 0; i < 6; i++)
	{
		doryBlue[i] = { 10, 1, 2, 14, 5, 6, 3.f, 0.3f, 0.16875f };
		doryBlue[i].sprite.setTexture(doryBlueTexture);
		doryBlue[i].sprite.setTextureRect(IntRect(181, 0, -181, 181));
		doryBlue[i].sprite.setPosition(Vector2f(rand() % 1739, rand() % 899));
		doryBlue[i].sprite.setScale(1.1, 1.1);
		doryBlue_directionRand[i] = rand() % 8;
	}
	//Barracuda
	Entity barracuda[2];
	Texture barracudaTexture;
	barracudaTexture.loadFromFile("Resources/Sprites/bigEnemy.png");
	int barracuda_currentFrame[2] = {};
	int barracuda_directionRand[2];
	Clock barracuda_clock[2];
	float barracuda_time[2];
	for (int i = 0; i < 2; i++)
	{
		barracuda[i] = { 20, 1, 2, 13, 5, 6, 2.25f, 0.225f, 0.1875f };
		barracuda[i].sprite.setTexture(barracudaTexture);
		barracuda[i].sprite.setTextureRect(IntRect(271, 0, -271, 121));
		barracuda[i].sprite.setPosition(Vector2f(rand() % 1739, rand() % 899));
		barracuda[i].sprite.setScale(1.4, 1.4);
		barracuda_directionRand[i] = rand() % 8;
	}
	//Level 3
	//Angelfish blue
	Entity angelfishBlue[12];
	Texture angelfishBlueTexture;
	angelfishBlueTexture.loadFromFile("Resources/Sprites/Angelfish_blue.png");
	int angelfishBlue_currentFrame[12] = {};
	int angelfishBlue_directionRand[12];
	Clock angelfishBlue_clock[12];
	float angelfishBlue_time[12];
	for (int i = 0; i < 12; i++)
	{
		angelfishBlue[i] = { 0, 2, 3, 14, 5, 0, 3.75f, 0.375f, 0.05f };
		angelfishBlue[i].sprite.setTexture(angelfishBlueTexture);
		angelfishBlue[i].sprite.setTextureRect(IntRect(126, 106, -126, 106));
		angelfishBlue[i].sprite.setPosition(Vector2f(rand() % 1794, rand() % 974));
		angelfishBlue[i].sprite.setScale(0.6, 0.6);
		angelfishBlue_directionRand[i] = rand() % 8;
	}
	//Surgeonfish blue
	Entity surgeonBlue[6];
	Texture surgeonBlueTexture;
	surgeonBlueTexture.loadFromFile("Resources/Sprites/Surgeonfish_blue.png");
	int surgeonBlue_currentFrame[6] = {};
	int surgeonBlue_directionRand[6];
	Clock surgeonBlue_clock[6];
	float surgeonBlue_time[6];
	for (int i = 0; i < 6; i++)
	{
		surgeonBlue[i] = { 10, 1, 2, 13, 4, 5, 3.f, 0.3f, 0.16875f };
		surgeonBlue[i].sprite.setTexture(surgeonBlueTexture);
		surgeonBlue[i].sprite.setTextureRect(IntRect(171, 0, -171, 106));
		surgeonBlue[i].sprite.setPosition(Vector2f(rand() % 1749, rand() % 974));
		surgeonBlue[i].sprite.setScale(1.1, 1.1);
		surgeonBlue_directionRand[i] = rand() % 8;
	}
	//Marlin
	Entity marlin[2];
	Texture marlinTexture;
	marlinTexture.loadFromFile("Resources/Sprites/Layer_2.png");
	int marlin_currentFrame[2] = {};
	int marlin_directionRand[2];
	Clock marlin_clock[2];
	float marlin_time[2];
	for (int i = 0; i < 2; i++)
	{
		marlin[i] = { 20, 1, 2, 14, 5, 5, 2.25f, 0.225f, 0.1875f };
		marlin[i].sprite.setTexture(marlinTexture);
		marlin[i].sprite.setTextureRect(IntRect(251, 0, -251, 176));
		marlin[i].sprite.setPosition(Vector2f(rand() % 1669, rand() % 904));
		marlin[i].sprite.setScale(1.4, 1.4);
		marlin_directionRand[i] = rand() % 8;
	}

	//Player sprites
	Texture angelTexture;
	angelTexture.loadFromFile("Resources/Sprites/Angelfish.png");
	Sprite angelfish;
	angelfish.setTexture(angelTexture);
	angelfish.setTextureRect(IntRect(0, 0, 126, 106));
	angelfish.setPosition(Vector2f(1585, 510));

	Texture anglerTexture;
	anglerTexture.loadFromFile("Resources/Sprites/player2.png");
	Sprite anglerfish;
	anglerfish.setTexture(anglerTexture);
	anglerfish.setTextureRect(IntRect(0, 0, 201, 181));
	anglerfish.setPosition(Vector2f(1560, 455));

	Texture anglerTextureBrown;
	anglerTextureBrown.loadFromFile("Resources/Sprites/player3.png");
	Sprite anglerfishBrown;
	anglerfishBrown.setTexture(anglerTextureBrown);
	anglerfishBrown.setTextureRect(IntRect(0, 0, 201, 181));
	anglerfishBrown.setPosition(Vector2f(1560, 455));

	//Semi transparent overlay
	RectangleShape darkOverlay;
	darkOverlay.setSize(Vector2f(1920, 1080));
	darkOverlay.setFillColor(Color(0, 0, 0, 100));


	View view(FloatRect(0, 0, 1920, 1080));
	window.setView(view);
	while (true)
	{
		if (pagenumber == 1)
		{

			while (window.isOpen())
			{

				Event event;
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed)
						window.close();
					if (event.type == Event::KeyReleased)
					{
						if (event.key.code == Keyboard::Up)
						{
							mousedownsound.play();
							selectedLevel--;
							menu.moveup();
							break;
						}
						if (event.key.code == Keyboard::Down)
						{
							mousedownsound.play();
							selectedLevel++;
							menu.movedown();
							break;
						}
						if (event.key.code == Keyboard::Escape)
						{
							pagenumber = 0;
						}
						if (event.key.code == Keyboard::Return)
						{
							mouseoversound.play();

							if (menu.getselecteditem() == 0)
							{
								pagenumber = 5;
							}
							if (menu.getselecteditem() == 1)
							{
								pagenumber = 6;
							}
							if (menu.getselecteditem() == 2)
							{
								pagenumber = 7;
							}
							if (menu.getselecteditem() == 3)
							{
								pagenumber = 8;
							}

						}
					}
				}

				//Selected level
				if (selectedLevel <= -1)
					selectedLevel = 3;
				if (selectedLevel >= 4)
					selectedLevel = 0;

				//Color loop
				colorLoopTimer = colorLoopClock.getElapsedTime().asSeconds();
				if (colorLoopTimer >= 1)
				{
					colorLoopClock.restart().asSeconds();
					if (!colorLoop)
						colorLoop = true;
					else
						colorLoop = false;
				}

				//Entity direction, clock, movement
				dt = dt_clock.restart().asSeconds();

				directionRandomizerTime = directionRandomizerClock.getElapsedTime().asSeconds();
				if (directionRandomizerTime >= 1)
				{
					for (int i = 0; i < 12; i++)
					{
						Minnow_directionRand[i] = rand() % 8;
						surgeonRed_directionRand[i] = rand() % 8;
						angelfishBlue_directionRand[i] = rand() % 8;
					}
					for (int i = 0; i < 6; i++)
					{
						surgeonOrange_directionRand[i] = rand() % 8;
						doryBlue_directionRand[i] = rand() % 8;
						surgeonBlue_directionRand[i] = rand() % 8;
					}
					for (int i = 0; i < 2; i++)
					{
						doryGreen_directionRand[i] = rand() % 8;
						barracuda_directionRand[i] = rand() % 8;
						marlin_directionRand[i] = rand() % 8;
					}
					directionRandomizerTime = directionRandomizerClock.restart().asSeconds();
				}
				for (int i = 0; i < 12; i++)
				{
					enemyMovement(minnow[i].velocity, minnow[i].direction, Minnow_directionRand[i], dt,
						minnow[i].maxVel, minnow[i].accel, minnow[i].resist, 60, minnow[i].sprite);
					minnow[i].sprite.move(minnow[i].velocity.x * dt * 60, minnow[i].velocity.y * dt * 60);
					animation(minnow[i].sprite, Minnow_currentFrame[i], minnow[i].rowMotion, minnow[i].maxFrameMotion, minnow[i].velocity,
						minnow[i].direction, Minnow_clock[i], Minnow_time[i], 60);

					enemyMovement(surgeonRed[i].velocity, surgeonRed[i].direction, surgeonRed_directionRand[i], dt,
						surgeonRed[i].maxVel, surgeonRed[i].accel, surgeonRed[i].resist, 60, surgeonRed[i].sprite);
					surgeonRed[i].sprite.move(surgeonRed[i].velocity.x * dt * 60, surgeonRed[i].velocity.y * dt * 60);
					animation(surgeonRed[i].sprite, surgeonRed_currentFrame[i], surgeonRed[i].rowMotion, surgeonRed[i].maxFrameMotion, surgeonRed[i].velocity,
						surgeonRed[i].direction, surgeonRed_clock[i], surgeonRed_time[i], 60);

					enemyMovement(angelfishBlue[i].velocity, angelfishBlue[i].direction, angelfishBlue_directionRand[i], dt,
						angelfishBlue[i].maxVel, angelfishBlue[i].accel, angelfishBlue[i].resist, 60, angelfishBlue[i].sprite);
					angelfishBlue[i].sprite.move(angelfishBlue[i].velocity.x * dt * 60, angelfishBlue[i].velocity.y * dt * 60);
					animation(angelfishBlue[i].sprite, angelfishBlue_currentFrame[i], angelfishBlue[i].rowMotion, angelfishBlue[i].maxFrameMotion, angelfishBlue[i].velocity,
						angelfishBlue[i].direction, angelfishBlue_clock[i], angelfishBlue_time[i], 60);
				}
				for (int i = 0; i < 6; i++)
				{
					enemyMovement(surgeonOrange[i].velocity, surgeonOrange[i].direction, surgeonOrange_directionRand[i], dt,
						surgeonOrange[i].maxVel, surgeonOrange[i].accel, surgeonOrange[i].resist, 60, surgeonOrange[i].sprite);
					surgeonOrange[i].sprite.move(surgeonOrange[i].velocity.x * dt * 60, surgeonOrange[i].velocity.y * dt * 60);
					animation(surgeonOrange[i].sprite, surgeonOrange_currentFrame[i], surgeonOrange[i].rowMotion, surgeonOrange[i].maxFrameMotion, surgeonOrange[i].velocity,
						surgeonOrange[i].direction, surgeonOrange_clock[i], surgeonOrange_time[i], 80);

					enemyMovement(doryBlue[i].velocity, doryBlue[i].direction, doryBlue_directionRand[i], dt,
						doryBlue[i].maxVel, doryBlue[i].accel, doryBlue[i].resist, 60, doryBlue[i].sprite);
					doryBlue[i].sprite.move(doryBlue[i].velocity.x * dt * 60, doryBlue[i].velocity.y * dt * 60);
					animation(doryBlue[i].sprite, doryBlue_currentFrame[i], doryBlue[i].rowMotion, doryBlue[i].maxFrameMotion, doryBlue[i].velocity,
						doryBlue[i].direction, doryBlue_clock[i], doryBlue_time[i], 80);

					enemyMovement(surgeonBlue[i].velocity, surgeonBlue[i].direction, surgeonBlue_directionRand[i], dt,
						surgeonBlue[i].maxVel, surgeonBlue[i].accel, surgeonBlue[i].resist, 60, surgeonBlue[i].sprite);
					surgeonBlue[i].sprite.move(surgeonBlue[i].velocity.x * dt * 60, surgeonBlue[i].velocity.y * dt * 60);
					animation(surgeonBlue[i].sprite, surgeonBlue_currentFrame[i], surgeonBlue[i].rowMotion, surgeonBlue[i].maxFrameMotion, surgeonBlue[i].velocity,
						surgeonBlue[i].direction, surgeonBlue_clock[i], surgeonBlue_time[i], 80);
				}
				for (int i = 0; i < 2; i++)
				{
					enemyMovement(doryGreen[i].velocity, doryGreen[i].direction, doryGreen_directionRand[i], dt,
						doryGreen[i].maxVel, doryGreen[i].accel, doryGreen[i].resist, 60, doryGreen[i].sprite);
					doryGreen[i].sprite.move(doryGreen[i].velocity.x * dt * 60, doryGreen[i].velocity.y * dt * 60);
					animation(doryGreen[i].sprite, doryGreen_currentFrame[i], doryGreen[i].rowMotion, doryGreen[i].maxFrameMotion, doryGreen[i].velocity,
						doryGreen[i].direction, doryGreen_clock[i], doryGreen_time[i], 100);

					enemyMovement(barracuda[i].velocity, barracuda[i].direction, barracuda_directionRand[i], dt,
						barracuda[i].maxVel, barracuda[i].accel, barracuda[i].resist, 60, barracuda[i].sprite);
					barracuda[i].sprite.move(barracuda[i].velocity.x * dt * 60, barracuda[i].velocity.y * dt * 60);
					animation(barracuda[i].sprite, barracuda_currentFrame[i], barracuda[i].rowMotion, barracuda[i].maxFrameMotion, barracuda[i].velocity,
						barracuda[i].direction, barracuda_clock[i], barracuda_time[i], 100);

					enemyMovement(marlin[i].velocity, marlin[i].direction, marlin_directionRand[i], dt,
						marlin[i].maxVel, marlin[i].accel, marlin[i].resist, 60, marlin[i].sprite);
					marlin[i].sprite.move(marlin[i].velocity.x * dt * 60, marlin[i].velocity.y * dt * 60);
					animation(marlin[i].sprite, marlin_currentFrame[i], marlin[i].rowMotion, marlin[i].maxFrameMotion, marlin[i].velocity,
						marlin[i].direction, marlin_clock[i], marlin_time[i], 100);
				}

				//Draw
				window.clear();
				if (pagenumber != 1)
				{
					break;
				}

				if (selectedLevel == 0)
				{
					window.draw(background[0]);
					for (int i = 0; i < 12; i++)
						window.draw(minnow[i].sprite);
					for (int i = 0; i < 6; i++)
						window.draw(surgeonOrange[i].sprite);
					for (int i = 0; i < 2; i++)
						window.draw(doryGreen[i].sprite);
					window.draw(darkOverlay);
					window.draw(angelfish);

					you.setPosition(Vector2f(1580, 420));
					you.setOutlineColor(Color::Black);
					if (!colorLoop)
						you.setFillColor(Color(255, 165, 0, 255));
					else
						you.setFillColor(Color(216, 52, 235, 255));
				}
				else if (selectedLevel == 1)
				{
					window.draw(background[0]);
					for (int i = 0; i < 12; i++)
						window.draw(minnow[i].sprite);
					window.draw(darkOverlay);
					window.draw(angelfish);

					you.setPosition(Vector2f(1580, 420));
					you.setOutlineColor(Color::Black);
					if (!colorLoop)
						you.setFillColor(Color(255, 165, 0, 255));
					else
						you.setFillColor(Color(216, 52, 235, 255));
				}
				else if (selectedLevel == 2)
				{
					window.draw(background[2]);
					for (int i = 0; i < 12; i++)
						window.draw(angelfishBlue[i].sprite);
					for (int i = 0; i < 6; i++)
						window.draw(surgeonBlue[i].sprite);
					for (int i = 0; i < 2; i++)
						window.draw(marlin[i].sprite);
					window.draw(darkOverlay);
					window.draw(anglerfishBrown);

					you.setPosition(Vector2f(1580, 410));
					you.setOutlineColor(Color::Black);
					if (!colorLoop)
						you.setFillColor(Color(248, 208, 116, 255));
					else
						you.setFillColor(Color(170, 145, 80, 255));
				}
				else if (selectedLevel == 3)
				{
					window.draw(background[1]);
					for (int i = 0; i < 12; i++)
						window.draw(surgeonRed[i].sprite);
					for (int i = 0; i < 6; i++)
						window.draw(doryBlue[i].sprite);
					for (int i = 0; i < 2; i++)
						window.draw(barracuda[i].sprite);
					window.draw(darkOverlay);
					window.draw(anglerfish);

					you.setPosition(Vector2f(1580, 410));
					you.setOutlineColor(Color::White);
					if (!colorLoop)
						you.setFillColor(Color(46, 163, 0, 255));
					else
						you.setFillColor(Color(6, 87, 1, 255));
				}
				window.draw(you);
				window.draw(textBackground);
				menu.draw(window);
				window.draw(bottom_info);
				window.display();

			}
			if (pagenumber == 0)
			{
				windoww(window, mousedownbuffer, mousedownsound, mouseoverbuffer, mouseoversound, introbuffer, introsound, stagebuffer, stagesound, music);
			}
			if (pagenumber == 5)
			{
				music.stop();
				introsound.play();
				Level1(window, mousedownbuffer, mousedownsound, mouseoverbuffer, mouseoversound, introbuffer, introsound, stagebuffer, stagesound, music);
			}
			if (pagenumber == 6)
			{
				music.stop();
				introsound.play();
				Level2(window, mousedownbuffer, mousedownsound, mouseoverbuffer, mouseoversound, introbuffer, introsound, stagebuffer, stagesound, music);

			}
			if (pagenumber == 7)
			{
				music.stop();
				introsound.play();

				Level3(window, mousedownbuffer, mousedownsound, mouseoverbuffer, mouseoversound, introbuffer, introsound, stagebuffer, stagesound, music);
			}
			if (pagenumber == 8)
			{
				music.stop();
				introsound.play();
				Level4(window, mousedownbuffer, mousedownsound, mouseoverbuffer, mouseoversound, introbuffer, introsound, stagebuffer, stagesound, music);
			}

		}
	}
}
void Level1(RenderWindow& window, SoundBuffer& mousedownbuffer, Sound& mousedownsound, SoundBuffer& mouseoverbuffer, Sound& mouseoversound, SoundBuffer& introbuffer, Sound& introsound, SoundBuffer& stagebuffer, Sound& stagesound, Music& music)
{
	levelnumber = 1;
	const unsigned WINDOW_WIDTH = 1920, WINDOW_HEIGHT = 1080;
	int eatingnum = 0;
	//Pause Menu
	menu pausemenu(window.getSize().x, window.getSize().y);
	pausemenu.menuu[0].setString("Resume");
	pausemenu.menuu[1].setString("Levels Menu");
	pausemenu.menuu[2].setString("Exit");
	



	leaderboardScore = 0;
	bool pausemenuisopen = false;

	//pausemenu texture
	Texture pausemenutexture;
	pausemenutexture.loadFromFile("Resources/Backgrounds/pausemenu1.jpg");
	Sprite pausemenusprite;
	pausemenusprite.setTexture(pausemenutexture);

	//Game Over Texture
	Texture GameOvertexture;
	GameOvertexture.loadFromFile("Resources/Backgrounds/GameOver.png");
	Sprite GameOver;
	GameOver.setTexture(GameOvertexture);
	GameOver.setScale(1.8, 1.8);
	GameOver.setPosition(550, 200);
	RectangleShape GameOverBackground;
	GameOverBackground.setSize(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	GameOverBackground.setFillColor(Color(0, 0, 0, 100));

	//Background
	Texture backgroundTexture;
	backgroundTexture.loadFromFile("Resources/Backgrounds/background.jpg");
	Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);
	Vector2u sizeBG = backgroundTexture.getSize();
	backgroundSprite.setOrigin(sizeBG.x / 2, sizeBG.y / 2);
	backgroundSprite.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);




	//score bar texture
	Texture scorebartexture;
	scorebartexture.loadFromFile("Resources/Backgrounds/Scorebar.jpeg");
	Sprite ScoreBar;
	ScoreBar.setTexture(scorebartexture);
	ScoreBar.setScale(1.5, 1);
	ScoreBar.setTextureRect(IntRect(0, 0, 1314, 135));

	//menu texture for minnow
	Texture ScoreMinnowTexture;
	ScoreMinnowTexture.loadFromFile("Resources/Sprites/Minnow.png");
	Sprite ScoreMinnow;
	ScoreMinnow.setTexture(ScoreMinnowTexture);
	ScoreMinnow.setPosition(430, 30);
	ScoreMinnow.setScale(1.2, 1.2);
	ScoreMinnow.setTextureRect(IntRect(66, 0, -66, 49));

	//menu texture for surgeon
	Texture ScoreSurgeonfishTexture;
	ScoreSurgeonfishTexture.loadFromFile("Resources/Sprites/Surgeonfish.png");
	Sprite ScoreSurgeonfish;
	ScoreSurgeonfish.setTexture(ScoreSurgeonfishTexture);
	ScoreSurgeonfish.setPosition(600, 5);
	ScoreSurgeonfish.setScale(0.8, 0.8);
	ScoreSurgeonfish.setTextureRect(IntRect(171, 0, -171, 106));

	//menu texture for john dory
	Texture ScoreJohnDoryTexture;
	ScoreJohnDoryTexture.loadFromFile("Resources/Sprites/John Dory.png");
	Sprite ScoreJohnDory;
	ScoreJohnDory.setTexture(ScoreJohnDoryTexture);
	ScoreJohnDory.setPosition(860, -27);
	ScoreJohnDory.setScale(0.7, 0.7);
	ScoreJohnDory.setTextureRect(IntRect(181, 0, -181, 181));

	//transparent  fish
	Texture transparentFishtexture;
	transparentFishtexture.loadFromFile("Resources/Sprites/Ellipse_15.png");
	Sprite transparentFish[2];
	transparentFish[0].setTexture(transparentFishtexture);
	transparentFish[1].setTexture(transparentFishtexture);
	bool istransparentFish[2] = { true,true };
	transparentFish[0].setScale(0.9, 0.9);
	transparentFish[0].setPosition(580, -10);
	transparentFish[1].setPosition(817, -18);

	//default bar
	RectangleShape BarBlack;
	BarBlack.setSize(Vector2f(700, 15));
	BarBlack.setPosition(390, 93);
	BarBlack.setFillColor(Color::Black);

	//Levelup bar
	RectangleShape BarRed;
	BarRed.setSize(Vector2f(94, 11));
	BarRed.setPosition(393, 95);
	BarRed.setFillColor(Color::Red);

	CircleShape Triangle;
	Triangle.setRadius(18);
	Triangle.setPointCount(3);
	Triangle.setPosition(575, 99);
	Triangle.setFillColor(Color::Blue);

	CircleShape Triangle1;
	Triangle1.setRadius(18);
	Triangle1.setPointCount(3);
	Triangle1.setPosition(773, 99);
	Triangle1.setFillColor(Color::Blue);

	//Score number
	Font Scorefont;
	Scorefont.loadFromFile("Resources/Fonts/GUMDROP.ttf");
	Text ScoreText;
	ScoreText.setFont(Scorefont);
	ScoreText.setCharacterSize(40);
	ScoreText.setFillColor(Color::White);
	ScoreText.setPosition(1560, 20);


	//Clock, elapsed time, framerate independence
	Clock dt_clock, spawn_clock[3], movement_clock[3], animationClock;
	float dt;


	//Movement, spawn and random direction intialization
	float movementMultiplier = 60.f;
	float enemySpawnTimeElapsed[3];
	float enemyMovementTimeElapsed[3];
	int enemyDirectionRandomizer[3] = { 0, 0, 0 };


	//Animation initialization
	float animationTime = animationClock.getElapsedTime().asMilliseconds();
	float animationLoopTime[3] = { 60, 80, 100 };
	int currentFramePlayer = 0;
	int currentFrameEnemy[3] = { 0, 0, 0 };




	//FRENZY
	Texture frenzyTexture;
	frenzyTexture.loadFromFile("Resources/Sprites/FRENZY.png");
	Sprite frenzySprite;
	frenzySprite.setTexture(frenzyTexture);
	frenzySprite.setTextureRect(IntRect(0, 0, 350, 120));
	frenzySprite.setPosition(WINDOW_WIDTH / 2 - 175, WINDOW_HEIGHT / 2 - 360);
	Clock frenzyClock, frenzyClockLoss;
	float frenzyTimeLimit = frenzyClock.getElapsedTime().asSeconds(), frenzyTimeLoss;
	bool ateInLastSeconds = false;
	int frenzyColumn = 0, frenzyRow = 0;
	int frenzymulti = 1;

	//font multiplier
	Font frenzyMultiFont;
	frenzyMultiFont.loadFromFile("Resources/Fonts/Roboto-Black.ttf");
	Text frenzyMultiplier;
	frenzyMultiplier.setFont(frenzyMultiFont);
	frenzyMultiplier.setFillColor(Color::White);
	frenzyMultiplier.setOutlineColor(Color::Black);
	frenzyMultiplier.setOutlineThickness(3);
	frenzyMultiplier.setPosition(1760, 5);
	frenzyMultiplier.setCharacterSize(70);


	//chomp 
	Texture chompTexture;
	chompTexture.loadFromFile("Resources/Sprites/Chomp.png");
	Sprite chompSprite;
	chompSprite.setTexture(chompTexture);
	chompSprite.setTextureRect(IntRect(0, 0, 74, 61));
	chompSprite.setPosition(920, 920);


	//Player
	Entity player = { 0, 2, 3, 14, 4, 0, 11.25f, 0.6f, 0.2f };
	player.texture.loadFromFile("Resources/Sprites/Angelfish.png");
	player.sprite.setTexture(player.texture);
	player.sprite.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	player.sprite.setTextureRect(IntRect(126, 106, -126, 106));
	player.sprite.setScale(Vector2f(0.8, 0.8));
	bool deathStatus = false;
	int currentFrameIdle = 0, maxFrameIdle = 6;
	Clock idleClock;
	float idleTimer;
	bool eating = false;
	int currentFrameEating = 0;
	Clock eatingClock;
	float eatingTime = eatingClock.getElapsedTime().asMilliseconds();

	//Small enemies / Minnow
	Entity enemySmall = { 0, 0, 1, 14, 5, 0, 3.75f, 0.375f, 0.05f };
	enemySmall.texture.loadFromFile("Resources/Sprites/Minnow.png");
	enemySmall.sprite.setTexture(enemySmall.texture);
	enemySmall.sprite.setTextureRect(IntRect(66, 0, -66, 49));
	vector <Sprite> Minnow;
	vector <Vector2f> Minnow_velocity;
	vector <Vector2f> Minnow_direction;
	vector <int> Minnow_directionRand;
	vector <int> Minnow_currentFrame;
	vector <Clock> Minnow_clock;
	vector <float> Minnow_time;
	bool eatingMinnow = false;
	int currentFrameEatingMinnow = 0;
	Clock eatingClockMinnow;
	float eatingTimeMinnow = eatingClockMinnow.getElapsedTime().asMilliseconds();

	//Medium enemies / Surgeonfish
	Entity enemyMedium = { 10, 1, 2, 13, 4, 5, 3.f, 0.3f, 0.16875f };
	enemyMedium.texture.loadFromFile("Resources/Sprites/Surgeonfish.png");
	enemyMedium.sprite.setTexture(enemyMedium.texture);
	enemyMedium.sprite.setTextureRect(IntRect(171, 0, -171, 106));
	vector <Sprite> Surgeonfish;
	vector <Vector2f> Surgeonfish_velocity;
	vector <Vector2f> Surgeonfish_direction;
	vector <int> Surgeonfish_directionRand;
	vector <int> Surgeonfish_currentFrame;
	vector <Clock> Surgeonfish_clock;
	vector <float> Surgeonfish_time;
	int surgeonSpawnTimer = 8;
	bool eatingSurgeon = false;
	int currentFrameEatingSurgeon = 0;
	Clock eatingClockSurgeon;
	float eatingTimeSurgeon = eatingClockSurgeon.getElapsedTime().asMilliseconds();

	//Large enemies / John Dory
	Entity enemyLarge = { 20, 1, 2, 14, 4, 6, 2.25f, 0.225f, 0.1875f };
	enemyLarge.texture.loadFromFile("Resources/Sprites/John Dory.png");
	enemyLarge.sprite.setTexture(enemyLarge.texture);
	enemyLarge.sprite.setTextureRect(IntRect(181, 0, -181, 181));
	enemyLarge.sprite.setScale(1.3, 1.3);
	vector <Sprite> JohnDory;
	vector <Vector2f> JohnDory_velocity;
	vector <Vector2f> JohnDory_direction;
	vector <int> JohnDory_directionRand;
	vector <int> JohnDory_currentFrame;
	vector <Clock> JohnDory_clock;
	vector <float> JohnDory_time;
	bool eatingJohnDory = false;
	int currentFrameEatingJohnDory = 0;
	Clock eatingClockJohnDory;
	float eatingTimeJohnDory = eatingClockJohnDory.getElapsedTime().asMilliseconds();
	int dorySpawnTimer = 15, dorySpawnQuantity = 2;

	//Oyster
	Texture oysterTexture;
	oysterTexture.loadFromFile("Resources/Sprites/Oyster.png");
	Sprite oysterSprite;
	oysterSprite.setTexture(oysterTexture);
	oysterSprite.setTextureRect(IntRect(0, 0, 101, 101));
	oysterSprite.setPosition(860, 880);
	oysterSprite.setScale(2, 2);
	Clock oysterOpenClock;
	int oysterOpenTime;
	Clock oysterStayOpenClock;
	int oysterStayOpenTime;
	Clock oysterAnimationClock;
	int oysterAnimationTime;
	int oysterFrame = 0;
	bool oysterClose = false;

	Texture pearlTexture;
	pearlTexture.loadFromFile("Resources/Sprites/Pearl.png");
	Sprite pearlSprite;
	pearlSprite.setTexture(pearlTexture);
	pearlSprite.setTextureRect(IntRect(0, 51, 52, 51));
	pearlSprite.setPosition(910, 930);
	pearlSprite.setScale(2, 2);


	//Shark
	Texture SharkTexture;
	SharkTexture.loadFromFile("Resources/Sprites/bigEnemy.png");
	Sprite sharkSprite;
	sharkSprite.setTexture(SharkTexture);
	sharkSprite.setScale(2, 2);
	sharkSprite.setPosition(10000, 5000);
	sharkSprite.setTextureRect(IntRect(0, 0, 271, 121));
	Clock sharkSpawnClock;
	int sharkSpawnTimer;
	int sharkSide = -1;
	int sharkCurrentFrame = 0;
	Clock sharkAnimationClock;
	float sharkAnimationTime;
	Clock sharkEatingClock;
	float sharkEatingTime;
	bool sharkEating = false;


	//SOUNDS

	//minnowEating sound
	SoundBuffer eatingminnowbuffer;
	eatingminnowbuffer.loadFromFile("Resources/sounds/bite1.ogg");
	Sound eatingminnowsound;
	eatingminnowsound.setBuffer(eatingminnowbuffer);
	bool eatingminnowboolean = true;

	//surgeonEating sound
	SoundBuffer eatingsurgeonbuffer;
	eatingsurgeonbuffer.loadFromFile("Resources/sounds/bite2.ogg");
	Sound eatingsurgeonsound;
	eatingsurgeonsound.setBuffer(eatingsurgeonbuffer);
	bool eatingsurgeonboolean = true;

	//johndoryEating sound
	SoundBuffer eatingjohndorybuffer;
	eatingjohndorybuffer.loadFromFile("Resources/sounds/bite3.ogg");
	Sound eatingjohndorysound;
	eatingjohndorysound.setBuffer(eatingjohndorybuffer);
	bool eatingjohndoryboolean = true;

	//SoundBuffer GameOver
	SoundBuffer GameOverSoundbuffer;
	GameOverSoundbuffer.loadFromFile("Resources/sounds/GameOver.ogg");
	Sound GameOverSound;
	GameOverSound.setBuffer(GameOverSoundbuffer);
	bool playDeathSound = true;

	//gamemusic
	bool musicisplayed = true;
	Music gamemusic;
	gamemusic.openFromFile("Resources/music/level1music.ogg");
	gamemusic.play();
	gamemusic.setLoop(musicisplayed);

	//frenzy sound
	SoundBuffer Feedingfrenysoundbuffer;
	Feedingfrenysoundbuffer.loadFromFile("Resources/sounds/feedingFrenzy.ogg");
	Sound Feedingfrenysound;
	Feedingfrenysound.setBuffer(Feedingfrenysoundbuffer);


	//doublefrenzy sound
	SoundBuffer doublefrenzysoundbuffer;
	doublefrenzysoundbuffer.loadFromFile("Resources/sounds/doubleFrenzy.ogg");
	Sound doublefrenzysound;
	doublefrenzysound.setBuffer(doublefrenzysoundbuffer);

	//growth sound
	SoundBuffer Growthsoundbuffer;
	Growthsoundbuffer.loadFromFile("Resources/sounds/playerGrow.ogg");
	Sound Growthsound;
	Growthsound.setBuffer(Growthsoundbuffer);
	bool Growthsoundboolean = true;

	//eatgulp sound
	SoundBuffer eatgulpsoundbuffer;
	eatgulpsoundbuffer.loadFromFile("Resources/sounds/eatGulp.ogg");
	Sound eatgulpsound;
	eatgulpsound.setBuffer(eatgulpsoundbuffer);

	//eating pearl and being eaten by oyster
	SoundBuffer pearlEatBuffer;
	pearlEatBuffer.loadFromFile("Resources/sounds/oysterPearl.ogg");
	Sound pearlEat;
	pearlEat.setBuffer(pearlEatBuffer);

	SoundBuffer oysterDieBuffer;
	oysterDieBuffer.loadFromFile("Resources/sounds/oysterBite.ogg");
	Sound oysterDie;
	oysterDie.setBuffer(oysterDieBuffer);


	//view camera pausemenu
	View view;
	view.reset(FloatRect(0, 0, 1024, 1024));
	View view1(FloatRect(0, 0, 1920, 1080));
	pausemenu.menuu[0].setCharacterSize(60);
	pausemenu.menuu[1].setCharacterSize(60);
	pausemenu.menuu[2].setCharacterSize(60);
	pausemenu.menuu[0].setPosition(Vector2f(400, 430));
	pausemenu.menuu[1].setPosition(Vector2f(350, 550));
	pausemenu.menuu[2].setPosition(Vector2f(420, 670));

	pausemenu.menuu[3].setString("");

	//Keeping the highest score
	ofstream ofHighScore;
	ifstream ifHighScore;

	ifHighScore.open("HighScore.txt", ios::in);

	ifHighScore >> highScoreInFile;
	ifHighScore.close();

	bool redBarMaxReached = false;


	while (true)
	{
		if (pagenumber == 5)
		{

			while (window.isOpen())
			{
				window.setView(view1);

				//Exiting
				Event event;
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed)
						window.close();
					if (event.type == Event::KeyPressed)
					{
						if (event.key.code == Keyboard::Escape)
						{
							pausemenuisopen = true;

						}
						if (event.key.code == Keyboard::Up)
						{
							if (pausemenuisopen)
								mousedownsound.play();
							pausemenu.pausemoveup();
						}
						if (event.key.code == Keyboard::Down)
						{
							if (pausemenuisopen)
								mousedownsound.play();
							pausemenu.pausemovedown();
						}
						if (event.key.code == Keyboard::Return)
						{
							mouseoversound.play();

							if (pausemenu.getselecteditem() == 0)
							{
								pausenumber = 0;
								pausemenuisopen = false;
							}
							if (pausemenu.getselecteditem() == 1)
							{
								gamemusic.pause();
								pagenumber = 500;
							}
							if (pausemenu.getselecteditem() == 2)
							{
								pagenumber = 2;

							}

						}


					}

				}


				//Time between frames
				dt = dt_clock.restart().asSeconds();

				//Shark animation initialization
				sharkAnimationTime = sharkAnimationClock.getElapsedTime().asMilliseconds();
				sharkEatingTime = sharkEatingClock.getElapsedTime().asMilliseconds();

				//Shark spawn and animation
				sharkSpawnTimer = sharkSpawnClock.getElapsedTime().asSeconds();
				if (sharkSpawnTimer >= 13)
				{
					sharkSide = rand() % 2;
					if (sharkSide == 0)
					{
						sharkSprite.setTextureRect(IntRect(0, 121, 271, 121));
						sharkSprite.setPosition(WINDOW_WIDTH, rand() % (WINDOW_HEIGHT - 121 - 135) + 135);
					}
					else
					{
						sharkSprite.setTextureRect(IntRect(271, 121, -271, 121));
						sharkSprite.setPosition(-271, rand() % (WINDOW_HEIGHT - 121 - 135) + 135);
					}
					sharkSpawnClock.restart().asSeconds();
				}

				if (!pausemenuisopen)
				{
					if (sharkSide == 0)
					{
						sharkSprite.move(-10 * dt * movementMultiplier, 0);
						if (!sharkEating)
						{
							if (sharkAnimationTime >= 100)
							{
								sharkSprite.setTextureRect(IntRect((++sharkCurrentFrame) * 271, 121, 271, 121));
								sharkAnimationClock.restart().asMilliseconds();
								if (sharkCurrentFrame == 13)
									sharkCurrentFrame = 0;
							}
						}
						else
						{
							if (sharkEatingTime >= 40)
							{
								sharkSprite.setTextureRect(IntRect((++sharkCurrentFrame) * 271, 0, 271, 121));
								sharkEatingClock.restart().asMilliseconds();
								if (sharkCurrentFrame == 5)
								{
									sharkCurrentFrame = 0;
									sharkEating = false;
								}
							}
						}
					}
					else if (sharkSide == 1)
					{
						sharkSprite.move(10 * dt * movementMultiplier, 0);
						if (!sharkEating)
						{
							if (sharkAnimationTime >= 100)
							{
								sharkSprite.setTextureRect(IntRect((++sharkCurrentFrame) * 271, 121, -271, 121));
								sharkAnimationClock.restart().asMilliseconds();
								if (sharkCurrentFrame == 13)
									sharkCurrentFrame = 0;
							}
						}
						else
						{
							if (sharkEatingTime >= 40)
							{
								sharkSprite.setTextureRect(IntRect((++sharkCurrentFrame) * 271, 0, -271, 121));
								sharkEatingClock.restart().asMilliseconds();
								if (sharkCurrentFrame == 5)
								{
									sharkCurrentFrame = 0;
									sharkEating = false;
								}
							}
						}
					}
				}

				//Shark and player collision
				if (sharkSprite.getGlobalBounds().intersects(player.sprite.getGlobalBounds()))
					deathStatus = true;

				//Player's movement, collision with screen
				if (!pausemenuisopen)
				{
					playerMovement(player.velocity, player.direction, dt, player.maxVel, player.accel, player.resist, movementMultiplier);
					player.sprite.move(player.velocity.x * dt * movementMultiplier, player.velocity.y * dt * movementMultiplier);
				}
				playerScreenCollision(player.sprite, WINDOW_WIDTH, WINDOW_HEIGHT);

				//Player's animation
				if (!eating)
					animation(player.sprite, currentFramePlayer, player.rowMotion, player.maxFrameMotion, player.velocity,
						player.direction, animationClock, animationTime);

				//Player's idle animation
				if (player.velocity.x == 0 && player.velocity.y == 0)
				{
					idleTimer = idleClock.getElapsedTime().asMilliseconds();
					if (idleTimer >= 120)
					{
						if (player.direction.x >= 0)
						{
							player.sprite.setTextureRect(IntRect(currentFrameIdle * 126 + 126, 106, -126, 106));
							currentFrameIdle++;
							idleClock.restart();
						}
						else if (player.direction.x < 0)
						{
							player.sprite.setTextureRect(IntRect(currentFrameIdle * 126, 106, 126, 106));
							currentFrameIdle++;
							idleClock.restart();
						}
						if (currentFrameIdle >= maxFrameIdle)
							currentFrameIdle = 0;
					}
				}

				//Player levelup
				if (player.score >= enemyMedium.score && player.score < enemyLarge.score)
				{
					player.sprite.setScale(1.1, 1.1);
					istransparentFish[0] = false;
					if (Growthsoundboolean) {
						Growthsound.play();
						Growthsoundboolean = false;
					}
				}
				if (player.score >= enemyLarge.score)
				{
					player.sprite.setScale(1.6, 1.6);
					istransparentFish[1] = false;
					if (!Growthsoundboolean) {
						Growthsound.play();
						Growthsoundboolean = true;
					}
				}
				if (player.score >= enemyMedium.score)
				{
					surgeonSpawnTimer = 5;
					dorySpawnTimer = 12;
					dorySpawnQuantity = 3;
				}
				if (player.score >= enemyLarge.score)
				{
					dorySpawnTimer = 8;
					dorySpawnQuantity = 4;
				}

				//Enemy spawn
				if (!pausemenuisopen)
				{
					//Spawn timer
					for (int i = 0; i < 3; i++)
					{
						enemySpawnTimeElapsed[i] = spawn_clock[i].getElapsedTime().asSeconds();
					}
					//Minnow or small
					if (Minnow.size() <= 16)
					{
						if (enemySpawnTimeElapsed[0] >= 0.5)
						{
							int side = rand() % 2;
							if (side == 0)
								enemySmall.sprite.setPosition(0 - enemySmall.sprite.getGlobalBounds().width, rand() % (WINDOW_HEIGHT - 135) + 135);
							else
								enemySmall.sprite.setPosition(WINDOW_WIDTH, rand() % (WINDOW_HEIGHT - 135) + 135);

							Minnow.push_back(enemySmall.sprite);
							Minnow_velocity.push_back(enemySmall.velocity);
							Minnow_direction.push_back(enemySmall.direction);
							Minnow_directionRand.push_back(enemyDirectionRandomizer[0]);
							Minnow_currentFrame.push_back(currentFrameEnemy[0]);
							Minnow_clock.push_back(animationClock);
							Minnow_time.push_back(animationTime);

							enemySpawnTimeElapsed[0] = spawn_clock[0].restart().asSeconds();
						}
					}
					//Surgeonfish or medium
					if (Surgeonfish.size() <= 10)
					{
						if (enemySpawnTimeElapsed[1] >= surgeonSpawnTimer)
						{
							int side = rand() % 2;
							if (side == 0)
								enemyMedium.sprite.setPosition(0 - enemyMedium.sprite.getGlobalBounds().width, rand() % (WINDOW_HEIGHT - 135) + 135);
							else
								enemyMedium.sprite.setPosition(WINDOW_WIDTH, rand() % (WINDOW_HEIGHT - 135) + 135);

							Surgeonfish.push_back(enemyMedium.sprite);
							Surgeonfish_velocity.push_back(enemyMedium.velocity);
							Surgeonfish_direction.push_back(enemyMedium.direction);
							Surgeonfish_directionRand.push_back(enemyDirectionRandomizer[1]);
							Surgeonfish_currentFrame.push_back(currentFrameEnemy[1]);
							Surgeonfish_clock.push_back(animationClock);
							Surgeonfish_time.push_back(animationTime);

							enemySpawnTimeElapsed[1] = spawn_clock[1].restart().asSeconds();
						}
					}
					// John Dory or large
					if (JohnDory.size() <= dorySpawnQuantity)
					{
						if (enemySpawnTimeElapsed[2] >= dorySpawnTimer)
						{
							int side = rand() % 2;
							if (side == 0)
								enemyLarge.sprite.setPosition(0 - enemyLarge.sprite.getGlobalBounds().width, rand() % (WINDOW_HEIGHT - 135) + 135);
							else
								enemyLarge.sprite.setPosition(WINDOW_WIDTH, rand() % (WINDOW_HEIGHT - 135) + 135);

							JohnDory.push_back(enemyLarge.sprite);
							JohnDory_velocity.push_back(enemyLarge.velocity);
							JohnDory_direction.push_back(enemyLarge.direction);
							JohnDory_directionRand.push_back(enemyDirectionRandomizer[2]);
							JohnDory_currentFrame.push_back(currentFrameEnemy[2]);
							JohnDory_clock.push_back(animationClock);
							JohnDory_time.push_back(animationTime);

							enemySpawnTimeElapsed[2] = spawn_clock[2].restart().asSeconds();
						}
					}

					//Direction Randomizer
					for (int i = 0; i < 3; i++)
					{
						enemyMovementTimeElapsed[i] = movement_clock[i].getElapsedTime().asSeconds();
						if (enemyMovementTimeElapsed[i] >= 1)
						{
							if (i == 0)
							{
								for (int j = 0; j < Minnow.size(); j++)
								{
									Minnow_directionRand[j] = rand() % 8;
								}
							}
							if (i == 1)
							{
								for (int j = 0; j < Surgeonfish.size(); j++)
								{
									Surgeonfish_directionRand[j] = rand() % 8;
								}
							}
							if (i == 2)
							{
								for (int j = 0; j < JohnDory.size(); j++)
								{
									JohnDory_directionRand[j] = rand() % 8;
								}
							}
							enemyMovementTimeElapsed[i] = 0;
							movement_clock[i].restart();
						}
					}

					// enemy movement, behaviour, collision
					for (int i = 0; i < Minnow.size(); i++)
					{
						enemyMovement(Minnow_velocity[i], Minnow_direction[i], Minnow_directionRand[i], dt,
							enemySmall.maxVel, enemySmall.accel, enemySmall.resist, movementMultiplier, Minnow[i]); //DOESN'T MOVE IF THIS IS COMMENTED

						enemyBehavior(player.sprite, Minnow[i], Minnow_velocity[i], Minnow_direction[i], dt,
							enemySmall.maxVel, enemySmall.accel, enemySmall.resist, movementMultiplier);
						Minnow[i].move(Minnow_velocity[i].x * dt * movementMultiplier, Minnow_velocity[i].y * dt * movementMultiplier);

						animation(Minnow[i], Minnow_currentFrame[i], enemySmall.rowMotion, enemySmall.maxFrameMotion, Minnow_velocity[i],
							Minnow_direction[i], Minnow_clock[i], Minnow_time[i], animationLoopTime[0]);

						playerAndEnemyCollision(player.sprite, Minnow[i], player.score, enemySmall.score, deathStatus, i, Minnow, Minnow_velocity,
							Minnow_direction, Minnow_directionRand, Minnow_currentFrame, Minnow_clock, Minnow_time, eating, currentFrameEating, player.direction,
							eatingClock, eatingTime, eatingminnowsound, frenzyRow, frenzyColumn, ateInLastSeconds, frenzyClock,
							Feedingfrenysound, doublefrenzysound, eatgulpsound, leaderboardScore, frenzymulti, chompSprite, eatingnum);
					}
					for (int i = 0; i < Surgeonfish.size(); i++)
					{
						enemyMovement(Surgeonfish_velocity[i], Surgeonfish_direction[i], Surgeonfish_directionRand[i], dt,
							enemySmall.maxVel, enemySmall.accel, enemySmall.resist, movementMultiplier, Surgeonfish[i]);
						if (player.score >= enemyMedium.score)
						{
							enemyBehavior(player.sprite, Surgeonfish[i], Surgeonfish_velocity[i], Surgeonfish_direction[i], dt,
								enemyMedium.maxVel, enemyMedium.accel, enemyMedium.resist, movementMultiplier);
						}
						Surgeonfish[i].move(Surgeonfish_velocity[i].x * dt * movementMultiplier, Surgeonfish_velocity[i].y * dt * movementMultiplier);
						if (!eatingSurgeon)
							animation(Surgeonfish[i], Surgeonfish_currentFrame[i], enemyMedium.rowMotion, enemyMedium.maxFrameMotion, Surgeonfish_velocity[i], Surgeonfish_direction[i], Surgeonfish_clock[i], Surgeonfish_time[i], animationLoopTime[1]);

						playerAndEnemyCollision(player.sprite, Surgeonfish[i], player.score, enemyMedium.score, deathStatus, i, Surgeonfish, Surgeonfish_velocity,
							Surgeonfish_direction, Surgeonfish_directionRand, Surgeonfish_currentFrame, Surgeonfish_clock, Surgeonfish_time, eating, currentFrameEating, player.direction,
							eatingClock, eatingTime, eatingsurgeonsound, frenzyRow, frenzyColumn, ateInLastSeconds,
							frenzyClock, Feedingfrenysound, doublefrenzysound, eatgulpsound, leaderboardScore, frenzymulti, chompSprite, eatingnum);
					}
					for (int i = 0; i < JohnDory.size(); i++)
					{
						enemyMovement(JohnDory_velocity[i], JohnDory_direction[i], JohnDory_directionRand[i], dt,
							enemySmall.maxVel, enemySmall.accel, enemySmall.resist, movementMultiplier, JohnDory[i]);
						if (player.score >= enemyLarge.score)
						{
							enemyBehavior(player.sprite, JohnDory[i], JohnDory_velocity[i], JohnDory_direction[i], dt,
								enemyLarge.maxVel, enemyLarge.accel, enemyLarge.resist, movementMultiplier);
						}
						JohnDory[i].move(JohnDory_velocity[i].x * dt * movementMultiplier, JohnDory_velocity[i].y * dt * movementMultiplier);

						if (!eatingJohnDory)
							animation(JohnDory[i], JohnDory_currentFrame[i], enemyLarge.rowMotion, enemyLarge.maxFrameMotion, JohnDory_velocity[i], JohnDory_direction[i], JohnDory_clock[i], JohnDory_time[i], animationLoopTime[2]);

						playerAndEnemyCollision(player.sprite, JohnDory[i], player.score, enemyLarge.score, deathStatus, i, JohnDory, JohnDory_velocity,
							JohnDory_direction, JohnDory_directionRand, JohnDory_currentFrame, JohnDory_clock, JohnDory_time, eating, currentFrameEating, player.direction,
							eatingClock, eatingTime, eatingjohndorysound, frenzyRow, frenzyColumn, ateInLastSeconds,
							frenzyClock, Feedingfrenysound, doublefrenzysound, eatgulpsound, leaderboardScore, frenzymulti, chompSprite, eatingnum);
					}
				}


				//Enemy and enemy collision
				bool skipMinnow = false;
				for (int i = 0; i < Minnow.size(); i++)
				{
					//Shark and minnow
					if (sharkSprite.getGlobalBounds().intersects(Minnow[i].getGlobalBounds()))
					{
						sharkCurrentFrame = 0;
						sharkEating = true;
						Minnow.erase(Minnow.begin() + i);
						Minnow_velocity.erase(Minnow_velocity.begin() + i);
						Minnow_direction.erase(Minnow_direction.begin() + i);
						Minnow_directionRand.erase(Minnow_directionRand.begin() + i);
						Minnow_currentFrame.erase(Minnow_currentFrame.begin() + i);
						Minnow_clock.erase(Minnow_clock.begin() + i);
						Minnow_time.erase(Minnow_time.begin() + i);
						skipMinnow = true;
					}
					bool skipSurgeon = false;
					bool skipJohn = false;
					for (int j = 0; j < Surgeonfish.size(); j++)
					{
						//Shark and surgeonfish
						if (sharkSprite.getGlobalBounds().intersects(Surgeonfish[j].getGlobalBounds()))
						{
							sharkCurrentFrame = 0;
							sharkEating = true;
							Surgeonfish.erase(Surgeonfish.begin() + j);
							Surgeonfish_velocity.erase(Surgeonfish_velocity.begin() + j);
							Surgeonfish_direction.erase(Surgeonfish_direction.begin() + j);
							Surgeonfish_directionRand.erase(Surgeonfish_directionRand.begin() + j);
							Surgeonfish_currentFrame.erase(Surgeonfish_currentFrame.begin() + j);
							Surgeonfish_clock.erase(Surgeonfish_clock.begin() + j);
							Surgeonfish_time.erase(Surgeonfish_time.begin() + j);
							skipSurgeon = true;
						}
						if (skipMinnow)
							break;
						if (skipSurgeon)
							break;
						//Minnow and Surgeonfish
						enemyAndEnemyCollision(Minnow[i], Surgeonfish[j], enemySmall.score, enemyMedium.score, i, j, Minnow, Surgeonfish, Minnow_velocity, Surgeonfish_velocity,
							Minnow_direction, Surgeonfish_direction, Minnow_directionRand, Surgeonfish_directionRand, Minnow_currentFrame, Surgeonfish_currentFrame,
							Minnow_clock, Surgeonfish_clock, Minnow_time, Surgeonfish_time, skipMinnow,
							eatingMinnow, currentFrameEatingMinnow, Minnow_direction[i], eatingClockMinnow, eatingTimeMinnow, 0,
							eatingSurgeon, currentFrameEatingSurgeon, Surgeonfish_direction[j], eatingClockSurgeon, eatingTimeSurgeon, enemyMedium.maxFrameEat);
						if (skipMinnow)
							break;

						for (int k = 0; k < JohnDory.size(); k++)
						{
							//Shark and john dory
							if (sharkSprite.getGlobalBounds().intersects(JohnDory[k].getGlobalBounds()))
							{
								sharkCurrentFrame = 0;
								sharkEating = true;
								JohnDory.erase(JohnDory.begin() + k);
								JohnDory_velocity.erase(JohnDory_velocity.begin() + k);
								JohnDory_direction.erase(JohnDory_direction.begin() + k);
								JohnDory_directionRand.erase(JohnDory_directionRand.begin() + k);
								JohnDory_currentFrame.erase(JohnDory_currentFrame.begin() + k);
								JohnDory_clock.erase(JohnDory_clock.begin() + k);
								JohnDory_time.erase(JohnDory_time.begin() + k);
								skipJohn = true;
							}
							//Surgeonfish and JohnDory
							if (skipJohn)
								break;
							enemyAndEnemyCollision(Surgeonfish[j], JohnDory[k], enemyMedium.score, enemyLarge.score, j, k, Surgeonfish, JohnDory, Surgeonfish_velocity, JohnDory_velocity,
								Surgeonfish_direction, JohnDory_direction, Surgeonfish_directionRand, JohnDory_directionRand, Surgeonfish_currentFrame, JohnDory_currentFrame,
								Surgeonfish_clock, JohnDory_clock, Surgeonfish_time, JohnDory_time, skipSurgeon,
								eatingSurgeon, currentFrameEatingSurgeon, Surgeonfish_direction[j], eatingClockSurgeon, eatingTimeSurgeon, enemyMedium.maxFrameEat,
								eatingJohnDory, currentFrameEatingJohnDory, JohnDory_direction[k], eatingClockJohnDory, eatingTimeJohnDory, enemyLarge.maxFrameEat);
							if (skipSurgeon)
								break;
						}
					}
					// Minnow and John Dory
					for (int j = 0; j < JohnDory.size(); j++)
					{
						if (skipMinnow)
							break;
						enemyAndEnemyCollision(Minnow[i], JohnDory[j], enemySmall.score, enemyLarge.score, i, j, Minnow, JohnDory, Minnow_velocity, JohnDory_velocity,
							Minnow_direction, JohnDory_direction, Minnow_directionRand, JohnDory_directionRand, Minnow_currentFrame, JohnDory_currentFrame,
							Minnow_clock, JohnDory_clock, Minnow_time, JohnDory_time, skipMinnow,
							eatingMinnow, currentFrameEatingMinnow, Minnow_direction[i], eatingClockMinnow, eatingTimeMinnow, 0,
							eatingJohnDory, currentFrameEatingJohnDory, JohnDory_direction[j], eatingClockJohnDory, eatingTimeJohnDory, enemyLarge.maxFrameEat);
						if (skipMinnow)
							break;
					}
				}


				//FRENZY DECREASE
				frenzyTimeLimit = frenzyClock.getElapsedTime().asSeconds();
				if (frenzyTimeLimit > 2)
				{
					ateInLastSeconds = false;
				}
				frenzyTimeLoss = frenzyClockLoss.getElapsedTime().asMilliseconds();
				if (!ateInLastSeconds)
				{
					if (frenzyTimeLoss >= 350)
					{
						frenzyClockLoss.restart();
						if (frenzyRow > 0)
							frenzyRow--;

						if (frenzyRow == 0 && frenzyColumn != 0)
						{
							frenzyColumn--;
							if (frenzyColumn > 0)
								frenzyRow = 6;
							else
								frenzyRow = 0;
						}
						if (frenzyRow == 0 && frenzyColumn == 0)
						{
							frenzyColumn = 0;
							frenzyRow = 0;
						}
					}
				}
				//FRENZY UPDATE
				frenzySprite.setTextureRect(IntRect(frenzyColumn * 350, frenzyRow * 120, 350, 120));

				//Frenzy Multiplier
				if (frenzyColumn < 2 && frenzyRow < 6)
				{
					frenzyMultiplier.setString("1X");
					frenzyMultiplier.setFillColor(Color::White);
					frenzymulti = 1;
				}
				else if ((frenzyColumn == 1 && frenzyRow == 6) || (frenzyColumn == 2 && frenzyRow < 6))
				{
					frenzyMultiplier.setString("2X");
					frenzyMultiplier.setFillColor(Color::Blue);
					frenzymulti = 2;
				}
				else if (frenzyColumn == 2 && frenzyRow == 6)
				{
					frenzyMultiplier.setString("3X");
					frenzyMultiplier.setFillColor(Color::Red);
					frenzymulti = 3;
				}

				//Score number update
				ScoreText.setString("" + to_string(leaderboardScore));

				//Redbar Levelup update
				if (BarRed.getSize().x < 694) {
					BarRed.setSize(Vector2f(player.score * 20, 11));
				}
				else
				{
					BarRed.setSize(Vector2f(694, 11));

					if (!redBarMaxReached)
					{
						stagesound.play();


						//High score override
						if (highScoreInFile < leaderboardScore)
						{
							highScoreInFile = leaderboardScore;
							ofHighScore.open("HighScore.txt", ios::out | ios::trunc);
							ofHighScore << leaderboardScore;
							ofHighScore.close();
						}
						levelnumber = 1;
						gamemusic.stop();
						pagenumber = 9;
						endgame(window, mousedownbuffer, mousedownsound, mouseoverbuffer, mouseoversound, introbuffer, introsound, stagebuffer, stagesound, music);


					}
					redBarMaxReached = true;
				}
				//score = false;
				//Render draw
				window.clear();
				if (pagenumber != 5)
				{
					break;
				}
				window.draw(backgroundSprite);

				//Return To Menu to continue
				menu ok(window.getSize().x, window.getSize().y);
				ok.menuu[0].setString("Return To Menu");
				ok.menuu[2].setString("");
				ok.menuu[1].setString("");
				ok.menuu[3].setString("");
				ok.menuu[0].setFillColor(Color::Red);
				ok.menuu[0].setCharacterSize(120);
				ok.menuu[0].setPosition(Vector2f(550, 800));


				//OYSTER ANIMATION AND SHIT
				oysterOpenTime = oysterOpenClock.getElapsedTime().asSeconds();
				oysterStayOpenTime = oysterStayOpenClock.getElapsedTime().asSeconds();
				oysterAnimationTime = oysterAnimationClock.getElapsedTime().asMilliseconds();

				if (oysterOpenTime == 12)
				{
					oysterStayOpenClock.restart().asSeconds();
					oysterAnimationClock.restart().asMilliseconds();
				}
				if (!deathStatus)
				{
					window.draw(oysterSprite);
					if (oysterFrame >= 3)
					{
						if (player.sprite.getGlobalBounds().intersects(pearlSprite.getGlobalBounds()))
						{
							leaderboardScore += 100;
							pearlSprite.setScale(0, 0);
							eating = true;
							pearlEat.play();
						}
						window.draw(pearlSprite);
					}
					if (oysterOpenTime >= 12)
					{

						if (oysterFrame < 4)
						{
							if (oysterAnimationTime >= 40)
							{
								oysterAnimationClock.restart().asMilliseconds();
								oysterSprite.setTextureRect(IntRect((++oysterFrame) * 101, 0, 101, 101));
							}
						}

					}
				}

				if (oysterOpenTime > 12 && oysterStayOpenTime >= 8)
				{
					oysterOpenClock.restart().asSeconds();
					oysterAnimationClock.restart().asMilliseconds();
					oysterClose = true;
				}
				else if (oysterOpenTime < 12 && oysterStayOpenTime >= 8)
				{
					if (oysterFrame > 0 && oysterClose == true)
					{
						if (oysterAnimationTime >= 40)
							oysterSprite.setTextureRect(IntRect((--oysterFrame) * 101, 0, 101, 101));
					}
					else if (oysterFrame == 0)
					{
						oysterClose = false;
						pearlSprite.setScale(2, 2);
					}
				}

				if (player.sprite.getGlobalBounds().intersects(oysterSprite.getGlobalBounds()) && oysterClose == true && oysterFrame == 1)
				{
					deathStatus = true;
					oysterDie.play();
				}
				//Enemy draw
				for (int i = 0; i < Minnow.size(); i++)
				{
					window.draw(Minnow[i]);
				}
				for (int i = 0; i < Surgeonfish.size(); i++)
				{
					window.draw(Surgeonfish[i]);
				}
				for (int i = 0; i < JohnDory.size(); i++)
				{
					window.draw(JohnDory[i]);
				}
				window.draw(sharkSprite);

				//Scorebar, frenzy and player draw
				if (!deathStatus)
				{
					//Scorebar
					window.draw(ScoreBar);
					window.draw(BarBlack);
					window.draw(BarRed);
					window.draw(Triangle);
					window.draw(Triangle1);
					//Enemy sprite in scorebar
					window.draw(ScoreMinnow);
					window.draw(ScoreSurgeonfish);
					window.draw(ScoreJohnDory);
					if (istransparentFish[0])
						window.draw(transparentFish[0]);
					if (istransparentFish[1])
						window.draw(transparentFish[1]);

					//Chomp draw
					if (eating)
						window.draw(chompSprite);

					//Draw frenzy, it's multiplier and the score
					window.draw(frenzyMultiplier);
					window.draw(ScoreText);
					window.draw(frenzySprite);

					//Player
					window.draw(player.sprite);
				}

				//draw background
				else
				{
					ok.draw(window);
					window.draw(GameOverBackground);
					window.draw(GameOver);
					//return to main menu after game over
					while (window.pollEvent(event))
					{
						if (event.type == Event::KeyReleased && event.key.code == Keyboard::Return)
						{
							pagenumber = 0;
							windoww(window, mousedownbuffer, mousedownsound, mouseoverbuffer, mouseoversound, introbuffer, introsound, stagebuffer, stagesound, music);



						}
					}
					if (playDeathSound)
					{
						GameOverSound.play();
						playDeathSound = false;
						gamemusic.stop();


					}
					if (highScoreInFile < leaderboardScore)
					{
						highScoreInFile = leaderboardScore;
						ofHighScore.open("HighScore.txt", ios::out | ios::trunc);
						ofHighScore << leaderboardScore;
						ofHighScore.close();
					}
				}


				//when pause menu open
				if (pausemenuisopen)
				{
					window.setView(view);
					window.draw(pausemenusprite);
					pausemenu.draw(window);
				}


				window.display();
			}

			if (pausenumber == 0)
			{
				pausemenuisopen = false;

			}
			if (pagenumber == 500)
			{

				pagenumber = 0;
				music.play();
				windoww(window, mousedownbuffer, mousedownsound, mouseoverbuffer, mouseoversound, introbuffer, introsound, stagebuffer, stagesound, music);
			}
			if (pagenumber == 2)
			{
				gamemusic.pause();
				window.close();

			}
		}
	}
}
void Level2(RenderWindow& window, SoundBuffer& mousedownbuffer, Sound& mousedownsound, SoundBuffer& mouseoverbuffer, Sound& mouseoversound, SoundBuffer& introbuffer, Sound& introsound, SoundBuffer& stagebuffer, Sound& stagesound, Music& music)
{
	levelnumber = 2;
	const unsigned WINDOW_WIDTH = 1920, WINDOW_HEIGHT = 1080;
	//RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Feeding Frenzy", Style::Fullscreen);

	//Icon
	Image icon;
	icon.loadFromFile("Resources/Backgrounds/Icon.png");
	//windowGame.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	leaderboardScore = 0;

	//Pause Menu
	menu pausemenu(window.getSize().x, window.getSize().y);
	pausemenu.menuu[0].setString("Resume");
	pausemenu.menuu[1].setString("Levels Menu");
	pausemenu.menuu[2].setString("Exit");
	pausemenu.menuu[3].setString("");

	bool pausemenuisopen = false;

	//pausemenu texture
	Texture pausemenutexture;
	pausemenutexture.loadFromFile("Resources/Backgrounds/pausemenu1.jpg");
	Sprite pausemenusprite;
	pausemenusprite.setTexture(pausemenutexture);

	//Game Over Texture
	Texture GameOvertexture;
	GameOvertexture.loadFromFile("Resources/Backgrounds/GameOver.png");
	Sprite GameOver;
	GameOver.setTexture(GameOvertexture);
	GameOver.setScale(1.8, 1.8);
	GameOver.setPosition(550, 200);
	RectangleShape GameOverBackground;
	GameOverBackground.setSize(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	GameOverBackground.setFillColor(Color(0, 0, 0, 100));

	//Background
	Texture backgroundTexture;
	backgroundTexture.loadFromFile("Resources/Backgrounds/background.jpg");
	Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);
	Vector2u sizeBG = backgroundTexture.getSize();
	backgroundSprite.setOrigin(sizeBG.x / 2, sizeBG.y / 2);
	backgroundSprite.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);




	//score bar texture
	Texture scorebartexture;
	scorebartexture.loadFromFile("Resources/Backgrounds/Scorebar.jpeg");
	Sprite ScoreBar;
	ScoreBar.setTexture(scorebartexture);
	ScoreBar.setScale(1.5, 1);
	ScoreBar.setTextureRect(IntRect(0, 0, 1314, 135));

	//menu texture for minnow
	Texture ScoreMinnowTexture;
	ScoreMinnowTexture.loadFromFile("Resources/Sprites/Minnow.png");
	Sprite ScoreMinnow;
	ScoreMinnow.setTexture(ScoreMinnowTexture);
	ScoreMinnow.setPosition(400, 0);
	ScoreMinnow.setScale(2, 2);
	ScoreMinnow.setTextureRect(IntRect(66, 0, -66, 49));

	//menu texture for surgeon
	Texture ScoreSurgeonfishTexture;
	ScoreSurgeonfishTexture.loadFromFile("Resources/Sprites/Surgeonfish.png");
	Sprite ScoreSurgeonfish;
	ScoreSurgeonfish.setTexture(ScoreSurgeonfishTexture);
	ScoreSurgeonfish.setPosition(600, 5);
	ScoreSurgeonfish.setScale(0, 0);
	ScoreSurgeonfish.setTextureRect(IntRect(171, 0, -171, 106));

	//menu texture for john dory
	Texture ScoreJohnDoryTexture;
	ScoreJohnDoryTexture.loadFromFile("Resources/Sprites/John Dory.png");
	Sprite ScoreJohnDory;
	ScoreJohnDory.setTexture(ScoreJohnDoryTexture);
	ScoreJohnDory.setPosition(860, -27);
	ScoreJohnDory.setScale(0, 0);
	ScoreJohnDory.setTextureRect(IntRect(181, 0, -181, 181));

	//transparent  fish
	Texture transparentFishtexture;
	transparentFishtexture.loadFromFile("Resources/Sprites/Ellipse_15.png");
	Sprite transparentFish[2];
	transparentFish[0].setTexture(transparentFishtexture);
	transparentFish[1].setTexture(transparentFishtexture);
	bool istransparentFish[2] = { true,true };
	transparentFish[0].setScale(0, 0);
	transparentFish[1].setScale(0, 0);
	transparentFish[0].setPosition(580, -10);
	transparentFish[1].setPosition(817, -18);

	//default bar
	RectangleShape BarBlack;
	BarBlack.setSize(Vector2f(700, 15));
	BarBlack.setPosition(390, 93);
	BarBlack.setFillColor(Color::Black);

	//Levelup bar
	RectangleShape BarRed;
	BarRed.setSize(Vector2f(94, 11));
	BarRed.setPosition(393, 95);
	BarRed.setFillColor(Color::Red);

	CircleShape Triangle;
	Triangle.setRadius(18);
	Triangle.setPointCount(3);
	Triangle.setPosition(575, 99);
	Triangle.setFillColor(Color::Blue);

	CircleShape Triangle1;
	Triangle1.setRadius(18);
	Triangle1.setPointCount(3);
	Triangle1.setPosition(773, 99);
	Triangle1.setFillColor(Color::Blue);


	//clock texture
	Texture clockTimerTexture;
	clockTimerTexture.loadFromFile("Resources/Sprites/clockk.png");

	Sprite clockTimer;
	clockTimer.setTexture(clockTimerTexture);
	clockTimer.setScale(0.025, 0.025);
	clockTimer.setPosition(865, 915);

	Clock levelTwoClock;
	int levelTwoTimer;
	int timerBeforePause = 0;
	bool timeSaved = false;

	//clock background
	Texture clockbackgroundTexture;
	clockbackgroundTexture.loadFromFile("Resources/Sprites/Rounded Rectangle 1.png");
	Sprite clockbackground[2];
	clockbackground[0].setTexture(clockbackgroundTexture);
	clockbackground[0].setPosition(1630, 915);
	clockbackground[0].setScale(0.38, 0.4);
	clockbackground[1].setTexture(clockbackgroundTexture);
	clockbackground[1].setPosition(830, 890);
	clockbackground[1].setScale(0.55, 0.63);

	//timer font
	Font TimerFont;
	TimerFont.loadFromFile("Resources/Fonts/Roboto-Black.ttf");
	Text Timer;
	Timer.setFont(TimerFont);
	Timer.setCharacterSize(50);
	Timer.setFillColor(Color::White);
	Timer.setPosition(1000, 930);

	//number of fish font
	Font eatingNumFont;
	eatingNumFont.loadFromFile("Resources/Fonts/Roboto-Black.ttf");
	Text eatingNumText;
	eatingNumText.setFont(eatingNumFont);
	eatingNumText.setCharacterSize(50);
	eatingNumText.setFillColor(Color::White);
	eatingNumText.setPosition(1650, 930);

	int eatingNum = 0;




	//Score number
	Font Scorefont;
	Scorefont.loadFromFile("Resources/Fonts/GUMDROP.ttf");
	Text ScoreText;
	ScoreText.setFont(Scorefont);
	ScoreText.setCharacterSize(40);
	ScoreText.setFillColor(Color::White);
	ScoreText.setPosition(1560, 20);


	//Clock, elapsed time, framerate independence
	Clock dt_clock, spawn_clock[3], movement_clock[3], animationClock;
	float dt;


	//Movement, spawn and random direction intialization
	float movementMultiplier = 60.f;
	float enemySpawnTimeElapsed[3];
	float enemyMovementTimeElapsed[3];
	int enemyDirectionRandomizer[3] = { 0, 0, 0 };


	//Animation initialization
	float animationTime = animationClock.getElapsedTime().asMilliseconds();
	float animationLoopTime[3] = { 60, 80, 100 };
	int currentFramePlayer = 0;
	int currentFrameEnemy[3] = { 0, 0, 0 };




	//FRENZY
	Texture frenzyTexture;
	frenzyTexture.loadFromFile("Resources/Sprites/FRENZY.png");
	Sprite frenzySprite;
	frenzySprite.setTexture(frenzyTexture);
	frenzySprite.setTextureRect(IntRect(0, 0, 350, 120));
	frenzySprite.setPosition(WINDOW_WIDTH / 2 - 175, WINDOW_HEIGHT / 2 - 360);
	Clock frenzyClock, frenzyClockLoss;
	float frenzyTimeLimit = frenzyClock.getElapsedTime().asSeconds(), frenzyTimeLoss;
	bool ateInLastSeconds = false;
	int frenzyColumn = 0, frenzyRow = 0;
	int frenzymulti = 1;

	//font multiplier
	Font frenzyMultiFont;
	frenzyMultiFont.loadFromFile("Resources/Fonts/Roboto-Black.ttf");
	Text frenzyMultiplier;
	frenzyMultiplier.setFont(frenzyMultiFont);
	frenzyMultiplier.setFillColor(Color::White);
	frenzyMultiplier.setOutlineColor(Color::Black);
	frenzyMultiplier.setOutlineThickness(3);
	frenzyMultiplier.setPosition(1760, 5);
	frenzyMultiplier.setCharacterSize(70);


	//chomp 
	Texture chompTexture;
	chompTexture.loadFromFile("Resources/Sprites/Chomp.png");
	Sprite chompSprite;
	chompSprite.setTexture(chompTexture);


	//Player
	Entity player = { 0, 2, 3, 14, 4, 0, 11.25f, 0.6f, 0.2f };
	player.texture.loadFromFile("Resources/Sprites/Angelfish.png");
	player.sprite.setTexture(player.texture);
	player.sprite.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	player.sprite.setTextureRect(IntRect(126, 106, -126, 106));
	player.sprite.setScale(Vector2f(0.8, 0.8));
	bool deathStatus = false;
	int currentFrameIdle = 0, maxFrameIdle = 6;
	Clock idleClock;
	float idleTimer;
	bool eating = false;
	int currentFrameEating = 0;
	Clock eatingClock;
	float eatingTime = eatingClock.getElapsedTime().asMilliseconds();

	//Small enemies / Minnow
	Entity enemySmall = { 0, 0, 1, 14, 5, 0, 3.75f, 0.375f, 0.05f };
	enemySmall.texture.loadFromFile("Resources/Sprites/Minnow.png");
	enemySmall.sprite.setTexture(enemySmall.texture);
	enemySmall.sprite.setTextureRect(IntRect(66, 0, -66, 49));
	vector <Sprite> Minnow;
	vector <Vector2f> Minnow_velocity;
	vector <Vector2f> Minnow_direction;
	vector <int> Minnow_directionRand;
	vector <int> Minnow_currentFrame;
	vector <Clock> Minnow_clock;
	vector <float> Minnow_time;
	bool eatingMinnow = false;
	int currentFrameEatingMinnow = 0;
	Clock eatingClockMinnow;
	float eatingTimeMinnow = eatingClockMinnow.getElapsedTime().asMilliseconds();

	//Medium enemies / Surgeonfish
	Entity enemyMedium = { 10, 1, 2, 13, 4, 5, 3.f, 0.3f, 0.16875f };
	enemyMedium.texture.loadFromFile("Resources/Sprites/Surgeonfish.png");
	enemyMedium.sprite.setTexture(enemyMedium.texture);
	enemyMedium.sprite.setTextureRect(IntRect(171, 0, -171, 106));
	enemyMedium.sprite.setScale(0, 0);
	vector <Sprite> Surgeonfish;
	vector <Vector2f> Surgeonfish_velocity;
	vector <Vector2f> Surgeonfish_direction;
	vector <int> Surgeonfish_directionRand;
	vector <int> Surgeonfish_currentFrame;
	vector <Clock> Surgeonfish_clock;
	vector <float> Surgeonfish_time;
	int surgeonSpawnTimer = 8;
	bool eatingSurgeon = false;
	int currentFrameEatingSurgeon = 0;
	Clock eatingClockSurgeon;
	float eatingTimeSurgeon = eatingClockSurgeon.getElapsedTime().asMilliseconds();

	//Large enemies / John Dory
	Entity enemyLarge = { 20, 1, 2, 14, 4, 6, 2.25f, 0.225f, 0.1875f };
	enemyLarge.texture.loadFromFile("Resources/Sprites/John Dory.png");
	enemyLarge.sprite.setTexture(enemyLarge.texture);
	enemyLarge.sprite.setTextureRect(IntRect(181, 0, -181, 181));
	enemyLarge.sprite.setScale(0, 0);
	vector <Sprite> JohnDory;
	vector <Vector2f> JohnDory_velocity;
	vector <Vector2f> JohnDory_direction;
	vector <int> JohnDory_directionRand;
	vector <int> JohnDory_currentFrame;
	vector <Clock> JohnDory_clock;
	vector <float> JohnDory_time;
	bool eatingJohnDory = false;
	int currentFrameEatingJohnDory = 0;
	Clock eatingClockJohnDory;
	float eatingTimeJohnDory = eatingClockJohnDory.getElapsedTime().asMilliseconds();





	//SOUNDS

	//minnowEating sound
	SoundBuffer eatingminnowbuffer;
	eatingminnowbuffer.loadFromFile("Resources/sounds/bite1.ogg");
	Sound eatingminnowsound;
	eatingminnowsound.setBuffer(eatingminnowbuffer);
	bool eatingminnowboolean = true;

	//surgeonEating sound
	SoundBuffer eatingsurgeonbuffer;
	eatingsurgeonbuffer.loadFromFile("Resources/sounds/bite2.ogg");
	Sound eatingsurgeonsound;
	eatingsurgeonsound.setBuffer(eatingsurgeonbuffer);
	bool eatingsurgeonboolean = true;

	//johndoryEating sound
	SoundBuffer eatingjohndorybuffer;
	eatingjohndorybuffer.loadFromFile("Resources/sounds/bite3.ogg");
	Sound eatingjohndorysound;
	eatingjohndorysound.setBuffer(eatingjohndorybuffer);
	bool eatingjohndoryboolean = true;

	//SoundBuffer GameOver
	SoundBuffer GameOverSoundbuffer;
	GameOverSoundbuffer.loadFromFile("Resources/sounds/GameOver.ogg");
	Sound GameOverSound;
	GameOverSound.setBuffer(GameOverSoundbuffer);
	bool playDeathSound = true;

	//gamemusic
	bool musicisplayed = true;
	Music gamemusic;
	gamemusic.openFromFile("Resources/music/timerlevel.ogg");
	gamemusic.play();
	gamemusic.setLoop(musicisplayed);

	//frenzy sound
	SoundBuffer Feedingfrenysoundbuffer;
	Feedingfrenysoundbuffer.loadFromFile("Resources/sounds/feedingFrenzy.ogg");
	Sound Feedingfrenysound;
	Feedingfrenysound.setBuffer(Feedingfrenysoundbuffer);


	//doublefrenzy sound
	SoundBuffer doublefrenzysoundbuffer;
	doublefrenzysoundbuffer.loadFromFile("Resources/sounds/doubleFrenzy.ogg");
	Sound doublefrenzysound;
	doublefrenzysound.setBuffer(doublefrenzysoundbuffer);

	//growth sound
	SoundBuffer Growthsoundbuffer;
	Growthsoundbuffer.loadFromFile("Resources/sounds/playerGrow.ogg");
	Sound Growthsound;
	Growthsound.setBuffer(Growthsoundbuffer);
	bool Growthsoundboolean = true;

	//eatgulp sound
	SoundBuffer eatgulpsoundbuffer;
	eatgulpsoundbuffer.loadFromFile("Resources/sounds/eatGulp.ogg");
	Sound eatgulpsound;
	eatgulpsound.setBuffer(eatgulpsoundbuffer);



	//view camera pausemenu
	View view(FloatRect(0, 0, 1000, 1000));
	View view1(FloatRect(0, 0, 1920, 1080));
	pausemenu.menuu[0].setCharacterSize(70);
	pausemenu.menuu[1].setCharacterSize(65);
	pausemenu.menuu[2].setCharacterSize(70);
	pausemenu.menuu[0].setPosition(Vector2f(400, 430));
	pausemenu.menuu[1].setPosition(Vector2f(350, 550));
	pausemenu.menuu[2].setPosition(Vector2f(420, 670));


	//Keeping the highest score
	ofstream ofHighScore;
	ifstream ifHighScore;

	ifHighScore.open("HighScore.txt", ios::in);

	ifHighScore >> highScoreInFile;
	ifHighScore.close();

	bool redBarMaxReached = false;


	while (true)
	{
		if (pagenumber == 6)
		{

			while (window.isOpen())
			{
				window.setView(view1);

				//Exiting
				Event event;
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed)
						window.close();
					if (event.type == Event::KeyPressed)
					{
						if (event.key.code == Keyboard::Escape)
						{
							pausemenuisopen = true;
						}
						if (event.key.code == Keyboard::Up)
						{
							if (pausemenuisopen)
								mousedownsound.play();
							pausemenu.pausemoveup();
						}
						if (event.key.code == Keyboard::Down)
						{
							if (pausemenuisopen)
								mousedownsound.play();
							pausemenu.pausemovedown();
						}
						if (event.key.code == Keyboard::Return)
						{
							if (pausemenu.getselecteditem() == 0)
							{
								pausenumber = 0;
								pausemenuisopen = false;
							}
							if (pausemenu.getselecteditem() == 1)
							{
								gamemusic.pause();
								pagenumber = 100;
							}
							if (pausemenu.getselecteditem() == 2)
							{
								window.close();
								pausenumber = 2;

							}
						}


					}

				}


				//Time between frames
				dt = dt_clock.restart().asSeconds();


				levelTwoTimer = levelTwoClock.getElapsedTime().asSeconds();



				//Player's movement, collision with screen
				if (!pausemenuisopen)
				{
					playerMovement(player.velocity, player.direction, dt, player.maxVel, player.accel, player.resist, movementMultiplier);
					player.sprite.move(player.velocity.x * dt * movementMultiplier, player.velocity.y * dt * movementMultiplier);
				}
				playerScreenCollision(player.sprite, WINDOW_WIDTH, WINDOW_HEIGHT);

				//Player's animation
				if (!eating)
					animation(player.sprite, currentFramePlayer, player.rowMotion, player.maxFrameMotion, player.velocity,
						player.direction, animationClock, animationTime);

				//Player's idle animation
				if (player.velocity.x == 0 && player.velocity.y == 0)
				{
					idleTimer = idleClock.getElapsedTime().asMilliseconds();
					if (idleTimer >= 120)
					{
						if (player.direction.x >= 0)
						{
							player.sprite.setTextureRect(IntRect(currentFrameIdle * 126 + 126, 106, -126, 106));
							currentFrameIdle++;
							idleClock.restart();
						}
						else if (player.direction.x < 0)
						{
							player.sprite.setTextureRect(IntRect(currentFrameIdle * 126, 106, 126, 106));
							currentFrameIdle++;
							idleClock.restart();
						}
						if (currentFrameIdle >= maxFrameIdle)
							currentFrameIdle = 0;
					}
				}

				//Player levelup
				if (player.score >= enemyMedium.score && player.score < enemyLarge.score)
				{
					//player.sprite.setScale(1.1, 1.1);
					istransparentFish[0] = false;
					if (Growthsoundboolean) {
						//Growthsound.play();
						Growthsoundboolean = false;
					}
				}
				if (player.score >= enemyLarge.score)
				{
					//player.sprite.setScale(1.6, 1.6);
					istransparentFish[1] = false;
					if (!Growthsoundboolean) {
						//Growthsound.play();
						Growthsoundboolean = true;
					}
				}
				if (player.score >= enemyMedium.score)
					surgeonSpawnTimer = 3;

				//Enemy spawn
				if (!pausemenuisopen)
				{
					//Spawn timer
					for (int i = 0; i < 3; i++)
					{
						enemySpawnTimeElapsed[i] = spawn_clock[i].getElapsedTime().asSeconds();
					}
					//Minnow or small
					if (Minnow.size() <= 16)
					{
						if (enemySpawnTimeElapsed[0] >= 0.5)
						{
							int side = rand() % 2;
							if (side == 0)
								enemySmall.sprite.setPosition(0 - enemySmall.sprite.getGlobalBounds().width, rand() % (WINDOW_HEIGHT - 135) + 135);
							else
								enemySmall.sprite.setPosition(WINDOW_WIDTH, rand() % (WINDOW_HEIGHT - 135) + 135);

							Minnow.push_back(enemySmall.sprite);
							Minnow_velocity.push_back(enemySmall.velocity);
							Minnow_direction.push_back(enemySmall.direction);
							Minnow_directionRand.push_back(enemyDirectionRandomizer[0]);
							Minnow_currentFrame.push_back(currentFrameEnemy[0]);
							Minnow_clock.push_back(animationClock);
							Minnow_time.push_back(animationTime);

							enemySpawnTimeElapsed[0] = spawn_clock[0].restart().asSeconds();
						}
					}
					//Surgeonfish or medium
					if (Surgeonfish.size() <= 12)
					{
						if (enemySpawnTimeElapsed[1] >= surgeonSpawnTimer)
						{
							int side = rand() % 2;
							if (side == 0)
								enemyMedium.sprite.setPosition(0 - enemyMedium.sprite.getGlobalBounds().width, rand() % (WINDOW_HEIGHT - 135) + 135);
							else
								enemyMedium.sprite.setPosition(WINDOW_WIDTH, rand() % (WINDOW_HEIGHT - 135) + 135);

							Surgeonfish.push_back(enemyMedium.sprite);
							Surgeonfish_velocity.push_back(enemyMedium.velocity);
							Surgeonfish_direction.push_back(enemyMedium.direction);
							Surgeonfish_directionRand.push_back(enemyDirectionRandomizer[1]);
							Surgeonfish_currentFrame.push_back(currentFrameEnemy[1]);
							Surgeonfish_clock.push_back(animationClock);
							Surgeonfish_time.push_back(animationTime);

							enemySpawnTimeElapsed[1] = spawn_clock[1].restart().asSeconds();
						}
					}
					// John Dory or large
					if (JohnDory.size() <= 2)
					{
						if (enemySpawnTimeElapsed[2] >= 18)
						{
							int side = rand() % 2;
							if (side == 0)
								enemyLarge.sprite.setPosition(0 - enemyLarge.sprite.getGlobalBounds().width, rand() % (WINDOW_HEIGHT - 135) + 135);
							else
								enemyLarge.sprite.setPosition(WINDOW_WIDTH, rand() % (WINDOW_HEIGHT - 135) + 135);

							JohnDory.push_back(enemyLarge.sprite);
							JohnDory_velocity.push_back(enemyLarge.velocity);
							JohnDory_direction.push_back(enemyLarge.direction);
							JohnDory_directionRand.push_back(enemyDirectionRandomizer[2]);
							JohnDory_currentFrame.push_back(currentFrameEnemy[2]);
							JohnDory_clock.push_back(animationClock);
							JohnDory_time.push_back(animationTime);

							enemySpawnTimeElapsed[2] = spawn_clock[2].restart().asSeconds();
						}
					}

					//Direction Randomizer
					for (int i = 0; i < 3; i++)
					{
						enemyMovementTimeElapsed[i] = movement_clock[i].getElapsedTime().asSeconds();
						if (enemyMovementTimeElapsed[i] >= 1)
						{
							if (i == 0)
							{
								for (int j = 0; j < Minnow.size(); j++)
								{
									Minnow_directionRand[j] = rand() % 8;
								}
							}
							if (i == 1)
							{
								for (int j = 0; j < Surgeonfish.size(); j++)
								{
									Surgeonfish_directionRand[j] = rand() % 8;
								}
							}
							if (i == 2)
							{
								for (int j = 0; j < JohnDory.size(); j++)
								{
									JohnDory_directionRand[j] = rand() % 8;
								}
							}
							enemyMovementTimeElapsed[i] = 0;
							movement_clock[i].restart();
						}
					}

					// enemy movement, behaviour, collision
					for (int i = 0; i < Minnow.size(); i++)
					{
						enemyMovement(Minnow_velocity[i], Minnow_direction[i], Minnow_directionRand[i], dt,
							enemySmall.maxVel, enemySmall.accel, enemySmall.resist, movementMultiplier, Minnow[i]); //DOESN'T MOVE IF THIS IS COMMENTED

						enemyBehavior(player.sprite, Minnow[i], Minnow_velocity[i], Minnow_direction[i], dt,
							enemySmall.maxVel, enemySmall.accel, enemySmall.resist, movementMultiplier);
						Minnow[i].move(Minnow_velocity[i].x * dt * movementMultiplier, Minnow_velocity[i].y * dt * movementMultiplier);

						animation(Minnow[i], Minnow_currentFrame[i], enemySmall.rowMotion, enemySmall.maxFrameMotion, Minnow_velocity[i],
							Minnow_direction[i], Minnow_clock[i], Minnow_time[i], animationLoopTime[0]);

						playerAndEnemyCollision(player.sprite, Minnow[i], player.score, enemySmall.score, deathStatus, i, Minnow, Minnow_velocity,
							Minnow_direction, Minnow_directionRand, Minnow_currentFrame, Minnow_clock, Minnow_time, eating, currentFrameEating, player.direction,
							eatingClock, eatingTime, eatingminnowsound, frenzyRow, frenzyColumn, ateInLastSeconds, frenzyClock,
							Feedingfrenysound, doublefrenzysound, eatgulpsound, leaderboardScore, frenzymulti, chompSprite, eatingNum);
					}
					for (int i = 0; i < Surgeonfish.size(); i++)
					{
						enemyMovement(Surgeonfish_velocity[i], Surgeonfish_direction[i], Surgeonfish_directionRand[i], dt,
							enemySmall.maxVel, enemySmall.accel, enemySmall.resist, movementMultiplier, Surgeonfish[i]);
						if (player.score >= enemyMedium.score)
						{
							enemyBehavior(player.sprite, Surgeonfish[i], Surgeonfish_velocity[i], Surgeonfish_direction[i], dt,
								enemyMedium.maxVel, enemyMedium.accel, enemyMedium.resist, movementMultiplier);
						}
						Surgeonfish[i].move(Surgeonfish_velocity[i].x * dt * movementMultiplier, Surgeonfish_velocity[i].y * dt * movementMultiplier);
						if (!eatingSurgeon)
							animation(Surgeonfish[i], Surgeonfish_currentFrame[i], enemyMedium.rowMotion, enemyMedium.maxFrameMotion, Surgeonfish_velocity[i], Surgeonfish_direction[i], Surgeonfish_clock[i], Surgeonfish_time[i], animationLoopTime[1]);

						playerAndEnemyCollision(player.sprite, Surgeonfish[i], player.score, enemyMedium.score, deathStatus, i, Surgeonfish, Surgeonfish_velocity,
							Surgeonfish_direction, Surgeonfish_directionRand, Surgeonfish_currentFrame, Surgeonfish_clock, Surgeonfish_time, eating, currentFrameEating, player.direction,
							eatingClock, eatingTime, eatingsurgeonsound, frenzyRow, frenzyColumn, ateInLastSeconds,
							frenzyClock, Feedingfrenysound, doublefrenzysound, eatgulpsound, leaderboardScore, frenzymulti, chompSprite, eatingNum);
					}
					for (int i = 0; i < JohnDory.size(); i++)
					{
						enemyMovement(JohnDory_velocity[i], JohnDory_direction[i], JohnDory_directionRand[i], dt,
							enemySmall.maxVel, enemySmall.accel, enemySmall.resist, movementMultiplier, JohnDory[i]);
						if (player.score >= enemyLarge.score)
						{
							enemyBehavior(player.sprite, JohnDory[i], JohnDory_velocity[i], JohnDory_direction[i], dt,
								enemyLarge.maxVel, enemyLarge.accel, enemyLarge.resist, movementMultiplier);
						}
						JohnDory[i].move(JohnDory_velocity[i].x * dt * movementMultiplier, JohnDory_velocity[i].y * dt * movementMultiplier);

						if (!eatingJohnDory)
							animation(JohnDory[i], JohnDory_currentFrame[i], enemyLarge.rowMotion, enemyLarge.maxFrameMotion, JohnDory_velocity[i], JohnDory_direction[i], JohnDory_clock[i], JohnDory_time[i], animationLoopTime[2]);

						playerAndEnemyCollision(player.sprite, JohnDory[i], player.score, enemyLarge.score, deathStatus, i, JohnDory, JohnDory_velocity,
							JohnDory_direction, JohnDory_directionRand, JohnDory_currentFrame, JohnDory_clock, JohnDory_time, eating, currentFrameEating, player.direction,
							eatingClock, eatingTime, eatingjohndorysound, frenzyRow, frenzyColumn, ateInLastSeconds,
							frenzyClock, Feedingfrenysound, doublefrenzysound, eatgulpsound, leaderboardScore, frenzymulti, chompSprite, eatingNum);
					}
				}

				//Enemy and enemy collision
				bool skipMinnow = false;
				for (int i = 0; i < Minnow.size(); i++)
				{
					//Minnow and Surgeonfish
					for (int j = 0; j < Surgeonfish.size(); j++)
					{
						enemyAndEnemyCollision(Minnow[i], Surgeonfish[j], enemySmall.score, enemyMedium.score, i, j, Minnow, Surgeonfish, Minnow_velocity, Surgeonfish_velocity,
							Minnow_direction, Surgeonfish_direction, Minnow_directionRand, Surgeonfish_directionRand, Minnow_currentFrame, Surgeonfish_currentFrame,
							Minnow_clock, Surgeonfish_clock, Minnow_time, Surgeonfish_time, skipMinnow,
							eatingMinnow, currentFrameEatingMinnow, Minnow_direction[i], eatingClockMinnow, eatingTimeMinnow, 0,
							eatingSurgeon, currentFrameEatingSurgeon, Surgeonfish_direction[j], eatingClockSurgeon, eatingTimeSurgeon, enemyMedium.maxFrameEat);
						if (skipMinnow)
							break;

						//Surgeonfish and JohnDory
						bool skipSurgeon = false;
						for (int k = 0; k < JohnDory.size(); k++)
						{
							enemyAndEnemyCollision(Surgeonfish[j], JohnDory[k], enemyMedium.score, enemyLarge.score, j, k, Surgeonfish, JohnDory, Surgeonfish_velocity, JohnDory_velocity,
								Surgeonfish_direction, JohnDory_direction, Surgeonfish_directionRand, JohnDory_directionRand, Surgeonfish_currentFrame, JohnDory_currentFrame,
								Surgeonfish_clock, JohnDory_clock, Surgeonfish_time, JohnDory_time, skipSurgeon,
								eatingSurgeon, currentFrameEatingSurgeon, Surgeonfish_direction[j], eatingClockSurgeon, eatingTimeSurgeon, enemyMedium.maxFrameEat,
								eatingJohnDory, currentFrameEatingJohnDory, JohnDory_direction[k], eatingClockJohnDory, eatingTimeJohnDory, enemyLarge.maxFrameEat);
							if (skipSurgeon)
								break;
						}
					}
					// Minnow and John Dory
					for (int j = 0; j < JohnDory.size(); j++)
					{
						if (skipMinnow)
							break;
						enemyAndEnemyCollision(Minnow[i], JohnDory[j], enemySmall.score, enemyLarge.score, i, j, Minnow, JohnDory, Minnow_velocity, JohnDory_velocity,
							Minnow_direction, JohnDory_direction, Minnow_directionRand, JohnDory_directionRand, Minnow_currentFrame, JohnDory_currentFrame,
							Minnow_clock, JohnDory_clock, Minnow_time, JohnDory_time, skipMinnow,
							eatingMinnow, currentFrameEatingMinnow, Minnow_direction[i], eatingClockMinnow, eatingTimeMinnow, 0,
							eatingJohnDory, currentFrameEatingJohnDory, JohnDory_direction[j], eatingClockJohnDory, eatingTimeJohnDory, enemyLarge.maxFrameEat);
						if (skipMinnow)
							break;
					}
				}




				//FRENZY DECREASE
				frenzyTimeLimit = frenzyClock.getElapsedTime().asSeconds();
				if (frenzyTimeLimit > 2)
				{
					ateInLastSeconds = false;
				}
				frenzyTimeLoss = frenzyClockLoss.getElapsedTime().asMilliseconds();
				if (!ateInLastSeconds)
				{
					if (frenzyTimeLoss >= 350)
					{
						frenzyClockLoss.restart();
						if (frenzyRow > 0)
							frenzyRow--;

						if (frenzyRow == 0 && frenzyColumn != 0)
						{
							frenzyColumn--;
							if (frenzyColumn > 0)
								frenzyRow = 6;
							else
								frenzyRow = 0;
						}
						if (frenzyRow == 0 && frenzyColumn == 0)
						{
							frenzyColumn = 0;
							frenzyRow = 0;
						}
					}
				}
				//FRENZY UPDATE
				frenzySprite.setTextureRect(IntRect(frenzyColumn * 350, frenzyRow * 120, 350, 120));

				//Frenzy Multiplier
				if (frenzyColumn < 2 && frenzyRow < 6)
				{
					frenzyMultiplier.setString("1X");
					frenzyMultiplier.setFillColor(Color::White);
					frenzymulti = 1;
				}
				else if ((frenzyColumn == 1 && frenzyRow == 6) || (frenzyColumn == 2 && frenzyRow < 6))
				{
					frenzyMultiplier.setString("2X");
					frenzyMultiplier.setFillColor(Color::Blue);
					frenzymulti = 2;
				}
				else if (frenzyColumn == 2 && frenzyRow == 6)
				{
					frenzyMultiplier.setString("3X");
					frenzyMultiplier.setFillColor(Color::Red);
					frenzymulti = 3;
				}


				//Timer number update
				Timer.setString("00:" + to_string(30 - levelTwoTimer - timerBeforePause));

				//EatingNum update and timer
				if (eatingNum <= 30)
				{
					eatingNumText.setString(to_string(eatingNum) + " of 30 ");
				}
				if (!pausemenuisopen && !timeSaved)
				{
					if (levelTwoTimer >= 30 - timerBeforePause)
						deathStatus = true;
					else if (eatingNum >= 30)
					{
						levelnumber = 2;
						pagenumber = 9;
						gamemusic.pause();
						endgame(window, mousedownbuffer, mousedownsound, mouseoverbuffer, mouseoversound, introbuffer, introsound, stagebuffer, stagesound, music);
					}
				}
				else if (pausemenuisopen && !timeSaved)
				{
					timerBeforePause += levelTwoTimer;
					timeSaved = true;
				}
				else if (!pausemenuisopen && timeSaved)
				{
					levelTwoClock.restart().asSeconds();
					timeSaved = false;
				}

				//Score number update
				ScoreText.setString("" + to_string(leaderboardScore));

				//Redbar Levelup update
				if (BarRed.getSize().x < 694) {
					BarRed.setSize(Vector2f(player.score * 20, 11));
				}
				else
				{
					BarRed.setSize(Vector2f(694, 11));
					stagesound.play();
					if (!redBarMaxReached)
					{

						//High score override
						if (highScoreInFile < leaderboardScore)
						{
							highScoreInFile = leaderboardScore;
							ofHighScore.open("HighScore.txt", ios::out | ios::trunc);
							ofHighScore << leaderboardScore;
							ofHighScore.close();
						}
						levelnumber = 2;
						stagesound.play();
						gamemusic.stop();
						pagenumber = 9;
						endgame(window, mousedownbuffer, mousedownsound, mouseoverbuffer, mouseoversound, introbuffer, introsound, stagebuffer, stagesound, music);


					}
					redBarMaxReached = true;
				}

				//score = false;
				//Render draw
				window.clear();
				if (pagenumber != 6)
				{
					break;
				}
				window.draw(backgroundSprite);

				//Return To Menu to continue
				menu ok(window.getSize().x, window.getSize().y);
				ok.menuu[0].setString("Return To Menu");
				ok.menuu[2].setString("");
				ok.menuu[1].setString("");
				ok.menuu[3].setString("");
				ok.menuu[0].setFillColor(Color::Red);
				ok.menuu[0].setCharacterSize(120);
				ok.menuu[0].setPosition(Vector2f(470, 800));

				//Enemy draw
				for (int i = 0; i < Minnow.size(); i++)
				{
					window.draw(Minnow[i]);
				}
				for (int i = 0; i < Surgeonfish.size(); i++)
				{
					window.draw(Surgeonfish[i]);
				}
				for (int i = 0; i < JohnDory.size(); i++)
				{
					window.draw(JohnDory[i]);
				}

				//Scorebar, frenzy and player draw
				if (!deathStatus)
				{
					//Scorebar

					window.draw(ScoreBar);
					window.draw(ScoreText);

					window.draw(BarBlack);

					window.draw(clockbackground[0]);
					window.draw(clockbackground[1]);
					window.draw(eatingNumText);
					window.draw(clockTimer);
					window.draw(Timer);

					//Enemy sprite in scorebar
					window.draw(ScoreMinnow);
					window.draw(ScoreSurgeonfish);
					window.draw(ScoreJohnDory);
					if (istransparentFish[0])
						window.draw(transparentFish[0]);
					if (istransparentFish[1])
						window.draw(transparentFish[1]);

					//Chomp draw
					if (eating)
						window.draw(chompSprite);

					//Draw frenzy, it's multiplier and the score
					window.draw(frenzyMultiplier);
					window.draw(frenzySprite);

					//Player
					window.draw(player.sprite);
				}

				//draw background
				else
				{
					ok.draw(window);
					window.draw(GameOverBackground);
					window.draw(GameOver);
					//return to main menu after game over
					while (window.pollEvent(event))
					{
						if (event.type == Event::KeyReleased && event.key.code == Keyboard::Return)
						{
							mouseoversound.play();
							pagenumber = 0;
							windoww(window, mousedownbuffer, mousedownsound, mouseoverbuffer, mouseoversound, introbuffer, introsound, stagebuffer, stagesound, music);

						}
					}
					if (playDeathSound)
					{
						GameOverSound.play();
						playDeathSound = false;
						gamemusic.stop();


					}
					if (highScoreInFile < leaderboardScore)
					{
						highScoreInFile = leaderboardScore;
						ofHighScore.open("HighScore.txt", ios::out | ios::trunc);
						ofHighScore << leaderboardScore;
						ofHighScore.close();
					}
				}


				//when pause menu open
				if (pausemenuisopen)
				{
					window.setView(view);
					window.draw(pausemenusprite);
					pausemenu.draw(window);
				}

				window.display();
			}

			if (pausenumber == 0)
			{
				pausemenuisopen = false;

			}
			if (pagenumber == 100)
			{

				music.play();
				pagenumber = 0;
				pausemenuisopen = false;
				windoww(window, mousedownbuffer, mousedownsound, mouseoverbuffer, mouseoversound, introbuffer, introsound, stagebuffer, stagesound, music);
			}
			if (pausenumber == 2)
			{
				gamemusic.pause();
				window.close();
			}
		}
	}

}
void Level3(RenderWindow& window, SoundBuffer& mousedownbuffer, Sound& mousedownsound, SoundBuffer& mouseoverbuffer, Sound& mouseoversound, SoundBuffer& introbuffer, Sound& introsound, SoundBuffer& stagebuffer, Sound& stagesound, Music& music)
{

	levelnumber = 3;
	int eatingnum = 0;
	const unsigned WINDOW_WIDTH = 1920, WINDOW_HEIGHT = 1080;
	//RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Feeding Frenzy", Style::Fullscreen);

	leaderboardScore = 0;

	//Icon
	Image icon;
	icon.loadFromFile("Resources/Backgrounds/Icon.png");
	//windowGame.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());


	//Pause Menu
	menu pausemenu(window.getSize().x, window.getSize().y);
	pausemenu.menuu[0].setString("Resume");
	pausemenu.menuu[1].setString("Levels Menu");
	pausemenu.menuu[2].setString("Exit");
	pausemenu.menuu[3].setString(" ");

	bool pausemenuisopen = false;

	//pausemenu texture
	Texture pausemenutexture;
	pausemenutexture.loadFromFile("Resources/Backgrounds/pausemenu1.jpg");
	Sprite pausemenusprite;
	pausemenusprite.setTexture(pausemenutexture);

	//Game Over Texture
	Texture GameOvertexture;
	GameOvertexture.loadFromFile("Resources/Backgrounds/GameOver.png");
	Sprite GameOver;
	GameOver.setTexture(GameOvertexture);
	GameOver.setScale(1.8, 1.8);
	GameOver.setPosition(550, 200);
	RectangleShape GameOverBackground;
	GameOverBackground.setSize(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	GameOverBackground.setFillColor(Color(0, 0, 0, 100));

	//Background
	Texture backgroundTexture;
	backgroundTexture.loadFromFile("Resources/Backgrounds/Untitled-1.jpg");
	Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);
	Vector2u sizeBG = backgroundTexture.getSize();
	backgroundSprite.setOrigin(sizeBG.x / 2, sizeBG.y / 2);
	backgroundSprite.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);



	//score bar texture
	Texture scorebartexture;
	scorebartexture.loadFromFile("Resources/Backgrounds/Scorebar.jpeg");
	Sprite ScoreBar;
	ScoreBar.setTexture(scorebartexture);
	ScoreBar.setScale(1.5, 1);
	ScoreBar.setTextureRect(IntRect(0, 0, 1314, 135));

	//menu texture for Surgeonfish2
	Texture ScoreSurgeonfish2Texture;
	ScoreSurgeonfish2Texture.loadFromFile("Resources/Sprites/Angelfish_blue.png");
	Sprite ScoreSurgeonfish2;
	ScoreSurgeonfish2.setTexture(ScoreSurgeonfish2Texture);
	ScoreSurgeonfish2.setPosition(445, 20);
	ScoreSurgeonfish2.setScale(0.55, 0.55);
	ScoreSurgeonfish2.setTextureRect(IntRect(126, 0, -126, 106));

	//menu texture for John_Dory2
	Texture ScoreJohn_Dory2Texture;
	ScoreJohn_Dory2Texture.loadFromFile("Resources/Sprites/Surgeonfish_blue.png");
	Sprite ScoreJohn_Dory2fish;
	ScoreJohn_Dory2fish.setTexture(ScoreJohn_Dory2Texture);
	ScoreJohn_Dory2fish.setPosition(600, 5);
	ScoreJohn_Dory2fish.setScale(0.8, 0.8);
	ScoreJohn_Dory2fish.setTextureRect(IntRect(171, 0, -171, 106));

	//menu texture for bigEnemy
	Texture ScorebigEnemyTexture;
	ScorebigEnemyTexture.loadFromFile("Resources/Sprites/Layer_2.png");
	Sprite ScorebigEnemy;
	ScorebigEnemy.setTexture(ScorebigEnemyTexture);
	ScorebigEnemy.setPosition(850, 0);
	ScorebigEnemy.setScale(0.7, 0.7);
	ScorebigEnemy.setTextureRect(IntRect(251, 0, -251, 176));

	//transparent  fish
	Texture transparentFishtexture;
	transparentFishtexture.loadFromFile("Resources/Sprites/Ellipse_15.png");
	Sprite transparentFish[2];
	transparentFish[0].setTexture(transparentFishtexture);
	transparentFish[1].setTexture(transparentFishtexture);
	bool istransparentFish[2] = { true,true };
	transparentFish[0].setScale(0.9, 0.9);
	transparentFish[0].setPosition(580, -10);
	transparentFish[1].setPosition(817, -18);

	//default bar
	RectangleShape BarBlack;
	BarBlack.setSize(Vector2f(700, 15));
	BarBlack.setPosition(390, 93);
	BarBlack.setFillColor(Color::Black);

	//Levelup bar
	RectangleShape BarRed;
	BarRed.setSize(Vector2f(94, 11));
	BarRed.setPosition(393, 95);
	BarRed.setFillColor(Color::Red);

	CircleShape Triangle;
	Triangle.setRadius(18);
	Triangle.setPointCount(3);
	Triangle.setPosition(575, 99);
	Triangle.setFillColor(Color::Blue);

	CircleShape Triangle1;
	Triangle1.setRadius(18);
	Triangle1.setPointCount(3);
	Triangle1.setPosition(773, 99);
	Triangle1.setFillColor(Color::Blue);

	//Score number
	Font Scorefont;
	Scorefont.loadFromFile("Resources/Fonts/GUMDROP.ttf");
	Text ScoreText;
	ScoreText.setFont(Scorefont);
	ScoreText.setCharacterSize(40);
	ScoreText.setFillColor(Color::White);
	ScoreText.setPosition(1560, 20);


	//Clock, elapsed time, framerate independence
	Clock dt_clock, spawn_clock[3], movement_clock[3], animationClock;
	float dt;


	//Movement, spawn and random direction intialization
	float movementMultiplier = 60.f;
	float enemySpawnTimeElapsed[3];
	float enemyMovementTimeElapsed[3];
	int enemyDirectionRandomizer[3] = { 0, 0, 0 };


	//Animation initialization
	float animationTime = animationClock.getElapsedTime().asMilliseconds();
	float animationLoopTime[3] = { 60, 80, 100 };
	int currentFramePlayer = 0;
	int currentFrameEnemy[3] = { 0, 0, 0 };



	//FRENZY
	Texture frenzyTexture;
	frenzyTexture.loadFromFile("Resources/Sprites/FRENZY.png");
	Sprite frenzySprite;
	frenzySprite.setTexture(frenzyTexture);
	frenzySprite.setTextureRect(IntRect(0, 0, 350, 120));
	frenzySprite.setPosition(WINDOW_WIDTH / 2 - 175, WINDOW_HEIGHT / 2 - 360);
	Clock frenzyClock, frenzyClockLoss;
	float frenzyTimeLimit = frenzyClock.getElapsedTime().asSeconds(), frenzyTimeLoss;
	bool ateInLastSeconds = false;
	int frenzyColumn = 0, frenzyRow = 0;
	int frenzymulti = 1;

	//font multiplier
	Font frenzyMultiFont;
	frenzyMultiFont.loadFromFile("Resources/Fonts/Roboto-Black.ttf");
	Text frenzyMultiplier;
	frenzyMultiplier.setFont(frenzyMultiFont);
	frenzyMultiplier.setFillColor(Color::White);
	frenzyMultiplier.setOutlineColor(Color::Black);
	frenzyMultiplier.setOutlineThickness(3);
	frenzyMultiplier.setPosition(1760, 5);
	frenzyMultiplier.setCharacterSize(70);


	//chomp 
	Texture chompTexture;
	chompTexture.loadFromFile("Resources/Sprites/Chomp.png");
	Sprite chompSprite;
	chompSprite.setTexture(chompTexture);


	//Player
	Entity player = { 0, 2, 3, 14, 5, 0, 11.25f, 0.6f, 0.2f };
	player.texture.loadFromFile("Resources/Sprites/player3.png");
	player.sprite.setTexture(player.texture);
	player.sprite.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	player.sprite.setTextureRect(IntRect(201, 181, -201, 181));
	player.sprite.setScale(Vector2f(0.8, 0.8));
	bool deathStatus = false;
	int currentFrameIdle = 0, maxFrameIdle = 7;
	Clock idleClock;
	float idleTimer;
	bool eating = false;
	int currentFrameEating = 0;
	Clock eatingClock;
	float eatingTime = eatingClock.getElapsedTime().asMilliseconds();


	//Small enemies / Surgeonfish2
	Entity enemySmall = { 0, 2, 3, 14, 5, 0, 3.75f, 0.375f, 0.05f };
	enemySmall.texture.loadFromFile("Resources/Sprites/Angelfish_blue.png");
	enemySmall.sprite.setTexture(enemySmall.texture);
	enemySmall.sprite.setTextureRect(IntRect(126, 106, -126, 106));
	enemySmall.sprite.setScale(0.6, 0.6);
	vector <Sprite> Surgeonfish2;
	vector <Vector2f> Surgeonfish2_velocity;
	vector <Vector2f> Surgeonfish2_direction;
	vector <int> Surgeonfish2_directionRand;
	vector <int> Surgeonfish2_currentFrame;
	vector <Clock> Surgeonfish2_clock;
	vector <float> Surgeonfish2_time;
	bool eatingSurgeonfish2 = false;
	int currentFrameEatingSurgeonfish2 = 0;
	Clock eatingClockSurgeonfish2;
	float eatingTimeSurgeonfish2 = eatingClockSurgeonfish2.getElapsedTime().asMilliseconds();



	//Medium enemies / John_Dory2
	Entity enemyMedium = { 10, 1, 2, 13, 4, 5, 3.f, 0.3f, 0.16875f };
	enemyMedium.texture.loadFromFile("Resources/Sprites/Surgeonfish_blue.png");
	enemyMedium.sprite.setTexture(enemyMedium.texture);
	enemyMedium.sprite.setTextureRect(IntRect(171, 0, -171, 106));
	enemyMedium.sprite.setScale(1.1, 1.1);
	vector <Sprite> John_Dory2fish;
	vector <Vector2f> John_Dory2_velocity;
	vector <Vector2f> John_Dory2_direction;
	vector <int> John_Dory2_directionRand;
	vector <int> John_Dory2_currentFrame;
	vector <Clock> John_Dory2_clock;
	vector <float> John_Dory2_time;
	int John_Dory2SpawnTimer = 8;
	bool eatingJohn_Dory2 = false;
	int currentFrameEatingJohn_Dory2 = 0;
	Clock eatingClockJohn_Dory2;
	float eatingTimeJohn_Dory2 = eatingClockJohn_Dory2.getElapsedTime().asMilliseconds();



	//Large enemies / bigEnemy
	Entity enemyLarge = { 20, 1, 2, 14, 5, 5, 2.25f, 0.225f, 0.1875f };
	enemyLarge.texture.loadFromFile("Resources/Sprites/Layer_2.png");
	enemyLarge.sprite.setTexture(enemyLarge.texture);
	enemyLarge.sprite.setTextureRect(IntRect(251, 0, -251, 176));
	enemyLarge.sprite.setScale(1.4, 1.4);
	vector <Sprite> bigEnemy;
	vector <Vector2f> bigEnemy_velocity;
	vector <Vector2f> bigEnemy_direction;
	vector <int> bigEnemy_directionRand;
	vector <int> bigEnemy_currentFrame;
	vector <Clock> bigEnemy_clock;
	vector <float> bigEnemy_time;
	bool eatingbigEnemy = false;
	int currentFrameEatingbigEnemy = 0;
	Clock eatingClockbigEnemy;
	float eatingTimebigEnemy = eatingClockbigEnemy.getElapsedTime().asMilliseconds();
	int bigEnemySpawnTimer = 15, bigEnemySpawnQuantity = 2;


	//SOUNDS

	//minnowEating sound
	SoundBuffer eatingminnowbuffer;
	eatingminnowbuffer.loadFromFile("Resources/sounds/bite1.ogg");
	Sound eatingminnowsound;
	eatingminnowsound.setBuffer(eatingminnowbuffer);
	bool eatingminnowboolean = true;

	//surgeonEating sound
	SoundBuffer eatingsurgeonbuffer;
	eatingsurgeonbuffer.loadFromFile("Resources/sounds/bite2.ogg");
	Sound eatingsurgeonsound;
	eatingsurgeonsound.setBuffer(eatingsurgeonbuffer);
	bool eatingsurgeonboolean = true;

	//johndoryEating sound
	SoundBuffer eatingjohndorybuffer;
	eatingjohndorybuffer.loadFromFile("Resources/sounds/bite3.ogg");
	Sound eatingjohndorysound;
	eatingjohndorysound.setBuffer(eatingjohndorybuffer);
	bool eatingjohndoryboolean = true;

	//SoundBuffer GameOver
	SoundBuffer GameOverSoundbuffer;
	GameOverSoundbuffer.loadFromFile("Resources/sounds/GameOver.ogg");
	Sound GameOverSound;
	GameOverSound.setBuffer(GameOverSoundbuffer);
	bool playDeathSound = true;

	//gamemusic
	Music gamemusic;
	gamemusic.openFromFile("Resources/music/level3music.ogg");
	gamemusic.play();

	//frenzy sound
	SoundBuffer Feedingfrenysoundbuffer;
	Feedingfrenysoundbuffer.loadFromFile("Resources/sounds/feedingFrenzy.ogg");
	Sound Feedingfrenysound;
	Feedingfrenysound.setBuffer(Feedingfrenysoundbuffer);


	//doublefrenzy sound
	SoundBuffer doublefrenzysoundbuffer;
	doublefrenzysoundbuffer.loadFromFile("Resources/sounds/doubleFrenzy.ogg");
	Sound doublefrenzysound;
	doublefrenzysound.setBuffer(doublefrenzysoundbuffer);

	//growth sound
	SoundBuffer Growthsoundbuffer;
	Growthsoundbuffer.loadFromFile("Resources/sounds/playerGrow.ogg");
	Sound Growthsound;
	Growthsound.setBuffer(Growthsoundbuffer);
	bool Growthsoundboolean = true;

	//eatgulp sound
	SoundBuffer eatgulpsoundbuffer;
	eatgulpsoundbuffer.loadFromFile("Resources/sounds/eatGulp.ogg");
	Sound eatgulpsound;
	eatgulpsound.setBuffer(eatgulpsoundbuffer);



	//view camera pausemenu
	View view(FloatRect(0, 0, 1000, 1000));
	View view1(FloatRect(0, 0, 1920, 1080));
	pausemenu.menuu[0].setCharacterSize(70);
	pausemenu.menuu[1].setCharacterSize(65);
	pausemenu.menuu[2].setCharacterSize(70);
	pausemenu.menuu[0].setPosition(Vector2f(400, 430));
	pausemenu.menuu[1].setPosition(Vector2f(350, 550));
	pausemenu.menuu[2].setPosition(Vector2f(420, 670));


	//Keeping the highest score
	ofstream ofHighScore;
	ifstream ifHighScore;

	ifHighScore.open("HighScore.txt", ios::in);

	ifHighScore >> highScoreInFile;
	ifHighScore.close();

	bool redBarMaxReached = false;


	while (true)
	{
		if (pagenumber == 7)
		{
			while (window.isOpen())
			{
				window.setView(view1);

				//Exiting
				Event event;
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed)
						window.close();
					if (event.type == Event::KeyPressed)
					{
						if (event.key.code == Keyboard::Escape)
						{
							if (pausemenuisopen)
								mouseoversound.play();
							pausemenuisopen = true;
						}
						if (event.key.code == Keyboard::Up)
						{
							if (pausemenuisopen)
								mousedownsound.play();
							pausemenu.pausemoveup();
						}
						if (event.key.code == Keyboard::Down)
						{
							if (pausemenuisopen)
							mousedownsound.play();
							pausemenu.pausemovedown();
						}
						if (event.key.code == Keyboard::Return)
						{
							mouseoversound.play();

							if (pausemenu.getselecteditem() == 0)
							{
								pausenumber = 0;
								pausemenuisopen = false;
							}
							if (pausemenu.getselecteditem() == 1)
							{

								gamemusic.pause();
								pagenumber = 0;
							}
							if (pausemenu.getselecteditem() == 2)
							{

								pagenumber = 2;

							}
						}


					}

				}


				//Time between frames
				dt = dt_clock.restart().asSeconds();




				//Player's movement, collision with screen
				if (!pausemenuisopen)
				{
					playerMovement(player.velocity, player.direction, dt, player.maxVel, player.accel, player.resist, movementMultiplier);
					player.sprite.move(player.velocity.x * dt * movementMultiplier, player.velocity.y * dt * movementMultiplier);
				}
				playerScreenCollision(player.sprite, WINDOW_WIDTH, WINDOW_HEIGHT);

				//Player's animation
				if (!eating)
					animation(player.sprite, currentFramePlayer, player.rowMotion, player.maxFrameMotion, player.velocity,
						player.direction, animationClock, animationTime);

				//Player's idle animation
				if (player.velocity.x == 0 && player.velocity.y == 0)
				{
					idleTimer = idleClock.getElapsedTime().asMilliseconds();
					if (idleTimer >= 120)
					{
						if (player.direction.x >= 0)
						{
							player.sprite.setTextureRect(IntRect(currentFrameIdle * 201 + 201, 181, -201, 181));
							currentFrameIdle++;
							idleClock.restart();
						}
						else if (player.direction.x < 0)
						{
							player.sprite.setTextureRect(IntRect(currentFrameIdle * 201, 181, 201, 181));
							currentFrameIdle++;
							idleClock.restart();
						}
						if (currentFrameIdle >= maxFrameIdle)
							currentFrameIdle = 0;
					}
				}

				//Player levelup
				if (player.score >= enemyMedium.score && player.score < enemyLarge.score)
				{
					player.sprite.setScale(1.1, 1.1);
					istransparentFish[0] = false;
					if (Growthsoundboolean) {
						Growthsound.play();
						Growthsoundboolean = false;
					}
				}
				if (player.score >= enemyLarge.score)
				{
					player.sprite.setScale(1.6, 1.6);
					istransparentFish[1] = false;
					if (!Growthsoundboolean) {
						Growthsound.play();
						Growthsoundboolean = true;
					}
				}

				if (player.score >= enemyMedium.score)
				{
					John_Dory2SpawnTimer = 5;
					bigEnemySpawnTimer = 12;
					bigEnemySpawnQuantity = 3;
				}
				if (player.score >= enemyLarge.score)
				{
					bigEnemySpawnTimer = 8;
					bigEnemySpawnQuantity = 4;
				}

				//Enemy spawn
				if (!pausemenuisopen)
				{
					//Spawn timer
					for (int i = 0; i < 3; i++)
					{
						enemySpawnTimeElapsed[i] = spawn_clock[i].getElapsedTime().asSeconds();
					}
					//Minnow or small
					if (Surgeonfish2.size() <= 16)
					{
						if (enemySpawnTimeElapsed[0] >= 0.5)
						{
							int side = rand() % 2;
							if (side == 0)
								enemySmall.sprite.setPosition(0 - enemySmall.sprite.getGlobalBounds().width, rand() % (WINDOW_HEIGHT - 135) + 135);
							else
								enemySmall.sprite.setPosition(WINDOW_WIDTH, rand() % (WINDOW_HEIGHT - 135) + 135);

							Surgeonfish2.push_back(enemySmall.sprite);
							Surgeonfish2_velocity.push_back(enemySmall.velocity);
							Surgeonfish2_direction.push_back(enemySmall.direction);
							Surgeonfish2_directionRand.push_back(enemyDirectionRandomizer[0]);
							Surgeonfish2_currentFrame.push_back(currentFrameEnemy[0]);
							Surgeonfish2_clock.push_back(animationClock);
							Surgeonfish2_time.push_back(animationTime);

							enemySpawnTimeElapsed[0] = spawn_clock[0].restart().asSeconds();
						}
					}
					//Surgeonfish or medium
					if (John_Dory2fish.size() <= 12)
					{
						if (enemySpawnTimeElapsed[1] >= John_Dory2SpawnTimer)
						{
							int side = rand() % 2;
							if (side == 0)
								enemyMedium.sprite.setPosition(0 - enemyMedium.sprite.getGlobalBounds().width, rand() % (WINDOW_HEIGHT - 135) + 135);
							else
								enemyMedium.sprite.setPosition(WINDOW_WIDTH, rand() % (WINDOW_HEIGHT - 135) + 135);

							John_Dory2fish.push_back(enemyMedium.sprite);
							John_Dory2_velocity.push_back(enemyMedium.velocity);
							John_Dory2_direction.push_back(enemyMedium.direction);
							John_Dory2_directionRand.push_back(enemyDirectionRandomizer[1]);
							John_Dory2_currentFrame.push_back(currentFrameEnemy[1]);
							John_Dory2_clock.push_back(animationClock);
							John_Dory2_time.push_back(animationTime);

							enemySpawnTimeElapsed[1] = spawn_clock[1].restart().asSeconds();
						}
					}
					// John Dory or large
					if (bigEnemy.size() <= bigEnemySpawnQuantity)
					{
						if (enemySpawnTimeElapsed[2] >= bigEnemySpawnTimer)
						{
							int side = rand() % 2;
							if (side == 0)
								enemyLarge.sprite.setPosition(0 - enemyLarge.sprite.getGlobalBounds().width, rand() % (WINDOW_HEIGHT - 135) + 135);
							else
								enemyLarge.sprite.setPosition(WINDOW_WIDTH, rand() % (WINDOW_HEIGHT - 135) + 135);

							bigEnemy.push_back(enemyLarge.sprite);
							bigEnemy_velocity.push_back(enemyLarge.velocity);
							bigEnemy_direction.push_back(enemyLarge.direction);
							bigEnemy_directionRand.push_back(enemyDirectionRandomizer[2]);
							bigEnemy_currentFrame.push_back(currentFrameEnemy[2]);
							bigEnemy_clock.push_back(animationClock);
							bigEnemy_time.push_back(animationTime);

							enemySpawnTimeElapsed[2] = spawn_clock[2].restart().asSeconds();
						}
					}

					//Direction Randomizer
					for (int i = 0; i < 3; i++)
					{
						enemyMovementTimeElapsed[i] = movement_clock[i].getElapsedTime().asSeconds();
						if (enemyMovementTimeElapsed[i] >= 1)
						{
							if (i == 0)
							{
								for (int j = 0; j < Surgeonfish2.size(); j++)
								{
									Surgeonfish2_directionRand[j] = rand() % 8;
								}
							}
							if (i == 1)
							{
								for (int j = 0; j < John_Dory2fish.size(); j++)
								{
									John_Dory2_directionRand[j] = rand() % 8;
								}
							}
							if (i == 2)
							{
								for (int j = 0; j < bigEnemy.size(); j++)
								{
									bigEnemy_directionRand[j] = rand() % 8;
								}
							}
							enemyMovementTimeElapsed[i] = 0;
							movement_clock[i].restart();
						}
					}

					// enemy movement, behaviour, collision
					for (int i = 0; i < Surgeonfish2.size(); i++)
					{
						enemyMovement(Surgeonfish2_velocity[i], Surgeonfish2_direction[i], Surgeonfish2_directionRand[i], dt,
							enemySmall.maxVel, enemySmall.accel, enemySmall.resist, movementMultiplier, Surgeonfish2[i]); //DOESN'T MOVE IF THIS IS COMMENTED

						enemyBehavior(player.sprite, Surgeonfish2[i], Surgeonfish2_velocity[i], Surgeonfish2_direction[i], dt,
							enemySmall.maxVel, enemySmall.accel, enemySmall.resist, movementMultiplier);
						Surgeonfish2[i].move(Surgeonfish2_velocity[i].x * dt * movementMultiplier, Surgeonfish2_velocity[i].y * dt * movementMultiplier);

						animation(Surgeonfish2[i], Surgeonfish2_currentFrame[i], enemySmall.rowMotion, enemySmall.maxFrameMotion, Surgeonfish2_velocity[i],
							Surgeonfish2_direction[i], Surgeonfish2_clock[i], Surgeonfish2_time[i], animationLoopTime[0]);

						playerAndEnemyCollision(player.sprite, Surgeonfish2[i], player.score, enemySmall.score, deathStatus, i, Surgeonfish2, Surgeonfish2_velocity,
							Surgeonfish2_direction, Surgeonfish2_directionRand, Surgeonfish2_currentFrame, Surgeonfish2_clock, Surgeonfish2_time, eating, currentFrameEating, player.direction,
							eatingClock, eatingTime, eatingminnowsound, frenzyRow, frenzyColumn, ateInLastSeconds, frenzyClock,
							Feedingfrenysound, doublefrenzysound, eatgulpsound, leaderboardScore, frenzymulti, chompSprite, eatingnum);
					}
					for (int i = 0; i < John_Dory2fish.size(); i++)
					{
						enemyMovement(John_Dory2_velocity[i], John_Dory2_direction[i], John_Dory2_directionRand[i], dt,
							enemySmall.maxVel, enemySmall.accel, enemySmall.resist, movementMultiplier, John_Dory2fish[i]);
						if (player.score >= enemyMedium.score)
						{
							enemyBehavior(player.sprite, John_Dory2fish[i], John_Dory2_velocity[i], John_Dory2_direction[i], dt,
								enemyMedium.maxVel, enemyMedium.accel, enemyMedium.resist, movementMultiplier);
						}
						John_Dory2fish[i].move(John_Dory2_velocity[i].x * dt * movementMultiplier, John_Dory2_velocity[i].y * dt * movementMultiplier);
						if (!eatingJohn_Dory2)
							animation(John_Dory2fish[i], John_Dory2_currentFrame[i], enemyMedium.rowMotion, enemyMedium.maxFrameMotion, John_Dory2_velocity[i], John_Dory2_direction[i], John_Dory2_clock[i], John_Dory2_time[i], animationLoopTime[1]);

						playerAndEnemyCollision(player.sprite, John_Dory2fish[i], player.score, enemyMedium.score, deathStatus, i, John_Dory2fish, John_Dory2_velocity,
							John_Dory2_direction, John_Dory2_directionRand, John_Dory2_currentFrame, John_Dory2_clock, John_Dory2_time, eating, currentFrameEating, player.direction,
							eatingClock, eatingTime, eatingsurgeonsound, frenzyRow, frenzyColumn, ateInLastSeconds,
							frenzyClock, Feedingfrenysound, doublefrenzysound, eatgulpsound, leaderboardScore, frenzymulti, chompSprite, eatingnum);
					}
					for (int i = 0; i < bigEnemy.size(); i++)
					{
						enemyMovement(bigEnemy_velocity[i], bigEnemy_direction[i], bigEnemy_directionRand[i], dt,
							enemySmall.maxVel, enemySmall.accel, enemySmall.resist, movementMultiplier, bigEnemy[i]);
						if (player.score >= enemyLarge.score)
						{
							enemyBehavior(player.sprite, bigEnemy[i], bigEnemy_velocity[i], bigEnemy_direction[i], dt,
								enemyLarge.maxVel, enemyLarge.accel, enemyLarge.resist, movementMultiplier);
						}
						bigEnemy[i].move(bigEnemy_velocity[i].x * dt * movementMultiplier, bigEnemy_velocity[i].y * dt * movementMultiplier);

						if (!eatingbigEnemy)
							animation(bigEnemy[i], bigEnemy_currentFrame[i], enemyLarge.rowMotion, enemyLarge.maxFrameMotion, bigEnemy_velocity[i], bigEnemy_direction[i], bigEnemy_clock[i], bigEnemy_time[i], animationLoopTime[2]);

						playerAndEnemyCollision(player.sprite, bigEnemy[i], player.score, enemyLarge.score, deathStatus, i, bigEnemy, bigEnemy_velocity,
							bigEnemy_direction, bigEnemy_directionRand, bigEnemy_currentFrame, bigEnemy_clock, bigEnemy_time, eating, currentFrameEating, player.direction,
							eatingClock, eatingTime, eatingjohndorysound, frenzyRow, frenzyColumn, ateInLastSeconds,
							frenzyClock, Feedingfrenysound, doublefrenzysound, eatgulpsound, leaderboardScore, frenzymulti, chompSprite, eatingnum);
					}
				}

				//Enemy and enemy collision
				bool skipMinnow = false;
				for (int i = 0; i < Surgeonfish2.size(); i++)
				{
					//Minnow and Surgeonfish
					for (int j = 0; j < John_Dory2fish.size(); j++)
					{
						enemyAndEnemyCollision(Surgeonfish2[i], John_Dory2fish[j], enemySmall.score, enemyMedium.score, i, j, Surgeonfish2, John_Dory2fish, Surgeonfish2_velocity, John_Dory2_velocity,
							Surgeonfish2_direction, John_Dory2_direction, Surgeonfish2_directionRand, John_Dory2_directionRand, Surgeonfish2_currentFrame, John_Dory2_currentFrame,
							Surgeonfish2_clock, John_Dory2_clock, Surgeonfish2_time, John_Dory2_time, skipMinnow,
							eatingSurgeonfish2, currentFrameEatingSurgeonfish2, Surgeonfish2_direction[i], eatingClockSurgeonfish2, eatingTimeSurgeonfish2, 0,
							eatingJohn_Dory2, currentFrameEatingJohn_Dory2, John_Dory2_direction[j], eatingClockJohn_Dory2, eatingTimeJohn_Dory2, enemyMedium.maxFrameEat);
						if (skipMinnow)
							break;

						//Surgeonfish and JohnDory
						bool skipSurgeon = false;
						for (int k = 0; k < bigEnemy.size(); k++)
						{
							enemyAndEnemyCollision(John_Dory2fish[j], bigEnemy[k], enemyMedium.score, enemyLarge.score, j, k, John_Dory2fish, bigEnemy, John_Dory2_velocity, bigEnemy_velocity,
								John_Dory2_direction, bigEnemy_direction, John_Dory2_directionRand, bigEnemy_directionRand, John_Dory2_currentFrame, bigEnemy_currentFrame,
								John_Dory2_clock, bigEnemy_clock, John_Dory2_time, bigEnemy_time, skipSurgeon,
								eatingJohn_Dory2, currentFrameEatingJohn_Dory2, John_Dory2_direction[j], eatingClockJohn_Dory2, eatingTimeJohn_Dory2, enemyMedium.maxFrameEat,
								eatingbigEnemy, currentFrameEatingbigEnemy, bigEnemy_direction[k], eatingClockbigEnemy, eatingTimebigEnemy, enemyLarge.maxFrameEat);
							if (skipSurgeon)
								break;
						}
					}
					// Minnow and John Dory
					for (int j = 0; j < bigEnemy.size(); j++)
					{
						if (skipMinnow)
							break;
						enemyAndEnemyCollision(Surgeonfish2[i], bigEnemy[j], enemySmall.score, enemyLarge.score, i, j, Surgeonfish2, bigEnemy, Surgeonfish2_velocity, bigEnemy_velocity,
							Surgeonfish2_direction, bigEnemy_direction, Surgeonfish2_directionRand, bigEnemy_directionRand, Surgeonfish2_currentFrame, bigEnemy_currentFrame,
							Surgeonfish2_clock, bigEnemy_clock, Surgeonfish2_time, bigEnemy_time, skipMinnow,
							eatingSurgeonfish2, currentFrameEatingSurgeonfish2, Surgeonfish2_direction[i], eatingClockSurgeonfish2, eatingTimeSurgeonfish2, 0,
							eatingbigEnemy, currentFrameEatingbigEnemy, bigEnemy_direction[j], eatingClockbigEnemy, eatingTimebigEnemy, enemyLarge.maxFrameEat);
						if (skipMinnow)
							break;
					}
				}




				//FRENZY DECREASE
				frenzyTimeLimit = frenzyClock.getElapsedTime().asSeconds();
				if (frenzyTimeLimit > 2)
				{
					ateInLastSeconds = false;
				}
				frenzyTimeLoss = frenzyClockLoss.getElapsedTime().asMilliseconds();
				if (!ateInLastSeconds)
				{
					if (frenzyTimeLoss >= 350)
					{
						frenzyClockLoss.restart();
						if (frenzyRow > 0)
							frenzyRow--;

						if (frenzyRow == 0 && frenzyColumn != 0)
						{
							frenzyColumn--;
							if (frenzyColumn > 0)
								frenzyRow = 6;
							else
								frenzyRow = 0;
						}
						if (frenzyRow == 0 && frenzyColumn == 0)
						{
							frenzyColumn = 0;
							frenzyRow = 0;
						}
					}
				}
				//FRENZY UPDATE
				frenzySprite.setTextureRect(IntRect(frenzyColumn * 350, frenzyRow * 120, 350, 120));

				//Frenzy Multiplier
				if (frenzyColumn < 2 && frenzyRow < 6)
				{
					frenzyMultiplier.setString("1X");
					frenzyMultiplier.setFillColor(Color::White);
					frenzymulti = 1;
				}
				else if ((frenzyColumn == 1 && frenzyRow == 6) || (frenzyColumn == 2 && frenzyRow < 6))
				{
					frenzyMultiplier.setString("2X");
					frenzyMultiplier.setFillColor(Color::Blue);
					frenzymulti = 2;
				}
				else if (frenzyColumn == 2 && frenzyRow == 6)
				{
					frenzyMultiplier.setString("3X");
					frenzyMultiplier.setFillColor(Color::Red);
					frenzymulti = 3;
				}

				//Score number update
				ScoreText.setString("" + to_string(leaderboardScore));

				//Redbar Levelup update
				if (BarRed.getSize().x < 694) {
					BarRed.setSize(Vector2f(player.score * 20, 11));
				}
				else
				{
					BarRed.setSize(Vector2f(694, 11));

					if (!redBarMaxReached)
					{
						stagesound.play();

						//High score override
						if (highScoreInFile < leaderboardScore)
						{
							highScoreInFile = leaderboardScore;
							ofHighScore.open("HighScore.txt", ios::out | ios::trunc);
							ofHighScore << leaderboardScore;
							ofHighScore.close();
						}
						levelnumber = 3;
						gamemusic.stop();
						pagenumber = 9;
						endgame(window, mousedownbuffer, mousedownsound, mouseoverbuffer, mouseoversound, introbuffer, introsound, stagebuffer, stagesound, music);


					}
					redBarMaxReached = true;
				}

				//score = false;
				//Render draw
				window.clear();
				if (pagenumber != 7)
				{
					break;
				}
				window.draw(backgroundSprite);

				//Return To Menu to continue
				menu ok(window.getSize().x, window.getSize().y);
				ok.menuu[0].setString("Return To Menu");
				ok.menuu[2].setString("");
				ok.menuu[1].setString("");
				ok.menuu[0].setFillColor(Color::Red);
				ok.menuu[0].setCharacterSize(120);
				ok.menuu[0].setPosition(Vector2f(470, 800));

				//Enemy draw
				for (int i = 0; i < Surgeonfish2.size(); i++)
				{
					window.draw(Surgeonfish2[i]);
				}
				for (int i = 0; i < John_Dory2fish.size(); i++)
				{
					window.draw(John_Dory2fish[i]);
				}
				for (int i = 0; i < bigEnemy.size(); i++)
				{
					window.draw(bigEnemy[i]);
				}

				//Scorebar, frenzy and player draw
				if (!deathStatus)
				{
					//Scorebar
					window.draw(ScoreBar);
					window.draw(BarBlack);
					window.draw(BarRed);
					window.draw(Triangle);
					window.draw(Triangle1);

					//Enemy sprite in scorebar
					window.draw(ScoreSurgeonfish2);
					window.draw(ScoreJohn_Dory2fish);
					window.draw(ScorebigEnemy);
					if (istransparentFish[0])
						window.draw(transparentFish[0]);
					if (istransparentFish[1])
						window.draw(transparentFish[1]);

					//Chomp draw
					if (eating)
						window.draw(chompSprite);

					//Draw frenzy, it's multiplier and the score
					window.draw(frenzyMultiplier);
					window.draw(ScoreText);
					window.draw(frenzySprite);

					//Player
					window.draw(player.sprite);
				}

				//draw background
				else
				{
					ok.draw(window);
					window.draw(GameOverBackground);
					window.draw(GameOver);
					Event event2;
					//return to main menu after game over
					while (window.pollEvent(event2))
					{

						if (event2.type == Event::KeyReleased)
						{
							if (event2.key.code == Keyboard::Return)
							{
								mouseoversound.play();

								pagenumber = 15;

							}
						}
					}
					if (playDeathSound)
					{
						GameOverSound.play();
						playDeathSound = false;
						gamemusic.stop();

					}
					if (highScoreInFile < leaderboardScore)
					{
						highScoreInFile = leaderboardScore;
						ofHighScore.open("HighScore.txt", ios::out | ios::trunc);
						ofHighScore << leaderboardScore;
						ofHighScore.close();
					}
				}

				//when pause menu open
				if (pausemenuisopen)
				{
					window.setView(view);
					window.draw(pausemenusprite);
					pausemenu.draw(window);
				}


				window.display();
			}

			if (pausenumber == 0)
			{
				pausemenuisopen = false;


			}
			if (pagenumber == 0)
			{
				music.play();
				windoww(window, mousedownbuffer, mousedownsound, mouseoverbuffer, mouseoversound, introbuffer, introsound, stagebuffer, stagesound, music);
			}
			if (pagenumber == 2)
			{
				gamemusic.pause();
				window.close();
			}
			if (pagenumber == 15)
			{
				pagenumber = 0;
				windoww(window, mousedownbuffer, mousedownsound, mouseoverbuffer, mouseoversound, introbuffer, introsound, stagebuffer, stagesound, music);
			}
		}
	}
}
void Level4(RenderWindow& window, SoundBuffer& mousedownbuffer, Sound& mousedownsound, SoundBuffer& mouseoverbuffer, Sound& mouseoversound, SoundBuffer& introbuffer, Sound& introsound, SoundBuffer& stagebuffer, Sound& stagesound, Music& music)
{
	levelnumber = 3;
	int eatingnum = 0;
	const unsigned WINDOW_WIDTH = 1920, WINDOW_HEIGHT = 1080;
	//RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Feeding Frenzy", Style::Fullscreen);

	leaderboardScore = 0;

	//Icon
	Image icon;
	icon.loadFromFile("Resources/Backgrounds/Icon.png");
	//windowGame.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());


	//Pause Menu
	menu pausemenu(window.getSize().x, window.getSize().y);
	pausemenu.menuu[0].setString("Resume");
	pausemenu.menuu[1].setString("Levels Menu");
	pausemenu.menuu[2].setString("Exit");
	bool pausemenuisopen = false;

	//pausemenu texture
	Texture pausemenutexture;
	pausemenutexture.loadFromFile("Resources/Backgrounds/pausemenu1.jpg");
	Sprite pausemenusprite;
	pausemenusprite.setTexture(pausemenutexture);

	//Game Over Texture
	Texture GameOvertexture;
	GameOvertexture.loadFromFile("Resources/Backgrounds/GameOver.png");
	Sprite GameOver;
	GameOver.setTexture(GameOvertexture);
	GameOver.setScale(1.8, 1.8);
	GameOver.setPosition(550, 200);
	RectangleShape GameOverBackground;
	GameOverBackground.setSize(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	GameOverBackground.setFillColor(Color(0, 0, 0, 100));

	//Background
	Texture backgroundTexture;
	backgroundTexture.loadFromFile("Resources/Backgrounds/background2.jpg");
	Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);
	Vector2u sizeBG = backgroundTexture.getSize();
	backgroundSprite.setOrigin(sizeBG.x / 2, sizeBG.y / 2);
	backgroundSprite.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);




	//score bar texture
	Texture scorebartexture;
	scorebartexture.loadFromFile("Resources/Backgrounds/Scorebar.jpeg");
	Sprite ScoreBar;
	ScoreBar.setTexture(scorebartexture);
	ScoreBar.setScale(1.5, 1);
	ScoreBar.setTextureRect(IntRect(0, 0, 1314, 135));

	//menu texture for Surgeonfish2
	Texture ScoreSurgeonfish2Texture;
	ScoreSurgeonfish2Texture.loadFromFile("Resources/Sprites/Surgeonfish2.png");
	Sprite ScoreSurgeonfish2;
	ScoreSurgeonfish2.setTexture(ScoreSurgeonfish2Texture);
	ScoreSurgeonfish2.setPosition(430, 20);
	ScoreSurgeonfish2.setScale(0.6, 0.6);
	ScoreSurgeonfish2.setTextureRect(IntRect(171, 0, -171, 106));

	//menu texture for John_Dory2
	Texture ScoreJohn_Dory2Texture;
	ScoreJohn_Dory2Texture.loadFromFile("Resources/Sprites/John_Dory2.png");
	Sprite ScoreJohn_Dory2fish;
	ScoreJohn_Dory2fish.setTexture(ScoreJohn_Dory2Texture);
	ScoreJohn_Dory2fish.setPosition(620, -25);
	ScoreJohn_Dory2fish.setScale(0.7, 0.7);
	ScoreJohn_Dory2fish.setTextureRect(IntRect(181, 0, -181, 181));

	//menu texture for bigEnemy
	Texture ScorebigEnemyTexture;
	ScorebigEnemyTexture.loadFromFile("Resources/Sprites/bigEnemy.png");
	Sprite ScorebigEnemy;
	ScorebigEnemy.setTexture(ScorebigEnemyTexture);
	ScorebigEnemy.setPosition(840, 5);
	ScorebigEnemy.setScale(0.6, 0.6);
	ScorebigEnemy.setTextureRect(IntRect(271, 0, -271, 121));

	//transparent  fish
	Texture transparentFishtexture;
	transparentFishtexture.loadFromFile("Resources/Sprites/Ellipse_15.png");
	Sprite transparentFish[2];
	transparentFish[0].setTexture(transparentFishtexture);
	transparentFish[1].setTexture(transparentFishtexture);
	bool istransparentFish[2] = { true,true };
	transparentFish[0].setScale(0.9, 0.9);
	transparentFish[0].setPosition(580, -10);
	transparentFish[1].setPosition(817, -18);

	//default bar
	RectangleShape BarBlack;
	BarBlack.setSize(Vector2f(700, 15));
	BarBlack.setPosition(390, 93);
	BarBlack.setFillColor(Color::Black);

	//Levelup bar
	RectangleShape BarRed;
	BarRed.setSize(Vector2f(94, 11));
	BarRed.setPosition(393, 95);
	BarRed.setFillColor(Color::Red);

	CircleShape Triangle;
	Triangle.setRadius(18);
	Triangle.setPointCount(3);
	Triangle.setPosition(575, 99);
	Triangle.setFillColor(Color::Blue);

	CircleShape Triangle1;
	Triangle1.setRadius(18);
	Triangle1.setPointCount(3);
	Triangle1.setPosition(773, 99);
	Triangle1.setFillColor(Color::Blue);

	//Score number
	Font Scorefont;
	Scorefont.loadFromFile("Resources/Fonts/GUMDROP.ttf");
	Text ScoreText;
	ScoreText.setFont(Scorefont);
	ScoreText.setCharacterSize(40);
	ScoreText.setFillColor(Color::White);
	ScoreText.setPosition(1560, 20);


	//Clock, elapsed time, framerate independence
	Clock dt_clock, spawn_clock[3], movement_clock[3], animationClock;
	float dt;


	//Movement, spawn and random direction intialization
	float movementMultiplier = 60.f;
	float enemySpawnTimeElapsed[3];
	float enemyMovementTimeElapsed[3];
	int enemyDirectionRandomizer[3] = { 0, 0, 0 };


	//Animation initialization
	float animationTime = animationClock.getElapsedTime().asMilliseconds();
	float animationLoopTime[3] = { 60, 80, 100 };
	int currentFramePlayer = 0;
	int currentFrameEnemy[3] = { 0, 0, 0 };




	//FRENZY
	Texture frenzyTexture;
	frenzyTexture.loadFromFile("Resources/Sprites/FRENZY.png");
	Sprite frenzySprite;
	frenzySprite.setTexture(frenzyTexture);
	frenzySprite.setTextureRect(IntRect(0, 0, 350, 120));
	frenzySprite.setPosition(WINDOW_WIDTH / 2 - 175, WINDOW_HEIGHT / 2 - 360);
	Clock frenzyClock, frenzyClockLoss;
	float frenzyTimeLimit = frenzyClock.getElapsedTime().asSeconds(), frenzyTimeLoss;
	bool ateInLastSeconds = false;
	int frenzyColumn = 0, frenzyRow = 0;
	int frenzymulti = 1;

	//font multiplier
	Font frenzyMultiFont;
	frenzyMultiFont.loadFromFile("Resources/Fonts/Roboto-Black.ttf");
	Text frenzyMultiplier;
	frenzyMultiplier.setFont(frenzyMultiFont);
	frenzyMultiplier.setFillColor(Color::White);
	frenzyMultiplier.setOutlineColor(Color::Black);
	frenzyMultiplier.setOutlineThickness(3);
	frenzyMultiplier.setPosition(1760, 5);
	frenzyMultiplier.setCharacterSize(70);


	//chomp 
	Texture chompTexture;
	chompTexture.loadFromFile("Resources/Sprites/Chomp.png");
	Sprite chompSprite;
	chompSprite.setTexture(chompTexture);


	//Player
	Entity player = { 0, 2, 3, 14, 5, 0, 11.25f, 0.6f, 0.2f };
	player.texture.loadFromFile("Resources/Sprites/player2.png");
	player.sprite.setTexture(player.texture);
	player.sprite.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	player.sprite.setTextureRect(IntRect(201, 181, -201, 181));
	player.sprite.setScale(Vector2f(0.8, 0.8));
	bool deathStatus = false;
	int currentFrameIdle = 0, maxFrameIdle = 7;
	Clock idleClock;
	float idleTimer;
	bool eating = false;
	int currentFrameEating = 0;
	Clock eatingClock;
	float eatingTime = eatingClock.getElapsedTime().asMilliseconds();

	//Small enemies / Surgeonfish2
	Entity enemySmall = { 0, 1, 2, 13, 5, 0, 3.75f, 0.375f, 0.05f };
	enemySmall.texture.loadFromFile("Resources/Sprites/Surgeonfish2.png");
	enemySmall.sprite.setTexture(enemySmall.texture);
	enemySmall.sprite.setTextureRect(IntRect(171, 0, -171, 106));
	enemySmall.sprite.setScale(0.6, 0.6);
	vector <Sprite> Surgeonfish2;
	vector <Vector2f> Surgeonfish2_velocity;
	vector <Vector2f> Surgeonfish2_direction;
	vector <int> Surgeonfish2_directionRand;
	vector <int> Surgeonfish2_currentFrame;
	vector <Clock> Surgeonfish2_clock;
	vector <float> Surgeonfish2_time;
	bool eatingSurgeonfish2 = false;
	int currentFrameEatingSurgeonfish2 = 0;
	Clock eatingClockSurgeonfish2;
	float eatingTimeSurgeonfish2 = eatingClockSurgeonfish2.getElapsedTime().asMilliseconds();



	//Medium enemies / John_Dory2
	Entity enemyMedium = { 10, 1, 2, 14, 5, 6, 3.f, 0.3f, 0.16875f };
	enemyMedium.texture.loadFromFile("Resources/Sprites/John_Dory2.png");
	enemyMedium.sprite.setTexture(enemyMedium.texture);
	enemyMedium.sprite.setTextureRect(IntRect(181, 0, -181, 181));
	enemyMedium.sprite.setScale(1.1, 1.1);
	vector <Sprite> John_Dory2fish;
	vector <Vector2f> John_Dory2_velocity;
	vector <Vector2f> John_Dory2_direction;
	vector <int> John_Dory2_directionRand;
	vector <int> John_Dory2_currentFrame;
	vector <Clock> John_Dory2_clock;
	vector <float> John_Dory2_time;
	int John_Dory2SpawnTimer = 8;
	bool eatingJohn_Dory2 = false;
	int currentFrameEatingJohn_Dory2 = 0;
	Clock eatingClockJohn_Dory2;
	float eatingTimeJohn_Dory2 = eatingClockJohn_Dory2.getElapsedTime().asMilliseconds();



	//Large enemies / bigEnemy
	Entity enemyLarge = { 20, 1, 2, 13, 5, 6, 2.25f, 0.225f, 0.1875f };
	enemyLarge.texture.loadFromFile("Resources/Sprites/bigEnemy.png");
	enemyLarge.sprite.setTexture(enemyLarge.texture);
	enemyLarge.sprite.setTextureRect(IntRect(271, 0, -271, 121));
	enemyLarge.sprite.setScale(1.4, 1.4);
	vector <Sprite> bigEnemy;
	vector <Vector2f> bigEnemy_velocity;
	vector <Vector2f> bigEnemy_direction;
	vector <int> bigEnemy_directionRand;
	vector <int> bigEnemy_currentFrame;
	vector <Clock> bigEnemy_clock;
	vector <float> bigEnemy_time;
	bool eatingbigEnemy = false;
	int currentFrameEatingbigEnemy = 0;
	Clock eatingClockbigEnemy;
	float eatingTimebigEnemy = eatingClockbigEnemy.getElapsedTime().asMilliseconds();
	int bigEnemySpawnTimer = 15, bigEnemySpawnQuantity = 2;


	//SOUNDS

	//minnowEating sound
	SoundBuffer eatingminnowbuffer;
	eatingminnowbuffer.loadFromFile("Resources/sounds/bite1.ogg");
	Sound eatingminnowsound;
	eatingminnowsound.setBuffer(eatingminnowbuffer);
	bool eatingminnowboolean = true;

	//surgeonEating sound
	SoundBuffer eatingsurgeonbuffer;
	eatingsurgeonbuffer.loadFromFile("Resources/sounds/bite2.ogg");
	Sound eatingsurgeonsound;
	eatingsurgeonsound.setBuffer(eatingsurgeonbuffer);
	bool eatingsurgeonboolean = true;

	//johndoryEating sound
	SoundBuffer eatingjohndorybuffer;
	eatingjohndorybuffer.loadFromFile("Resources/sounds/bite3.ogg");
	Sound eatingjohndorysound;
	eatingjohndorysound.setBuffer(eatingjohndorybuffer);
	bool eatingjohndoryboolean = true;

	//SoundBuffer GameOver
	SoundBuffer GameOverSoundbuffer;
	GameOverSoundbuffer.loadFromFile("Resources/sounds/GameOver.ogg");
	Sound GameOverSound;
	GameOverSound.setBuffer(GameOverSoundbuffer);
	bool playDeathSound = true;

	//gamemusic
	bool musicisplayed = true;
	Music gamemusic;
	gamemusic.openFromFile("Resources/music/level3music.ogg");
	gamemusic.play();
	gamemusic.setLoop(musicisplayed);

	//frenzy sound
	SoundBuffer Feedingfrenysoundbuffer;
	Feedingfrenysoundbuffer.loadFromFile("Resources/sounds/feedingFrenzy.ogg");
	Sound Feedingfrenysound;
	Feedingfrenysound.setBuffer(Feedingfrenysoundbuffer);


	//doublefrenzy sound
	SoundBuffer doublefrenzysoundbuffer;
	doublefrenzysoundbuffer.loadFromFile("Resources/sounds/doubleFrenzy.ogg");
	Sound doublefrenzysound;
	doublefrenzysound.setBuffer(doublefrenzysoundbuffer);

	//growth sound
	SoundBuffer Growthsoundbuffer;
	Growthsoundbuffer.loadFromFile("Resources/sounds/playerGrow.ogg");
	Sound Growthsound;
	Growthsound.setBuffer(Growthsoundbuffer);
	bool Growthsoundboolean = true;

	//eatgulp sound
	SoundBuffer eatgulpsoundbuffer;
	eatgulpsoundbuffer.loadFromFile("Resources/sounds/eatGulp.ogg");
	Sound eatgulpsound;
	eatgulpsound.setBuffer(eatgulpsoundbuffer);



	//view camera pausemenu
	View view(FloatRect(0, 0, 1000, 1000));
	View view1(FloatRect(0, 0, 1920, 1080));
	pausemenu.menuu[0].setCharacterSize(70);
	pausemenu.menuu[1].setCharacterSize(65);
	pausemenu.menuu[2].setCharacterSize(70);
	pausemenu.menuu[0].setPosition(Vector2f(400, 430));
	pausemenu.menuu[1].setPosition(Vector2f(350, 550));
	pausemenu.menuu[2].setPosition(Vector2f(420, 670));


	pausemenu.menuu[3].setString("");


	//Keeping the highest score
	ofstream ofHighScore;
	ifstream ifHighScore;

	ifHighScore.open("HighScore.txt", ios::in);

	ifHighScore >> highScoreInFile;
	ifHighScore.close();

	bool redBarMaxReached = false;


	while (true)
	{
		if (pagenumber == 8)
		{
			while (window.isOpen())
			{
				window.setView(view1);

				//Exiting
				Event event;
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed)
						window.close();
					if (event.type == Event::KeyPressed)
					{
						if (event.key.code == Keyboard::Escape)
						{
							mouseoversound.play();
							pausemenuisopen = true;
						}
						if (event.key.code == Keyboard::Up)
						{
							if (pausemenuisopen)
								mousedownsound.play();
							pausemenu.pausemoveup();
						}
						if (event.key.code == Keyboard::Down)
						{
							if (pausemenuisopen)
								mousedownsound.play();
							pausemenu.pausemovedown();
						}
						if (event.key.code == Keyboard::Return)
						{
							mouseoversound.play();

							if (pausemenu.getselecteditem() == 0)
							{
								pausenumber = 0;
								pausemenuisopen = false;
							}
							if (pausemenu.getselecteditem() == 1)
							{

								gamemusic.pause();
								pagenumber = 0;
							}
							if (pausemenu.getselecteditem() == 2)
							{

								pagenumber = 2;

							}
						}


					}

				}


				//Time between frames
				dt = dt_clock.restart().asSeconds();




				//Player's movement, collision with screen
				if (!pausemenuisopen)
				{
					playerMovement(player.velocity, player.direction, dt, player.maxVel, player.accel, player.resist, movementMultiplier);
					player.sprite.move(player.velocity.x * dt * movementMultiplier, player.velocity.y * dt * movementMultiplier);
				}
				playerScreenCollision(player.sprite, WINDOW_WIDTH, WINDOW_HEIGHT);

				//Player's animation
				if (!eating)
					animation(player.sprite, currentFramePlayer, player.rowMotion, player.maxFrameMotion, player.velocity,
						player.direction, animationClock, animationTime);

				//Player's idle animation
				if (player.velocity.x == 0 && player.velocity.y == 0)
				{
					idleTimer = idleClock.getElapsedTime().asMilliseconds();
					if (idleTimer >= 120)
					{
						if (player.direction.x >= 0)
						{
							player.sprite.setTextureRect(IntRect(currentFrameIdle * 201 + 201, 181, -201, 181));
							currentFrameIdle++;
							idleClock.restart();
						}
						else if (player.direction.x < 0)
						{
							player.sprite.setTextureRect(IntRect(currentFrameIdle * 201, 181, 201, 181));
							currentFrameIdle++;
							idleClock.restart();
						}
						if (currentFrameIdle >= maxFrameIdle)
							currentFrameIdle = 0;
					}
				}

				//Player levelup
				if (player.score >= enemyMedium.score && player.score < enemyLarge.score)
				{
					player.sprite.setScale(1.1, 1.1);
					istransparentFish[0] = false;
					if (Growthsoundboolean) {
						Growthsound.play();
						Growthsoundboolean = false;
					}
				}
				if (player.score >= enemyLarge.score)
				{
					player.sprite.setScale(1.6, 1.6);
					istransparentFish[1] = false;
					if (!Growthsoundboolean) {
						Growthsound.play();
						Growthsoundboolean = true;
					}
				}

				if (player.score >= enemyMedium.score)
				{
					John_Dory2SpawnTimer = 5;
					bigEnemySpawnTimer = 12;
					bigEnemySpawnQuantity = 3;
				}
				if (player.score >= enemyLarge.score)
				{
					bigEnemySpawnTimer = 8;
					bigEnemySpawnQuantity = 4;
				}

				//Enemy spawn
				if (!pausemenuisopen)
				{
					//Spawn timer
					for (int i = 0; i < 3; i++)
					{
						enemySpawnTimeElapsed[i] = spawn_clock[i].getElapsedTime().asSeconds();
					}
					//Minnow or small
					if (Surgeonfish2.size() <= 16)
					{
						if (enemySpawnTimeElapsed[0] >= 0.5)
						{
							int side = rand() % 2;
							if (side == 0)
								enemySmall.sprite.setPosition(0 - enemySmall.sprite.getGlobalBounds().width, rand() % (WINDOW_HEIGHT - 135) + 135);
							else
								enemySmall.sprite.setPosition(WINDOW_WIDTH, rand() % (WINDOW_HEIGHT - 135) + 135);

							Surgeonfish2.push_back(enemySmall.sprite);
							Surgeonfish2_velocity.push_back(enemySmall.velocity);
							Surgeonfish2_direction.push_back(enemySmall.direction);
							Surgeonfish2_directionRand.push_back(enemyDirectionRandomizer[0]);
							Surgeonfish2_currentFrame.push_back(currentFrameEnemy[0]);
							Surgeonfish2_clock.push_back(animationClock);
							Surgeonfish2_time.push_back(animationTime);

							enemySpawnTimeElapsed[0] = spawn_clock[0].restart().asSeconds();
						}
					}
					//Surgeonfish or medium
					if (John_Dory2fish.size() <= 12)
					{
						if (enemySpawnTimeElapsed[1] >= John_Dory2SpawnTimer)
						{
							int side = rand() % 2;
							if (side == 0)
								enemyMedium.sprite.setPosition(0 - enemyMedium.sprite.getGlobalBounds().width, rand() % (WINDOW_HEIGHT - 135) + 135);
							else
								enemyMedium.sprite.setPosition(WINDOW_WIDTH, rand() % (WINDOW_HEIGHT - 135) + 135);

							John_Dory2fish.push_back(enemyMedium.sprite);
							John_Dory2_velocity.push_back(enemyMedium.velocity);
							John_Dory2_direction.push_back(enemyMedium.direction);
							John_Dory2_directionRand.push_back(enemyDirectionRandomizer[1]);
							John_Dory2_currentFrame.push_back(currentFrameEnemy[1]);
							John_Dory2_clock.push_back(animationClock);
							John_Dory2_time.push_back(animationTime);

							enemySpawnTimeElapsed[1] = spawn_clock[1].restart().asSeconds();
						}
					}
					// John Dory or large
					if (bigEnemy.size() <= bigEnemySpawnQuantity)
					{
						if (enemySpawnTimeElapsed[2] >= bigEnemySpawnTimer)
						{
							int side = rand() % 2;
							if (side == 0)
								enemyLarge.sprite.setPosition(0 - enemyLarge.sprite.getGlobalBounds().width, rand() % (WINDOW_HEIGHT - 135) + 135);
							else
								enemyLarge.sprite.setPosition(WINDOW_WIDTH, rand() % (WINDOW_HEIGHT - 135) + 135);

							bigEnemy.push_back(enemyLarge.sprite);
							bigEnemy_velocity.push_back(enemyLarge.velocity);
							bigEnemy_direction.push_back(enemyLarge.direction);
							bigEnemy_directionRand.push_back(enemyDirectionRandomizer[2]);
							bigEnemy_currentFrame.push_back(currentFrameEnemy[2]);
							bigEnemy_clock.push_back(animationClock);
							bigEnemy_time.push_back(animationTime);

							enemySpawnTimeElapsed[2] = spawn_clock[2].restart().asSeconds();
						}
					}

					//Direction Randomizer
					for (int i = 0; i < 3; i++)
					{
						enemyMovementTimeElapsed[i] = movement_clock[i].getElapsedTime().asSeconds();
						if (enemyMovementTimeElapsed[i] >= 1)
						{
							if (i == 0)
							{
								for (int j = 0; j < Surgeonfish2.size(); j++)
								{
									Surgeonfish2_directionRand[j] = rand() % 8;
								}
							}
							if (i == 1)
							{
								for (int j = 0; j < John_Dory2fish.size(); j++)
								{
									John_Dory2_directionRand[j] = rand() % 8;
								}
							}
							if (i == 2)
							{
								for (int j = 0; j < bigEnemy.size(); j++)
								{
									bigEnemy_directionRand[j] = rand() % 8;
								}
							}
							enemyMovementTimeElapsed[i] = 0;
							movement_clock[i].restart();
						}
					}

					// enemy movement, behaviour, collision
					for (int i = 0; i < Surgeonfish2.size(); i++)
					{
						enemyMovement(Surgeonfish2_velocity[i], Surgeonfish2_direction[i], Surgeonfish2_directionRand[i], dt,
							enemySmall.maxVel, enemySmall.accel, enemySmall.resist, movementMultiplier, Surgeonfish2[i]); //DOESN'T MOVE IF THIS IS COMMENTED

						enemyBehavior(player.sprite, Surgeonfish2[i], Surgeonfish2_velocity[i], Surgeonfish2_direction[i], dt,
							enemySmall.maxVel, enemySmall.accel, enemySmall.resist, movementMultiplier);
						Surgeonfish2[i].move(Surgeonfish2_velocity[i].x * dt * movementMultiplier, Surgeonfish2_velocity[i].y * dt * movementMultiplier);

						animation(Surgeonfish2[i], Surgeonfish2_currentFrame[i], enemySmall.rowMotion, enemySmall.maxFrameMotion, Surgeonfish2_velocity[i],
							Surgeonfish2_direction[i], Surgeonfish2_clock[i], Surgeonfish2_time[i], animationLoopTime[0]);

						playerAndEnemyCollision(player.sprite, Surgeonfish2[i], player.score, enemySmall.score, deathStatus, i, Surgeonfish2, Surgeonfish2_velocity,
							Surgeonfish2_direction, Surgeonfish2_directionRand, Surgeonfish2_currentFrame, Surgeonfish2_clock, Surgeonfish2_time, eating, currentFrameEating, player.direction,
							eatingClock, eatingTime, eatingminnowsound, frenzyRow, frenzyColumn, ateInLastSeconds, frenzyClock,
							Feedingfrenysound, doublefrenzysound, eatgulpsound, leaderboardScore, frenzymulti, chompSprite, eatingnum);
					}
					for (int i = 0; i < John_Dory2fish.size(); i++)
					{
						enemyMovement(John_Dory2_velocity[i], John_Dory2_direction[i], John_Dory2_directionRand[i], dt,
							enemySmall.maxVel, enemySmall.accel, enemySmall.resist, movementMultiplier, John_Dory2fish[i]);
						if (player.score >= enemyMedium.score)
						{
							enemyBehavior(player.sprite, John_Dory2fish[i], John_Dory2_velocity[i], John_Dory2_direction[i], dt,
								enemyMedium.maxVel, enemyMedium.accel, enemyMedium.resist, movementMultiplier);
						}
						John_Dory2fish[i].move(John_Dory2_velocity[i].x * dt * movementMultiplier, John_Dory2_velocity[i].y * dt * movementMultiplier);
						if (!eatingJohn_Dory2)
							animation(John_Dory2fish[i], John_Dory2_currentFrame[i], enemyMedium.rowMotion, enemyMedium.maxFrameMotion, John_Dory2_velocity[i], John_Dory2_direction[i], John_Dory2_clock[i], John_Dory2_time[i], animationLoopTime[1]);

						playerAndEnemyCollision(player.sprite, John_Dory2fish[i], player.score, enemyMedium.score, deathStatus, i, John_Dory2fish, John_Dory2_velocity,
							John_Dory2_direction, John_Dory2_directionRand, John_Dory2_currentFrame, John_Dory2_clock, John_Dory2_time, eating, currentFrameEating, player.direction,
							eatingClock, eatingTime, eatingsurgeonsound, frenzyRow, frenzyColumn, ateInLastSeconds,
							frenzyClock, Feedingfrenysound, doublefrenzysound, eatgulpsound, leaderboardScore, frenzymulti, chompSprite, eatingnum);
					}
					for (int i = 0; i < bigEnemy.size(); i++)
					{
						enemyMovement(bigEnemy_velocity[i], bigEnemy_direction[i], bigEnemy_directionRand[i], dt,
							enemySmall.maxVel, enemySmall.accel, enemySmall.resist, movementMultiplier, bigEnemy[i]);
						if (player.score >= enemyLarge.score)
						{
							enemyBehavior(player.sprite, bigEnemy[i], bigEnemy_velocity[i], bigEnemy_direction[i], dt,
								enemyLarge.maxVel, enemyLarge.accel, enemyLarge.resist, movementMultiplier);
						}
						bigEnemy[i].move(bigEnemy_velocity[i].x * dt * movementMultiplier, bigEnemy_velocity[i].y * dt * movementMultiplier);

						if (!eatingbigEnemy)
							animation(bigEnemy[i], bigEnemy_currentFrame[i], enemyLarge.rowMotion, enemyLarge.maxFrameMotion, bigEnemy_velocity[i], bigEnemy_direction[i], bigEnemy_clock[i], bigEnemy_time[i], animationLoopTime[2]);

						playerAndEnemyCollision(player.sprite, bigEnemy[i], player.score, enemyLarge.score, deathStatus, i, bigEnemy, bigEnemy_velocity,
							bigEnemy_direction, bigEnemy_directionRand, bigEnemy_currentFrame, bigEnemy_clock, bigEnemy_time, eating, currentFrameEating, player.direction,
							eatingClock, eatingTime, eatingjohndorysound, frenzyRow, frenzyColumn, ateInLastSeconds,
							frenzyClock, Feedingfrenysound, doublefrenzysound, eatgulpsound, leaderboardScore, frenzymulti, chompSprite, eatingnum);
					}
				}

				//Enemy and enemy collision
				bool skipMinnow = false;
				for (int i = 0; i < Surgeonfish2.size(); i++)
				{
					//Minnow and Surgeonfish
					for (int j = 0; j < John_Dory2fish.size(); j++)
					{
						enemyAndEnemyCollision(Surgeonfish2[i], John_Dory2fish[j], enemySmall.score, enemyMedium.score, i, j, Surgeonfish2, John_Dory2fish, Surgeonfish2_velocity, John_Dory2_velocity,
							Surgeonfish2_direction, John_Dory2_direction, Surgeonfish2_directionRand, John_Dory2_directionRand, Surgeonfish2_currentFrame, John_Dory2_currentFrame,
							Surgeonfish2_clock, John_Dory2_clock, Surgeonfish2_time, John_Dory2_time, skipMinnow,
							eatingSurgeonfish2, currentFrameEatingSurgeonfish2, Surgeonfish2_direction[i], eatingClockSurgeonfish2, eatingTimeSurgeonfish2, 0,
							eatingJohn_Dory2, currentFrameEatingJohn_Dory2, John_Dory2_direction[j], eatingClockJohn_Dory2, eatingTimeJohn_Dory2, enemyMedium.maxFrameEat);
						if (skipMinnow)
							break;

						//Surgeonfish and JohnDory
						bool skipSurgeon = false;
						for (int k = 0; k < bigEnemy.size(); k++)
						{
							enemyAndEnemyCollision(John_Dory2fish[j], bigEnemy[k], enemyMedium.score, enemyLarge.score, j, k, John_Dory2fish, bigEnemy, John_Dory2_velocity, bigEnemy_velocity,
								John_Dory2_direction, bigEnemy_direction, John_Dory2_directionRand, bigEnemy_directionRand, John_Dory2_currentFrame, bigEnemy_currentFrame,
								John_Dory2_clock, bigEnemy_clock, John_Dory2_time, bigEnemy_time, skipSurgeon,
								eatingJohn_Dory2, currentFrameEatingJohn_Dory2, John_Dory2_direction[j], eatingClockJohn_Dory2, eatingTimeJohn_Dory2, enemyMedium.maxFrameEat,
								eatingbigEnemy, currentFrameEatingbigEnemy, bigEnemy_direction[k], eatingClockbigEnemy, eatingTimebigEnemy, enemyLarge.maxFrameEat);
							if (skipSurgeon)
								break;
						}
					}
					// Minnow and John Dory
					for (int j = 0; j < bigEnemy.size(); j++)
					{
						if (skipMinnow)
							break;
						enemyAndEnemyCollision(Surgeonfish2[i], bigEnemy[j], enemySmall.score, enemyLarge.score, i, j, Surgeonfish2, bigEnemy, Surgeonfish2_velocity, bigEnemy_velocity,
							Surgeonfish2_direction, bigEnemy_direction, Surgeonfish2_directionRand, bigEnemy_directionRand, Surgeonfish2_currentFrame, bigEnemy_currentFrame,
							Surgeonfish2_clock, bigEnemy_clock, Surgeonfish2_time, bigEnemy_time, skipMinnow,
							eatingSurgeonfish2, currentFrameEatingSurgeonfish2, Surgeonfish2_direction[i], eatingClockSurgeonfish2, eatingTimeSurgeonfish2, 0,
							eatingbigEnemy, currentFrameEatingbigEnemy, bigEnemy_direction[j], eatingClockbigEnemy, eatingTimebigEnemy, enemyLarge.maxFrameEat);
						if (skipMinnow)
							break;
					}
				}




				//FRENZY DECREASE
				frenzyTimeLimit = frenzyClock.getElapsedTime().asSeconds();
				if (frenzyTimeLimit > 2)
				{
					ateInLastSeconds = false;
				}
				frenzyTimeLoss = frenzyClockLoss.getElapsedTime().asMilliseconds();
				if (!ateInLastSeconds)
				{
					if (frenzyTimeLoss >= 350)
					{
						frenzyClockLoss.restart();
						if (frenzyRow > 0)
							frenzyRow--;

						if (frenzyRow == 0 && frenzyColumn != 0)
						{
							frenzyColumn--;
							if (frenzyColumn > 0)
								frenzyRow = 6;
							else
								frenzyRow = 0;
						}
						if (frenzyRow == 0 && frenzyColumn == 0)
						{
							frenzyColumn = 0;
							frenzyRow = 0;
						}
					}
				}
				//FRENZY UPDATE
				frenzySprite.setTextureRect(IntRect(frenzyColumn * 350, frenzyRow * 120, 350, 120));

				//Frenzy Multiplier
				if (frenzyColumn < 2 && frenzyRow < 6)
				{
					frenzyMultiplier.setString("1X");
					frenzyMultiplier.setFillColor(Color::White);
					frenzymulti = 1;
				}
				else if ((frenzyColumn == 1 && frenzyRow == 6) || (frenzyColumn == 2 && frenzyRow < 6))
				{
					frenzyMultiplier.setString("2X");
					frenzyMultiplier.setFillColor(Color::Blue);
					frenzymulti = 2;
				}
				else if (frenzyColumn == 2 && frenzyRow == 6)
				{
					frenzyMultiplier.setString("3X");
					frenzyMultiplier.setFillColor(Color::Red);
					frenzymulti = 3;
				}

				//Score number update
				ScoreText.setString("" + to_string(leaderboardScore));

				//Redbar Levelup update
				if (BarRed.getSize().x < 694) {
					BarRed.setSize(Vector2f(player.score * 20, 11));
				}
				else
				{
					BarRed.setSize(Vector2f(694, 11));

					if (!redBarMaxReached)
					{
						stagesound.play();

						//High score override
						if (highScoreInFile < leaderboardScore)
						{
							highScoreInFile = leaderboardScore;
							ofHighScore.open("HighScore.txt", ios::out | ios::trunc);
							ofHighScore << leaderboardScore;
							ofHighScore.close();
						}
						levelnumber = 4;
						gamemusic.stop();
						pagenumber = 9;
						endgame(window, mousedownbuffer, mousedownsound, mouseoverbuffer, mouseoversound, introbuffer, introsound, stagebuffer, stagesound, music);


					}
					redBarMaxReached = true;
				}

				//score = false;
				//Render draw
				window.clear();
				if (pagenumber != 8)
				{
					break;
				}
				window.draw(backgroundSprite);

				//Return To Menu to continue
				menu ok(window.getSize().x, window.getSize().y);
				ok.menuu[0].setString("Return To Menu");
				ok.menuu[2].setString("");
				ok.menuu[1].setString("");
				ok.menuu[3].setString("");
				ok.menuu[0].setFillColor(Color::Red);
				ok.menuu[0].setCharacterSize(120);
				ok.menuu[0].setPosition(Vector2f(470, 800));

				//Enemy draw
				for (int i = 0; i < Surgeonfish2.size(); i++)
				{
					window.draw(Surgeonfish2[i]);
				}
				for (int i = 0; i < John_Dory2fish.size(); i++)
				{
					window.draw(John_Dory2fish[i]);
				}
				for (int i = 0; i < bigEnemy.size(); i++)
				{
					window.draw(bigEnemy[i]);
				}

				//Scorebar, frenzy and player draw
				if (!deathStatus)
				{
					//Scorebar
					window.draw(ScoreBar);
					window.draw(BarBlack);
					window.draw(BarRed);
					window.draw(Triangle);
					window.draw(Triangle1);

					//Enemy sprite in scorebar
					window.draw(ScoreSurgeonfish2);
					window.draw(ScoreJohn_Dory2fish);
					window.draw(ScorebigEnemy);
					if (istransparentFish[0])
						window.draw(transparentFish[0]);
					if (istransparentFish[1])
						window.draw(transparentFish[1]);

					//Chomp draw
					if (eating)
						window.draw(chompSprite);

					//Draw frenzy, it's multiplier and the score
					window.draw(frenzyMultiplier);
					window.draw(ScoreText);
					window.draw(frenzySprite);

					//Player
					window.draw(player.sprite);
				}

				//draw background
				else
				{
					ok.draw(window);
					window.draw(GameOverBackground);
					window.draw(GameOver);
					Event event2;
					//return to main menu after game over
					while (window.pollEvent(event2))
					{

						if (event2.type == Event::KeyReleased)
						{
							if (event2.key.code == Keyboard::Return)
							{
								mouseoversound.play();

								pagenumber = 15;

							}
						}
					}
					if (playDeathSound)
					{
						GameOverSound.play();
						playDeathSound = false;
						gamemusic.stop();

					}
					if (highScoreInFile < leaderboardScore)
					{
						highScoreInFile = leaderboardScore;
						ofHighScore.open("HighScore.txt", ios::out | ios::trunc);
						ofHighScore << leaderboardScore;
						ofHighScore.close();
					}
				}

				//when pause menu open
				if (pausemenuisopen)
				{
					window.setView(view);
					window.draw(pausemenusprite);
					pausemenu.draw(window);
				}


				window.display();
			}

			if (pausenumber == 0)
			{
				pausemenuisopen = false;


			}
			if (pagenumber == 0)
			{
				music.play();
				windoww(window, mousedownbuffer, mousedownsound, mouseoverbuffer, mouseoversound, introbuffer, introsound, stagebuffer, stagesound, music);
			}
			if (pagenumber == 2)
			{
				gamemusic.pause();
				window.close();
			}
			if (pagenumber == 15)
			{
				pagenumber = 0;
				windoww(window, mousedownbuffer, mousedownsound, mouseoverbuffer, mouseoversound, introbuffer, introsound, stagebuffer, stagesound, music);
			}
		}
	}

}
void endgame(RenderWindow& window, SoundBuffer& mousedownbuffer, Sound& mousedownsound, SoundBuffer& mouseoverbuffer, Sound& mouseoversound, SoundBuffer& introbuffer, Sound& introsound, SoundBuffer& stagebuffer, Sound& stagesound, Music& music)
{
	stagesound.play();

	Sprite backgrounds;
	Texture backgroundt;
	backgroundt.loadFromFile("Resources/backgrounds/options.jpg");
	backgrounds.setTexture(backgroundt);
	View view(FloatRect(0, 0, 1000, 1000));
	window.setView(view);

	Font font;
	font.loadFromFile("Resources/Fonts/Five.otf");


	menu returntomenu(1200, window.getSize().y);
	returntomenu.menuu[0].setString("Back to Main Menu");
	returntomenu.menuu[0].setCharacterSize(40);
	returntomenu.menuu[0].setPosition(Vector2f(50, 800));


	returntomenu.menuu[1].setString("Exit");
	returntomenu.menuu[1].setCharacterSize(40);
	returntomenu.menuu[1].setPosition(Vector2f(500, 800));

	returntomenu.menuu[2].setString("Next Level");
	returntomenu.menuu[2].setPosition(Vector2f(750, 800));
	returntomenu.menuu[2].setCharacterSize(40);
	returntomenu.menuu[3].setString("");


	Text highscore, score, hey;
	highscore.setFont(font);
	score.setFont(font);



	highscore.setString("High score: " + to_string(highScoreInFile));
	highscore.setPosition(Vector2f(50, 150));
	highscore.setFillColor(Color::White);
	highscore.setCharacterSize(50);

	score.setString("Your score: " + to_string(leaderboardScore));
	score.setPosition(Vector2f(600, 150));
	score.setFillColor(Color::White);
	score.setCharacterSize(50);
	while (true)
	{

		if (pagenumber == 9)
		{


			while (window.isOpen())
			{
				Event event;
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed)
					{
						window.close();
					}
					if (event.type == Event::KeyReleased)
					{
						if (event.key.code == Keyboard::Right)
						{
							mousedownsound.play();

							returntomenu.pausemovedown();
						}
						if (event.key.code == Keyboard::Left)
						{
							mousedownsound.play();
							returntomenu.pausemoveup();

						}
						if (event.key.code == Keyboard::Return)
						{
							mouseoversound.play();
							if (returntomenu.getselecteditem() == 0)
							{
								pagenumber = 1000;
							}
							else if (returntomenu.getselecteditem() == 1)
							{
								pagenumber = 999;
							}
							else if (returntomenu.getselecteditem() == 2)
							{
								pagenumber = 998;
							}
						}


					}
				}

				window.clear();
				if (pagenumber != 9)
				{
					break;
				}
				window.draw(backgrounds);
				returntomenu.draw(window);
				window.draw(highscore);
				window.draw(score);
				window.display();

			}
			if (pagenumber == 1000)
			{
				pagenumber = 0;
				windoww(window, mousedownbuffer, mousedownsound, mouseoverbuffer, mouseoversound, introbuffer, introsound, stagebuffer, stagesound, music);
			}
			if (pagenumber == 999)
			{
				music.stop();
				window.close();
			}
			if (pagenumber == 998)
			{
				if (levelnumber == 1)
				{
					pagenumber = 6;
					Level2(window, mousedownbuffer, mousedownsound, mouseoverbuffer, mouseoversound, introbuffer, introsound, stagebuffer, stagesound, music);
				}
				else if (levelnumber == 2)
				{
					pagenumber = 7;
					Level3(window, mousedownbuffer, mousedownsound, mouseoverbuffer, mouseoversound, introbuffer, introsound, stagebuffer, stagesound, music);
				}
				else if (levelnumber == 3)
				{
					pagenumber = 8;
					Level4(window, mousedownbuffer, mousedownsound, mouseoverbuffer, mouseoversound, introbuffer, introsound, stagebuffer, stagesound, music);
				}
				else if (levelnumber == 4)
				{
					pagenumber = 10;
					congratulation(window, mousedownbuffer, mousedownsound, mouseoverbuffer, mouseoversound, introbuffer, introsound, stagebuffer, stagesound, music);
				}
			}
		}
	}

}
void congratulation(RenderWindow& window, SoundBuffer& mousedownbuffer, Sound& mousedownsound, SoundBuffer& mouseoverbuffer, Sound& mouseoversound, SoundBuffer& introbuffer, Sound& introsound, SoundBuffer& stagebuffer, Sound& stagesound, Music& music)
{
	Texture backgroundtexture;
	Sprite backgroundsprite;
	backgroundtexture.loadFromFile("Resources/Backgrounds/congratulation.jpg");
	backgroundsprite.setTexture(backgroundtexture);

	View view(FloatRect(0, 0, 1000, 1000));
	window.setView(view);

	Font font;
	font.loadFromFile("Resources/Fonts/Five.otf");

	Text highscore, score, ins, ins1, ins2, ins3, ins4, ins5, ins6;
	highscore.setFont(font);
	score.setFont(font);

	highscore.setString("High score: " + to_string(highScoreInFile));
	highscore.setPosition(Vector2f(100, 250));
	highscore.setFillColor(Color::Blue);
	highscore.setCharacterSize(50);

	score.setString("Your score: " + to_string(leaderboardScore));
	score.setPosition(Vector2f(600, 250));
	score.setFillColor(Color::Blue);
	score.setCharacterSize(50);

	ins.setFont(font);
	ins.setPosition(Vector2f(90, 400));
	ins.setCharacterSize(65);
	ins.setFillColor(Color(1, 150, 32));
	ins.setString(" Congratulation for wining !");

	ins1.setFont(font);
	ins1.setCharacterSize(35);
	ins1.setFillColor(Color::Blue);
	ins1.setString("Press Enter to return to mainmenu ");
	ins1.setPosition(Vector2f(200, 700));



	while (true)
	{
		if (pagenumber == 10)
		{
			while (window.isOpen())
			{
				Event event;
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed)
						window.close();
					if (event.type == Event::KeyReleased && event.key.code == Keyboard::Return)
					{
						pagenumber = 0;
					}


				}

				window.clear();
				if (pagenumber != 10)
				{
					break;
				}
				window.draw(backgroundsprite);
				window.draw(highscore);
				window.draw(score);
				window.draw(ins);
				window.draw(ins1);
				window.display();

			}
			if (pagenumber == 0)
			{
				windoww(window, mousedownbuffer, mousedownsound, mouseoverbuffer, mouseoversound, introbuffer, introsound, stagebuffer, stagesound, music);
			}
		}
	}

}


void playerMovement(Vector2f& playerVelocity, Vector2f& playerDirection, float dt,
	float playerMaxVel, float playerAccel, float playerResist, float movementMultiplier)
{
	//Player's movement
	//UP
	if (Keyboard::isKeyPressed(Keyboard::Key::W) || Keyboard::isKeyPressed(Keyboard::Key::Up))
	{
		playerDirection.y = -1.f;

		if (playerVelocity.y > -playerMaxVel)
			playerVelocity.y += playerAccel * playerDirection.y * dt * movementMultiplier;
	}
	//DOWN
	if (Keyboard::isKeyPressed(Keyboard::Key::S) || Keyboard::isKeyPressed(Keyboard::Key::Down))
	{
		playerDirection.y = 1.f;

		if (playerVelocity.y < playerMaxVel)
			playerVelocity.y += playerAccel * playerDirection.y * dt * movementMultiplier;
	}
	//LEFT
	if (Keyboard::isKeyPressed(Keyboard::Key::A) || Keyboard::isKeyPressed(Keyboard::Key::Left))
	{
		playerDirection.x = -1.f;

		if (playerVelocity.x > -playerMaxVel)
			playerVelocity.x += playerAccel * playerDirection.x * dt * movementMultiplier;
	}
	//RIGHT
	if (Keyboard::isKeyPressed(Keyboard::Key::D) || Keyboard::isKeyPressed(Keyboard::Key::Right))
	{
		playerDirection.x = 1.f;

		if (playerVelocity.x < playerMaxVel)
			playerVelocity.x += playerAccel * playerDirection.x * dt * movementMultiplier;
	}
	//Player's resistance
	//UP
	if (playerVelocity.y > 0.f)
	{
		playerVelocity.y -= playerResist * dt * movementMultiplier;

		if (playerVelocity.y < 0.f)
			playerVelocity.y = 0;
	}
	//DOWN
	else if (playerVelocity.y < 0.f)
	{
		playerVelocity.y += playerResist * dt * movementMultiplier;

		if (playerVelocity.y > 0.f)
			playerVelocity.y = 0;
	}
	//LEFT
	else if (playerVelocity.x < 0.f)
	{
		playerVelocity.x += playerResist * dt * movementMultiplier;

		if (playerVelocity.x > 0.f)
			playerVelocity.x = 0;
	}
	//RIGHT
	if (playerVelocity.x > 0.f)
	{
		playerVelocity.x -= playerResist * dt * movementMultiplier;

		if (playerVelocity.x < 0.f)
			playerVelocity.x = 0;
	}
}

void playerScreenCollision(Sprite& Sprite, const unsigned WINDOW_WIDTH, const unsigned WINDOW_HEIGHT)
{
	//Top
	if (Sprite.getPosition().y < 135)
		Sprite.setPosition(Sprite.getPosition().x, 135);
	//Down
	if (Sprite.getPosition().y + Sprite.getGlobalBounds().height > WINDOW_HEIGHT)
		Sprite.setPosition(Sprite.getPosition().x, WINDOW_HEIGHT - Sprite.getGlobalBounds().height);
	//Left
	if (Sprite.getPosition().x < 0)
		Sprite.setPosition(0, Sprite.getPosition().y);
	//Right
	if (Sprite.getPosition().x + Sprite.getGlobalBounds().width > WINDOW_WIDTH)
		Sprite.setPosition(WINDOW_WIDTH - Sprite.getGlobalBounds().width, Sprite.getPosition().y);
}

void enemyAndEnemyCollision(Sprite& enemy1Sprite, Sprite& enemy2Sprite, int score1, int score2, int position1, int position2, vector<Sprite>& sprite1, vector<Sprite>& sprite2,
	vector <Vector2f>& velocity1, vector <Vector2f>& velocity2, vector <Vector2f>& direction1, vector <Vector2f>& direction2,
	vector<int>& directionRand1, vector<int>& directionRand2, vector<int>& currentFrame1, vector<int>& currentFrame2,
	vector <Clock>& clock1, vector <Clock>& clock2, vector<float>& time1, vector<float>& time2, bool& skip,
	bool& eating1, int& currentFrameEating1, Vector2f direction11, Clock& clockEating1, float timeEating1, int maxFrameEat1,
	bool& eating2, int& currentFrameEating2, Vector2f direction22, Clock& clockEating2, float timeEating2, int maxFrameEat2)
{
	if (enemy1Sprite.getGlobalBounds().intersects(enemy2Sprite.getGlobalBounds()))
	{
		if (score1 > score2)
		{
			sprite2.erase(sprite2.begin() + position2);
			velocity2.erase(velocity2.begin() + position2);
			direction2.erase(direction2.begin() + position2);
			directionRand2.erase(directionRand2.begin() + position2);
			currentFrame2.erase(currentFrame2.begin() + position2);
			clock2.erase(clock2.begin() + position2);
			time2.erase(time2.begin() + position2);
			skip = true;
			eating1 = true;
			currentFrameEating1 = 0;
		}
		else if (score1 < score2)
		{
			sprite1.erase(sprite1.begin() + position1);
			velocity1.erase(velocity1.begin() + position1);
			direction1.erase(direction1.begin() + position1);
			directionRand1.erase(directionRand1.begin() + position1);
			currentFrame1.erase(currentFrame1.begin() + position1);
			clock1.erase(clock1.begin() + position1);
			time1.erase(time1.begin() + position1);
			skip = true;
			eating2 = true;
			currentFrameEating2 = 0;
		}
	}
	if (eating1)
	{
		timeEating1 = clockEating1.getElapsedTime().asMilliseconds();
		if (timeEating1 >= 80)
		{
			if (direction11.x == 1)
			{

				enemy1Sprite.setTextureRect(IntRect(currentFrameEating1 * enemy1Sprite.getLocalBounds().width + enemy1Sprite.getLocalBounds().width,
					0, -enemy1Sprite.getLocalBounds().width, enemy1Sprite.getLocalBounds().height));
				currentFrameEating1++;
				clockEating1.restart();
				if (currentFrameEating1 > maxFrameEat1)
				{
					currentFrameEating1 = 0;
					eating1 = false;
				}
			}
			else if (direction11.x == -1)
			{

				enemy1Sprite.setTextureRect(IntRect(currentFrameEating1 * enemy1Sprite.getLocalBounds().width,
					0, enemy1Sprite.getLocalBounds().width, enemy1Sprite.getLocalBounds().height));
				currentFrameEating1++;
				clockEating1.restart();

				if (currentFrameEating1 > maxFrameEat1)
				{
					currentFrameEating1 == 0;
					eating1 = false;
				}
			}
		}
	}
	if (eating2)
	{
		timeEating2 = clockEating2.getElapsedTime().asMilliseconds();
		if (timeEating2 >= 80)
		{
			if (direction22.x == 1)
			{

				enemy2Sprite.setTextureRect(IntRect(currentFrameEating2 * enemy2Sprite.getLocalBounds().width + enemy2Sprite.getLocalBounds().width,
					0, -enemy2Sprite.getLocalBounds().width, enemy2Sprite.getLocalBounds().height));
				currentFrameEating2++;
				clockEating2.restart();
				if (currentFrameEating2 >= maxFrameEat2)
				{
					currentFrameEating2 = 0;
					eating2 = false;
				}
			}
			else if (direction22.x == -1)
			{

				enemy2Sprite.setTextureRect(IntRect(currentFrameEating2 * enemy2Sprite.getLocalBounds().width,
					0, enemy2Sprite.getLocalBounds().width, enemy2Sprite.getLocalBounds().height));
				currentFrameEating2++;
				clockEating2.restart();

				if (currentFrameEating2 >= maxFrameEat2)
				{
					currentFrameEating2 = 0;
					eating2 = false;
				}
			}
		}
	}
}

void enemyBehavior(Sprite& playerSprite, Sprite& enemySprite, Vector2f& enemyVelocity, Vector2f& enemyDirection, float dt,
	float enemyMaxVel, float enemyAccel, float enemyResist, float movementMultiplier)
{
	//enemy's escape movement
	//UP
	if (playerSprite.getPosition().y - enemySprite.getPosition().y < 200 && playerSprite.getPosition().y - enemySprite.getPosition().y > 0 &&
		playerSprite.getPosition().x - enemySprite.getPosition().x < 250 && playerSprite.getPosition().x - enemySprite.getPosition().x > -250)
	{
		enemyDirection.y = -1.f;

		if (enemyVelocity.y > -enemyMaxVel)
			enemyVelocity.y += enemyAccel * enemyDirection.y * dt * movementMultiplier * 1.4;
	}
	//DOWN
	if (playerSprite.getPosition().y - enemySprite.getPosition().y > -200 && playerSprite.getPosition().y - enemySprite.getPosition().y < 0 &&
		(playerSprite.getPosition().x - enemySprite.getPosition().x < 250 && playerSprite.getPosition().x - enemySprite.getPosition().x > -250))
	{
		enemyDirection.y = 1.f;

		if (enemyVelocity.y < enemyMaxVel)
			enemyVelocity.y += enemyAccel * enemyDirection.y * dt * movementMultiplier * 1.4;
	}
	//LEFT
	if (playerSprite.getPosition().x - enemySprite.getPosition().x < 250 && playerSprite.getPosition().x - enemySprite.getPosition().x > 0 &&
		playerSprite.getPosition().y - enemySprite.getPosition().y < 200 && playerSprite.getPosition().y - enemySprite.getPosition().y > -200)
	{
		enemyDirection.x = -1.f;

		if (enemyVelocity.x > -enemyMaxVel)
			enemyVelocity.x += enemyAccel * enemyDirection.x * dt * movementMultiplier * 1.4;
	}
	//RIGHT
	if (playerSprite.getPosition().x - enemySprite.getPosition().x > -250 && playerSprite.getPosition().x - enemySprite.getPosition().x < 0 &&
		playerSprite.getPosition().y - enemySprite.getPosition().y < 200 && playerSprite.getPosition().y - enemySprite.getPosition().y > -200)
	{
		enemyDirection.x = 1.f;

		if (enemyVelocity.x < enemyMaxVel)
			enemyVelocity.x += enemyAccel * enemyDirection.x * dt * movementMultiplier * 1.4;
	}
}