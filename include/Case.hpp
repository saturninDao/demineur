#pragma once

#include "DEFINITIONS.hpp"
#include <string>
#include "Game.hpp"
#include <SFML/Graphics.hpp>

namespace SaturninFlorence {
      class Case
    {
        public:
            Case();

            void afficher(sf::RenderWindow& fenetre);
            void decouvrir();
            void setPlace(float x, float y);
            float getX();
            float getY();
            float getPlace();
            void placerMine();
            void placerCase(float x, float y);
            void Marquer();
            void ajoutVoisin();
            int nombreCaseMineVoisine;

//        private:
            GameDataRef _data = std::make_shared<GameData>();
            float _x;
            float _y;
            bool _estMarque = false;
            bool _estMinee = false;
            bool _estDecouvers = false;
            sf::Sprite _face;
    };
}
