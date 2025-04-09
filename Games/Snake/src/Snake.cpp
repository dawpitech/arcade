/*
** EPITECH PROJECT, 2025
** Snake
** File description:
** uwu
*/

#include "Snake.hpp"
#include <algorithm>
#include <random>
#include <string>
#include "ANAL/Events.hpp"
#include "ANAL/IArcade.hpp"
#include "ANAL/IModule.hpp"
#include "ANAL/Vector2.hpp"

std::vector<std::string> snakmap_org =
{
".............................",
".............................",
"##############################",
"#                            #",
"#                            #",
"#                            #",
"#                            #",
"#                            #",
"#                            #",
"#                            #",
"#                            #",
"#                            #",
"#                            #",
"#                            #",
"#                            #",
"#                            #",
"#                            #",
"#                            #",
"#                            #",
"#                            #",
"#                            #",
"#                            #",
"#                            #",
"#                            #",
"#                            #",
"#                            #",
"#                            #",
"#                            #",
"#                            #",
"#                            #",
"##############################",
".............................",
};

void Game::deinit()
{
    
}

void Game::init()
{
    this->m_player_name = "";
    this->m_game_ended = false;
    this->m_bestscore = -1;
    this->m_score = 0;
    this->m_berrypos = {10, 10};
    this->_snakemap = snakmap_org;
    this->m_snake.clear();
    this->m_snake.push_back({15, 15});
    this->m_direction = {1, 0};
    this->_snakemap[15][15] = '@';
}

void Game::restart()
{
    this->deinit();
    this->init();
}

Game::Game()
{
    this->init();
}

Game::~Game() { this->deinit(); }

void Game::processEvents(std::vector<ANAL::Event> &ev)
{
    for (auto &e : ev)
    {
        if (e.type == ANAL::EventType::KEYBOARD)
        {
            auto key = e.keyEvent->key;
            if (key == ANAL::Keys::ARROW_UP && m_direction.y == 0)
                m_direction = {0, -1};
            if (key == ANAL::Keys::ARROW_DOWN && m_direction.y == 0)
                m_direction = {0, 1};
            if (key == ANAL::Keys::ARROW_LEFT && m_direction.x == 0)
                m_direction = {-1, 0};
            if (key == ANAL::Keys::ARROW_RIGHT && m_direction.x == 0)
                m_direction = {1, 0};
            if (key == ANAL::Keys::KEY_R && this->m_game_ended)
                this->restart();
        }
    }
}

void Game::compute(ANAL::IArcade &arcade)
{
    if (this->m_player_name == "")
	this->m_player_name = arcade.getPlayerName();
    if (this->m_bestscore == -1)
	this->m_bestscore = arcade.getPlayerHighscore(this->m_player_name);
    if (this->m_game_ended) return;

    static int frame = 0;
    if (++frame < 5) return;
    frame = 0;

    auto new_head = m_snake.front();
    new_head.x += m_direction.x;
    new_head.y += m_direction.y;

    bool hit_self = false;
    for (auto &segment : m_snake)
    {
	if (segment.x == new_head.x && segment.y == new_head.y)
	{
	    hit_self = true;
	    break;
	}
    }
    if (_snakemap[new_head.y][new_head.x - 1] == '#' || hit_self)
    {
	m_game_ended = true;
	return;
    }
    m_snake.push_front(new_head);
    if (new_head.x == m_berrypos.x && new_head.y == m_berrypos.y)
    {
        m_score += 100;
        do {
            m_berrypos = {rand() % 28 + 1, rand() % 30};
        } while (_snakemap[m_berrypos.y][m_berrypos.x - 1] != ' ');
    }
    else
    {
        auto tail = m_snake.back();
        _snakemap[tail.y][tail.x - 1] = ' ';
        m_snake.pop_back();
    }
    _snakemap[new_head.y][new_head.x - 1] = '+';
}

void Game::render(ANAL::IRenderer &renderer, const ANAL::IArcade &arcade)
{
    renderer.clear();
    renderer.setWindowTitle("Snake");
    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            auto const map_e = arcade.newEntity();
            auto const map_a = arcade.newAsset();
            std::string tile = "./assets/Snake/textures/";
            switch (this->_snakemap[i][j])
            {
                case '#':
                    tile += "wall.png";
                    break;
                default:
		    tile = "";
		    break;
            }
	    if (tile != "") {
		map_a->setTexturePath(tile);
		map_a->setAlternateRender(this->_snakemap[i][j]);
		map_e->setPos(ANAL::Vector2(j + 1, i));
		map_e->setAsset(*map_a);
		renderer.drawEntity(*map_e);
	    }
        }
    }
    auto const berry_e = arcade.newEntity();
    auto const berry_a = arcade.newAsset();
    berry_a->setTexturePath("./assets/Snake/textures/berry.png");
    berry_a->setAlternateRender('@');
    berry_e->setPos(this->m_berrypos);
    berry_e->setAsset(*berry_a);
    renderer.drawEntity(*berry_e);
    renderer.drawText("Player: " + this->m_player_name, ANAL::Vector2(1, 0));
    renderer.drawText("Score: " + std::to_string(this->m_score), ANAL::Vector2(1, 1));
    renderer.drawText("Best: " + std::to_string(this->m_bestscore), ANAL::Vector2(20, 1));
    for (auto &segment : m_snake)
    {
	auto seg_e = arcade.newEntity();
	auto seg_a = arcade.newAsset();
	seg_a->setTexturePath("./assets/Snake/textures/snake.png");
	seg_a->setAlternateRender('o');
	seg_e->setPos(segment);
	seg_e->setAsset(*seg_a);
	renderer.drawEntity(*seg_e);
    }
    static int frame = 0;
    frame++;
    if (this->m_game_ended)
    {
	if (this->m_score > this->m_bestscore)
	    this->m_bestscore = this->m_score;
        if ((frame / 20) % 2 == 0)
        {
            renderer.drawText(" Game Over", ANAL::Vector2(13, 13));
            renderer.drawText("Player: " + this->m_player_name, ANAL::Vector2(13, 14));
            renderer.drawText("Score: " + std::to_string(this->m_score), ANAL::Vector2(13, 15));
            renderer.drawText("Best: " + std::to_string(this->m_bestscore), ANAL::Vector2(13, 16));
            renderer.drawText("Press R to restart", ANAL::Vector2(12, 17));
        }
    }
    if (frame >= 6000)
        frame = 0;
    renderer.render();
}

extern "C" std::unique_ptr<ANAL::IGame> uwu_entrypoint_game(void) { return std::make_unique<Game>(); }

ANAL::ModuleVersion uwu_get_module_version() { return ANAL::ModuleVersion::V1_1_0; }

ANAL::ModuleType uwu_get_module_type() { return ANAL::ModuleType::GAME; }
