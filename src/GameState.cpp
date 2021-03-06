#pragma once

#include <sstream>
#include "GameState.hpp"
#include "GameOverState.hpp"
#include "MainMenuState.hpp"
#include "PauseState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

namespace TepeGolo
{
	GameState::GameState(GameDataRef data) : _data(data){}

	void GameState::Init(){
		gameState = STATE_PLAYING;
		turn = CASE;

		this->_data->assets.LoadTexture("Button Pause", PAUSE_BUTTON);
		this->_data->assets.LoadTexture("Grid Sprite", GRID_SPRITE_FILEPATH);
		this->_data->assets.LoadTexture("Case Vide", CASE_VIDE_PATH);
		this->_data->assets.LoadTexture("Case Minee", CASE_MINEE_PATH);

		_background.setTexture(this->_data->assets.GetTexture("Background"));
		_pauseButton.setTexture(this->_data->assets.GetTexture("Button Pause"));
		_gridSprite.setTexture(this->_data->assets.GetTexture("Grid Sprite"));

		_pauseButton.setPosition( this->_data->fenetre.getSize( ).x - _pauseButton.getLocalBounds( ).width, _pauseButton.getPosition( ).y );
		_gridSprite.setPosition( (SCREEN_WIDTH/2)- (_gridSprite.getGlobalBounds().width/2), (SCREEN_HEIGHT/2)- (_gridSprite.getGlobalBounds().height/2) );

		InitCase();
		for(int x=0; x<9; x++){
            for(int y=0; y<9; y++){
                gridArray[x][y]=EMPTY_PIECE;
            }
		}
	}

	void GameState::GererEntrer()
	{
		sf::Event event;

		while (this->_data->fenetre.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->fenetre.close();
			}

			if (this->_data->imput.IsSpriteClicked(this->_pauseButton, sf::Mouse::Left, this->_data->fenetre))
			{
				// PAUSE
				this->_data->machine.AjoutEtat(EtatRef(new PauseState(_data)), true);
				//this->_data->machine.AjoutEtat(EtatRef(new GameOverState(_data)), true);
				//std::cout << "Pause The Game" << std::endl;
			}
			else if(this->_data->imput.IsSpriteClicked(this->_gridSprite, sf::Mouse::Left, this->_data->fenetre)){
                this->Decouvrire();
			}
		}
	}

	void GameState::Update(float dt)
	{

	}

	void GameState::Dessiner(float dt)
	{
		this->_data->fenetre.clear(sf::Color::Red);

		this->_data->fenetre.draw( this->_background );

		this->_data->fenetre.draw( this->_pauseButton );
		this->_data->fenetre.draw( this->_gridSprite );
		for(int x=0; x<9; x++){
            for(int y=0; y<9; y++){
                this->_data->fenetre.draw( this->_cases[x][y] );
            }
		}

		this->_data->fenetre.display();
	}

	void GameState::InitCase()
	{
		sf::Vector2u tempSpriteSize = this->_data->assets.GetTexture("Case Vide").getSize();

		for (int x = 0; x < 9; x++)
		{
			for (int y = 0; y < 9; y++)
			{
				_cases[x][y].setTexture(this->_data->assets.GetTexture("Case Vide"));
				_cases[x][y].setPosition(_gridSprite.getPosition().x + (tempSpriteSize.x * x) + 7,
                            _gridSprite.getPosition().y + (tempSpriteSize.y * y) + 7);
				_cases[x][y].setColor(sf::Color(0, 255, 255, 255));
			}
		}
	}

	void GameState::Decouvrire(){
	    sf::Vector2i posClick = this->_data->imput.GetMousePosition(this->_data->fenetre);
	    sf::FloatRect tailleGrille = _gridSprite.getGlobalBounds();
	    sf::Vector2f espace = sf::Vector2f((SCREEN_WIDTH - tailleGrille.width)/2, (SCREEN_HEIGHT-tailleGrille.height)/2);
	    sf::Vector2f posSurGrille = sf::Vector2f(posClick.x-espace.x, posClick.y-espace.y);

	    sf::Vector2f tailleCase = sf::Vector2f(tailleGrille.width/9, tailleGrille.height/9);
	    int colonne, ligne;

        //Determinons la colonne
	    if(posSurGrille.x < tailleCase.x){
            colonne =1;
	    }
	    else if(posSurGrille.x < tailleCase.x*2){
            colonne =2;
	    }
	    else if(posSurGrille.x < tailleCase.x*3){
            colonne =3;
	    }
	    else if(posSurGrille.x < tailleCase.x*4){
            colonne =4;
	    }
	    else if(posSurGrille.x < tailleCase.x*5){
            colonne =5;
	    }
	    else if(posSurGrille.x < tailleCase.x*6){
            colonne =6;
	    }
	    else if(posSurGrille.x < tailleCase.x*7){
            colonne =7;
	    }
	    else if(posSurGrille.x < tailleCase.x*8){
            colonne =8;
	    }
	    else if(posSurGrille.x < tailleGrille.width){
            colonne =9;
	    }

        //Determinons la ligne
	    if(posSurGrille.y < tailleCase.y){
            ligne =1;
	    }
	    else if(posSurGrille.y < tailleCase.y*2){
            ligne =2;
	    }
	    else if(posSurGrille.y < tailleCase.y*3){
            ligne =3;
	    }
	    else if(posSurGrille.y < tailleCase.y*4){
            ligne =4;
	    }
	    else if(posSurGrille.y < tailleCase.y*5){
            ligne =5;
	    }
	    else if(posSurGrille.y < tailleCase.y*6){
            ligne =6;
	    }
	    else if(posSurGrille.y < tailleCase.y*7){
            ligne =7;
	    }
	    else if(posSurGrille.y < tailleCase.y*8){
            ligne =8;
	    }
	    else if(posSurGrille.y < tailleGrille.height){
            ligne =9;
	    }

	    if (gridArray[colonne-1][ligne-1] = CASE_VIDE){
            gridArray[colonne-1][ligne-1] = turn;
            if(CASE == turn){
                _cases[colonne-1][ligne-1].setTexture(this->_data->assets.GetTexture("Case Minee"));
                turn = AI_PIECE;
            }
            else if(AI_PIECE == turn){
                _cases[colonne-1][ligne-1].setTexture(this->_data->assets.GetTexture("Case Vide"));
                turn = CASE;
            }

            _cases[colonne-1][ligne-1].setColor(sf::Color(255,255,255,255));
	    }
	}

}
