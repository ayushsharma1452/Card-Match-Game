#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h" 

using namespace FinalProject;
 
//Initialization of GameLogic
Game::Game()
{
	this->window.create(sf::VideoMode(800, 600), "Final Project", sf::Style::Titlebar);
}

Game::~Game()
{ 
}
 
//Local Variables for Game Logic
bool showFirstTime = false;
int turns = 0; 
float current_pause_length;
float pausedAt;  
float t;

//Item status, which stores state of a card: hidden, destroyed, visible
Card::ItemStatus itemStatus;

void Game::init()
{
	//Import card images
	this->savedimages.clear();
	this->savedimages.resize(10);
	for (int i = 0; i < 10; i++) 
	{
		std::string str="Image";
		str += char('0' + i);
		str += ".png"; 
		savedimages[i].loadFromFile("Materials/" + str);
	}
	//Import background,font,back and front sides of a card
	this->backtxt.loadFromFile("Materials/background.png");
	this->backspt.setTexture(this->backtxt, true); 
	this->itemfronttxt.loadFromFile("Materials/front.png");
	this->itemtxt.loadFromFile("Materials/back.png"); 
	this->font.loadFromFile("Materials/PixellettersFull.ttf");


	//Import of audios
	this->clickAudio.loadFromFile("Materials/click.wav");
	this->winAudio.loadFromFile("Materials/win.wav");
	this->loseAudio.loadFromFile("Materials/lose.wav");
	this->longWinAudio.loadFromFile("Materials/longWan.wav");


	//Start call for game logic
	this->StartGame();
}

void  Game::StartGame()
{
	this->GameFinished = false;
	this->items.clear();
	std::vector<std::pair<int, int> > indices;
	indices.clear();
	for (int i = 0; i < 10; i++) 
	{
		//Creates vector of 20 pair variables, where 1st element is random and 2nd element is from (0,9) range

		indices.push_back(std::make_pair(rand(), i));
		indices.push_back(std::make_pair(rand(), i));
	}
	std::sort(indices.begin(), indices.end());

	//After sorting, we get randommly distributed cards: shufflet
	for (int i = 0; i < 20; i++) {
		int ind = indices[i].second;
		this->items.push_back(new Card(this));
		this->items[i]->declare(ind);
	}
	itemStatus = Card::ItemStatus::Visible;
	this->changeStates();

	t = 0;
	current_pause_length =  pause2;
	pausedAt = 0;
	turns = 0;
	showFirstTime = false;
}
 
//Change states of card
void Game::changeStates() {
	for (int i = 0; i < 20; i++) {
		this->items[i]->itemStatus = itemStatus;
	}
}

//Gets card if mouse is inside of it
int Game::getItemInside(float x, float y)
{
	for (int i = 0; i < 20; i++) {
		if (this->items[i]->ClickOccured(x, y)) return i;
	}
	return -1;
}




 
void Game::newState(float TimeStep)
{
	t = t + TimeStep;

	if (t > 4 && showFirstTime == false) 
	{
		//If it's first time of load, wait untill user remembers cards
		itemStatus = Card::ItemStatus::Hidden;
		this->changeStates();
		showFirstTime = true;
	}

	//Set each cards positions
	for (int rows = 0; rows < 5; rows++)
	{
		for (int col = 0; col < 4; col++) 
		{
			int ind = rows * 4 + col;
			this->items[ind]->setPosition(rows, col);
		}
	}
	std::vector<int> openedInds;
	openedInds.clear();

	//If game is not in pause stage
	if (pausedAt + current_pause_length <= t) 
	{
		//Retrieve data of opened cards
		for (int i = 0; i < 20; i++) 
		{
			if (this->items[i]->itemStatus == Card::ItemStatus::Visible) {
				openedInds.push_back(i);
			}
		}






		if (openedInds.size() == 2) {
			int x = openedInds[0], y = openedInds[1];

			if (this->items[x]->index != this->items[y]->index) 
			{
				//If these cards are not same

				//Hide these cards again
				this->items[x]->itemStatus = Card::ItemStatus::Hidden;
				this->items[y]->itemStatus = Card::ItemStatus::Hidden;

				 
			}
			else 
			{
				//If these cards are same

				//Destroy these cards 
				this->items[x]->itemStatus = Card::ItemStatus::Destroyed;
				this->items[y]->itemStatus = Card::ItemStatus::Destroyed;

				bool Finished = true;
				for (int i = 0; i < 20; i++)
				{
					//Check if there are left any cards hidden
					if (this->items[i]->itemStatus != Card::ItemStatus::Destroyed)
						Finished = false;
				}
				 
				//Play Sounds if all cards are destroyed
				if (Finished) 
				{
					this->GameFinished = true;
					this->longWinSound.setBuffer(this->longWinAudio);
					this->longWinSound.play();
				}
			}
		}
	}


	sf::Event event;
	while (window.pollEvent(event)) 
	{  //Listen to input
		if (!event.type != sf::Event::Closed) {
			window.close();
		}
		if (pausedAt + current_pause_length <= t) {

			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//If mouse click
					int clickedInd = getItemInside(event.mouseButton.x, event.mouseButton.y);
					if (clickedInd != -1) //Get clicked card ind
					{
						this->items[clickedInd]->itemStatus = Card::ItemStatus::Visible;
						turns += 1;
						//Increase number of turns

					  //Play click sound
						this->clickSound.setBuffer(this->clickAudio); 
						this->clickSound.play();
					}

					if (this->GameFinished) {
						this->StartGame();
						//If game finished, and then restart was clicked start new one
					}
				}
			}

		}
	}
	if (pausedAt + current_pause_length <= t)
	{
		//If game is in pause state
		openedInds.clear();
		for (int i = 0; i < 20; i++) {
			if (this->items[i]->itemStatus == Card::ItemStatus::Visible) {
				openedInds.push_back(i);
			}
		}

		if (openedInds.size() == 2) 
		{
			//If new opened cards count are 2, pause again
			pausedAt = t;
			current_pause_length = pause1;
			if (openedInds.size() == 2) {
				int x = openedInds[0], y = openedInds[1];

				if (this->items[x]->index != this->items[y]->index) {
					this->loseSound.setBuffer(this->loseAudio);
					this->loseSound.play();
				}
				else {

					this->winSound.setBuffer(this->winAudio);
					this->winSound.play();
				}
			}
		}
	}
}

//Called once game finished, and draws finish screen elements
void Game::FinishScreen() 
{
	sf::Text text;
	text.setFont(this->font);
	text.setString("It took only " + std::to_string(turns / 2) + " turns for finishing round!");
	text.setCharacterSize(40);
	text.setFillColor(sf::Color::Yellow);
	text.setStyle(sf::Text::Bold);
	text.setPosition(140, 200);

	sf::Texture texture;
	texture.loadFromFile("Materials/button.png");


	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale(0.3, 0.3);
	sprite.setPosition(230, 300);
	window.draw(sprite);

	sf::Text text2;
	text2.setFont(this->font);
	text2.setString("Restart");
	text2.setCharacterSize(30);
	text2.setFillColor(sf::Color::White);
	text2.setStyle(sf::Text::Bold);
	text2.setPosition(350, 330);

	window.draw(text);
	window.draw(text2);
}

//Render components
void Game::drawIndividuals(float TimeStep)
{
	this->window.clear(); 
	window.draw(this->backspt); 
	for (int i = 0; i < 20; i++)
		this->items[i]->renderItem(); 
	if (this->GameFinished)
	{
		FinishScreen();
	}
	this->window.display();
}
 