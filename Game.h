#pragma once 
 
#include<vector>  
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <algorithm>
#include <iostream>
#include "Card.h"
#include "GameManager.h"
namespace FinalProject
{
	//Cross Reference Header to avoid errors
	class Card;
	class Game
	{
	private:   
		//List of cards located on canvas
		std::vector<Card*> items;
		 
		//Change Status of each Card
		void changeStates();

		//Gets index of a card if (x,y) locates inside it
		int getItemInside(float x, float y);


	public:
		
		//Pause Between Opens
		static const int pause1 = 1;

		//Pause At Start
		static const int pause2 = 1;

		//Audios
		sf::SoundBuffer clickAudio;
		sf::SoundBuffer winAudio;
		sf::SoundBuffer loseAudio; 
		sf::SoundBuffer longWinAudio;

		// sounds
		sf::Sound clickSound;
		sf::Sound winSound;
		sf::Sound loseSound;
		sf::Sound longWinSound;
		sf::RenderWindow window;
		 
		//Fonts
		sf::Font font;

		//Textures
		sf::Texture backtxt;
		sf::Sprite backspt;

		sf::Texture itemtxt;
		sf::Texture itemfronttxt;

		//Imported textures for cards
		std::vector<sf::Texture> savedimages;

		//Information  
		bool GameFinished;

		//Functions 
		Game();
		virtual ~Game();

		//Functions 
		void StartGame();  //  Called when each round Starts
		void init();
		void newState(float TimeStep);  
		void drawIndividuals(float TimeStep); // Render with a TimeStep
		void FinishScreen();  // Finish Stage
	};

}