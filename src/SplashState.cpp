#pragma once

#include <sstream>
#include "SplashState.hpp"
#include <iostream>

#include "DEFINITIONS.hpp"
#include "MainMenuState.hpp"

namespace SaturninFlorence
{
    SplashState::SplashState(GameDataRef data) : _data(data)
    {
    }

    void SplashState::Init()
    {
        this->_data->assets.LoadTexture("Arriere plan du splash", SPLASH_SCENE_BACKGROUND_FILEPATH);

        _background.setTexture(this->_data->assets.GetTexture("Arriere plan du splash"));
    }

    void SplashState::GererEntrer()
    {
        sf::Event event;
        while (this->_data->fenetre.pollEvent(event))
        {
            if (sf::Event::Closed == event.type)
            {
                this->_data->fenetre.close();
            }
        }
    }

    void SplashState::Update(float dt)
    {
        if (this->_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
        {
            //Aller au menu du jeu
            //this->_data->machine.AjoutEtat(EtatRef(new MainMenuState(_data)), true);
            this->_data->machine.AjoutEtat(EtatRef(new MainMenuState(this->_data)));
        }
    }

    void SplashState::Dessiner(float dt)
    {
        this->_data->fenetre.clear(sf::Color::Red);

        this->_data->fenetre.draw(this->_background);

        this->_data->fenetre.display();
    }
}
