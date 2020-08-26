#pragma once

#include <sstream>
#include "GameOverState.hpp"
#include "DEFINITIONS.hpp"
#include "GameState.hpp"
#include "MainMenuState.hpp"

#include <iostream>

namespace SaturninFlorence
{
	GameOverState::GameOverState(GameDataRef data) : _data(data)
	{

	}

	void GameOverState::Init()
	{
		this->_data->assets.LoadTexture("Retry Button", RETRY_BUTTON);
		this->_data->assets.LoadTexture("Home Button", HOME_BUTTON);

		this->_retryButton.setTexture(this->_data->assets.GetTexture("Retry Button"));
		this->_homeButton.setTexture(this->_data->assets.GetTexture("Home Button"));

		this->_retryButton.setPosition((this->_data->fenetre.getSize().x / 2) - (this->_retryButton.getLocalBounds().width / 2), (this->_data->fenetre.getSize().y / 3) - (this->_retryButton.getLocalBounds().height / 2));
		this->_homeButton.setPosition((this->_data->fenetre.getSize().x / 2) - (this->_homeButton.getLocalBounds().width / 2), (this->_data->fenetre.getSize().y / 3 * 2) - (this->_homeButton.getLocalBounds().height / 2));
	}

	void GameOverState::GererEntrer()
	{
		sf::Event event;

		while (this->_data->fenetre.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->fenetre.close();
			}

			if (this->_data->imput.IsSpriteClicked(this->_retryButton, sf::Mouse::Left, this->_data->fenetre))
			{
				// Switch To Main Menu State By Replacing The Game Over State
				this->_data->machine.AjoutEtat(EtatRef(new GameState(_data)), true);
			}

			if (this->_data->imput.IsSpriteClicked(this->_homeButton, sf::Mouse::Left, this->_data->fenetre))
			{
				// Switch To Main Menu State By Replacing The Game Over State
				this->_data->machine.AjoutEtat(EtatRef(new MainMenuState(_data)), true);

			}
		}
	}

	void GameOverState::Update(float dt)
	{

	}

	void GameOverState::Dessiner(float dt)
	{
		this->_data->fenetre.clear(sf::Color::Red);

		this->_data->fenetre.draw(this->_retryButton);
		this->_data->fenetre.draw(this->_homeButton);

		this->_data->fenetre.display();
	}
}
