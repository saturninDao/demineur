#pragma once

#include <SFML/Graphics.hpp>
#include "Etat.hpp"
#include "Game.hpp"


namespace SaturninFlorence{
    class MainMenuState:public Etat{
    public:
        MainMenuState(GameDataRef data);

        void Init();

        void GererEntrer();
        void Update(float dt);
        void Dessiner(float dt);

    private:
        GameDataRef _data;
        sf::Sprite _background;
        sf::Sprite _playButton;
        sf::Sprite _normalButton;
        sf::Sprite _intermediaireButton;
        sf::Sprite _difficileButton;
        sf::Sprite _titre;
    };
}

