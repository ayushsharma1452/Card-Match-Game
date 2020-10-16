
#pragma once 
 
#include<vector>  
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <algorithm>
#include <iostream>
#include "Game.h"

namespace FinalProject
{
	class Game;
	 
	class Card
	{ 
		 

	public:
		//Destroyed: means that card is no longer in game
		//Visible: card still is in play
		//Hidden: card is in play and hidden
		enum class  ItemStatus 
		{
			Destroyed = 0, Visible = 1, Hidden = 2 
		};

		//Game which is controller for Item Object
		Game* Main;
		//Index from screen: location of item on canvas
		int index;

		//Detailed locatin of Item
		int rowIndex,colIndex;
		//Item State
		ItemStatus itemStatus;
		 
		//Sprites used to render details
		sf::Sprite itemmain;
		sf::Sprite itemback;
		sf::Sprite itemfront;

		//Constructors
		Card(Game* main);
		virtual ~Card();

		//Intializator and assigner of card nummer
		void declare(int i);

		//Assign index of card annd import textures
		bool ClickOccured(float x, float y); 
		//Change Position of Item
		void setPosition(int r, int c);
		//Renders Item
		void renderItem();
	};

}
