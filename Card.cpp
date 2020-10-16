#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Card.h" 
using namespace FinalProject;

//Basic Constructor, which stores GameLogic: Controller of this card
Card::Card(Game* main)
{
	this->Main = main;  
	this->index = -1;
	this->rowIndex = -1;
	this->colIndex = -1;   
}

//Assign index of card annd import textures
void Card::declare(int i)
{   
	// gets the index 
	this->index = i;

	// sets the texture of the card 
	this->itemmain.setTexture(this->Main->savedimages[index]);
	// sets the scale of the card
	this->itemmain.setScale(0.2, 0.2);

	// sets the texture of the back of the card
	this->itemback.setTexture(this->Main->itemtxt); 
	// sets the scale for the back of the card
	this->itemback.setScale(110 / 512.0, 110 / 512.0);

	// stes the texture of the front of the card
	this->itemfront.setTexture(this->Main->itemfronttxt);
	// sets the scale for the front of the card
	this->itemfront.setScale(110 / 512.0, 110 / 512.0);
}

// destrutor
Card::~Card()
{
}

  
//Returns true if mouse has clicked
bool Card::ClickOccured(float x, float y)
{
	// checks if the card is hidden or not
	if (this->itemStatus != ItemStatus::Hidden)
	{
		// return false if the card is not hidden
		return false;
	}

	// define the base x and the column index
	float base_x = 174.0 + this->colIndex * 117.0;
	// define the base y  and the row index
	float base_y = 17.0 + this->rowIndex * 117.0;

	return (x >= base_x && x <= base_x + 100 && y >= base_y && y <= base_y + 100);
}

//Change position of Item
void Card::setPosition(int r, int c)
{
	// row position of current card
	this->rowIndex = r;
	// column position of current card
	this->colIndex = c;
	
	// define position of basex and column index
	float base_x = 174.0 + this->colIndex * 117.0;
	// define the position of the base y and the row index
	float base_y = 17.0 + this->rowIndex * 117.0;

	// sets the position of the object
	this->itemmain.setPosition(base_x, base_y);
	//sets the position of the card at the back
	this->itemback.setPosition(base_x - 5, base_y - 5);
	// set the position of the card in front 
	this->itemfront.setPosition(base_x - 5, base_y - 5);
}
 
//Render Item
void Card::renderItem()
{
	// if  condition to check the current is destroyed 
	if (this->itemStatus == ItemStatus::Destroyed)
	{
		// return the function
		return;
	}

	// switch case for the current  card status
	switch (this->itemStatus)
	{
		// case if the card is destroyed
		case ItemStatus::Destroyed:
			return;   
			break;
			// case if the card is visible
		case ItemStatus::Visible:

			// display card
			this->Main->window.draw(this->itemfront);
			this->Main->window.draw(this->itemmain);
			break;

			// case if the card is still hidden
		case ItemStatus::Hidden:
			this->Main->window.draw(this->itemback);
			break;
	} 
}
