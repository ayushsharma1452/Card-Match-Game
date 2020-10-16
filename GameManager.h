#pragma once  
#include<vector>  
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <algorithm>
#include "Game.h"
#include "Card.h"

namespace FinalProject
{ 
	class GameManager
	{
	private:
		  
	public:
		 

		//Functions 
		GameManager();
		virtual ~GameManager();

		void  Run(); 
	};

}