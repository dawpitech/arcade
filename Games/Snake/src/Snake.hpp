/*
** EPITECH PROJECT, 2025
** Snake
** File description:
** uwu
*/

#include "ANAL/IGame.hpp"
#include "ANAL/Vector2.hpp"
#include <deque>

class Game : public ANAL::IGame
{
    public:
	Game();
	~Game() override;

	void processEvents(std::vector<ANAL::Event>&) override;
	void compute() override;
	void render(ANAL::IRenderer& renderer, const ANAL::IArcade& arcade) override;

    private:
	void deinit();
	void init();
	void restart();

	std::vector<std::string> _snakemap;
	ANAL::Vector2<int> m_berrypos{0, 0};
	std::deque<ANAL::Vector2<int>> m_snake;
	ANAL::Vector2<int> m_direction{0, 0};
	bool m_game_ended;
	int m_score;
	int m_bestscore;
};
