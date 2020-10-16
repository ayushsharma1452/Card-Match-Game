#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameManager.h" 

using namespace FinalProject;
  
GameManager::GameManager()
{  
}

GameManager::~GameManager()
{ 
}
 
void  GameManager::Run()
{ 
	//starts clock here
	sf::Clock clock; 
	 
	//playing audio:
	/*
	sf::SoundBuffer backgroundMusic;
	backgroundMusic.loadFromFile("Materials/birdsWaveFile.wav");
	sf::Sound sound;
	sound.setBuffer(backgroundMusic);
	sound.play();
	 */


	 
	Game game;
	game.init(); //Initialize game basic bethods, like importing assets

	float lastT = 0;
	while (game.window.isOpen())
	{
		sf::Time elapsed = clock.getElapsedTime();

		float curT = elapsed.asSeconds();
		//Time Step
		float TimeStep = curT - lastT;
		lastT = curT;

		//Game Update
		game.newState(TimeStep);
		//Game Render
		game.drawIndividuals(TimeStep);

	 
	} 
} 
