/*
** EPITECH PROJECT, 2025
** pacman
** File description:
** uwu
*/

#include "ANAL/IGame.hpp"
#define MAP_SIZE 32

class Game : public ANAL::IGame
{
    public:
	Game();
	~Game() override;

	void processEvents(std::vector<ANAL::Event>&) override;
	void compute() override;
	void render(ANAL::IRenderer& renderer, const ANAL::IArcade& arcade) override;
};
