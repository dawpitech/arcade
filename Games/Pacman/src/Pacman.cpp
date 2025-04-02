/*
** EPITECH PROJECT, 2025
** Pacman
** File description:
** uwu
*/

#include "Pacman.hpp"
#include "ANAL/Events.hpp"
#include "ANAL/IModule.hpp"
#include "ANAL/Vector2.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <random>

std::vector<std::string> pacmanmap_org =
{
        "                             ",
        "                             ",
        " ############################",
        " #.............o............#",
        " #............##............#",
        " #.####.#####.##.#####.####.#",
        " #.####.#####.##.#####.####.#",
        " #..........................#",
        " #..........................#",
        " #..###.##.########.##.###..#",
        " #......##....##..o.##......#",
        " #####..#####.##.#####..#####",
        "     #..##..........##..#    ",
        "     #..##.###__###.##..#    ",
        " #####..##.#      #.##..#####",
        " #.o.......#      #.........#",
        " #####..##.#      # ##..#####",
        "     #..##.######## ##..#    ",
        "     #..##..........##..#    ",
        " #####..##.########.##..#####",
        " #............##............#",
        " #..###.#####.##.#####.###..#",
        " #...##................##...#",
        " #...##................##...#",
        " ##..##.##.########.##.##..##",
        " #......##....##....##......#",
        " #.##########.##.##########.#",
        " #..........................#",
        " #.............o............#",
        " ############################",
        "                             ",
        "                             "
};

void Game::deinit() {
    this->m_ghosts.clear();
}

void Game::init() {
    this->m_player = Player();
    this->_pacmanmap = pacmanmap_org;
    this->m_time_ghosts = 0;//280;
    this->m_ghosts.emplace_back(ANAL::Vector2(15, 14), "red");
    this->m_ghosts.emplace_back(ANAL::Vector2(16, 14), "blue");
    this->m_ghosts.emplace_back(ANAL::Vector2(15, 16), "pink");
    this->m_ghosts.emplace_back(ANAL::Vector2(16, 16), "orange");
}

void Game::restart() {
    this->deinit();
    this->init();
}

Game::Game() {
    this->m_best_score = 0;
    this->init();
}

Game::~Game() {
    this->deinit(); 
}

void Game::processEvents(std::vector<ANAL::Event> &ev) {
    static int frame = 0;
    static int add_x = 0;
    static int add_y = 0;

    for (auto e: ev) {
	switch (e.type) {
	case ANAL::EventType::KEYBOARD:
	{
	    auto key = e.keyEvent.value().key;
	    auto down = e.keyEvent.value().state == ANAL::State::RELEASED;
	    if (key == ANAL::Keys::ARROW_UP)
		add_y = down ? 0 : -1;
	    if (key == ANAL::Keys::ARROW_DOWN)
		add_y = down ? 0 : +1;
	    if (key == ANAL::Keys::ARROW_LEFT) {
		add_x = down ? 0 : -1;
		this->m_player.setLook(Player::LEFT);
	    }
	    if (key == ANAL::Keys::ARROW_RIGHT) {
		add_x = down ? 0 : +1;
		this->m_player.setLook(Player::RIGHT);
	    }
	    if (key == ANAL::Keys::KEY_R && this->m_player.getState() == Player::DEAD)
		this->restart();
	    break;
	}
	default:
	    break;
	}
    }
    if (frame++ < 1 || this->m_player.getState() == Player::DEAD) {
	return;
    }
    frame = 0;
    int new_x = (this->m_player.getPos().x + add_x) - 1;
    int new_y = (this->m_player.getPos().y + add_y);
    if (this->_pacmanmap[new_y][new_x] == '#' ||
	this->_pacmanmap[new_y][new_x] == '_')
	return;
    if (this->_pacmanmap[new_y][new_x] == '.') {
	this->_pacmanmap[new_y][new_x] = ' ';
	this->m_player.setScore(this->m_player.getScore() + 100);
    }
    if (this->_pacmanmap[new_y][new_x] == 'o') {
	this->_pacmanmap[new_y][new_x] = ' ';
	this->m_player.setScore(this->m_player.getScore() + 1000);
	this->m_player.tickReset();
	this->m_player.setState(Player::HIGH);
    }
    this->m_player.setPos(ANAL::Vector2{this->m_player.getPos().x + add_x,
	    this->m_player.getPos().y + add_y});
}

void Game::compute() {
    if (this->m_player.getState() == Player::DEAD) {
	if (this->m_player.getScore() > this->m_best_score)
	    this->m_best_score = this->m_player.getScore();
	return;
    }

    static int frame = 0;
    if (this->m_time_ghosts > 0)
	m_time_ghosts--;
    for (Ghost &e: this->m_ghosts) {
	if (e.getState() == Ghost::DEAD) {
	    if (e.getPos().x == e.getOrgPos().x &&
		e.getPos().y == e.getOrgPos().y) {
		e.tickDead();
	    }
	    e.setPos({e.getOrgPos().x, e.getOrgPos().y});
	}
    }
    if (this->m_player.getState() == Player::HIGH) {
	this->m_player.tickHigh();
	for (Ghost &g: this->m_ghosts)
	    if (g.getState() != Ghost::DEAD)
		g.setState(Ghost::SCARED);
    } else {
	for (Ghost &g: this->m_ghosts)
	    if (g.getState() != Ghost::DEAD)
		g.setState(Ghost::NORMAL);
    }
    for (Ghost &e: this->m_ghosts) {
	if (e.getPos().x == this->m_player.getPos().x &&
	    e.getPos().y == this->m_player.getPos().y) {
	    if (this->m_player.getState() == Player::HIGH) {
		e.setState(Ghost::DEAD);
		e.tickReset();
		this->m_player.setScore(this->m_player.getScore() + 300);
	    }
	    if (this->m_player.getState() != Player::HIGH &&
		e.getState() != Ghost::DEAD)
		this->m_player.setState(Player::DEAD);
	}
    }
    if (frame++ < 2) {
	return;
    }
    frame = 0;
    if (this->m_time_ghosts > 0)
	return;

    std::random_device rd;
    std::mt19937 rng(rd());
    for (Ghost &g : this->m_ghosts) {
	if (g.getState() != Ghost::DEAD) {
	    ANAL::Vector2 pos = g.getPos();
	    if (!g.getPassedGate()) {
		if (this->_pacmanmap[pos.y + 1][pos.x - 1] == '_') {
		    g.setPassedGate(true);
		} else {
		    pos.y -= 1;
		    g.setPos(pos);
		    continue;
		}
	    }
	    std::vector<ANAL::Vector2<int>> valid_moves;
	    if (this->_pacmanmap[pos.y][pos.x - 1 - 1] != '#' &&
		this->_pacmanmap[pos.y][pos.x - 1 - 1] != '_')
		valid_moves.push_back({pos.x - 1, pos.y});
	    if (this->_pacmanmap[pos.y][pos.x + 1 - 1] != '#' &&
		this->_pacmanmap[pos.y][pos.x + 1 - 1] != '_')
		valid_moves.push_back({pos.x + 1, pos.y});
	    if (this->_pacmanmap[pos.y - 1][pos.x - 1] != '#' &&
	        this->_pacmanmap[pos.y - 1][pos.x - 1] != '_')
		valid_moves.push_back({pos.x, pos.y - 1});
	    if (this->_pacmanmap[pos.y + 1][pos.x - 1] != '#' &&
		this->_pacmanmap[pos.y + 1][pos.x - 1] != '_')
		valid_moves.push_back({pos.x, pos.y + 1});
	    if (!valid_moves.empty()) {
		std::shuffle(valid_moves.begin(), valid_moves.end(), rng);
		auto p = valid_moves.front();
		if (p.x > g.getPos().x) {
		    g.setLook(Ghost::LEFT);
		} else {
		    g.setLook(Ghost::RIGHT);
		}
		g.setPos(p);
	    }
	}
    }
}

void Game::render(ANAL::IRenderer& renderer, const ANAL::IArcade& arcade) {
    renderer.clear();
    renderer.setWindowTitle("Pacman");
    for (int i = 0; i < 32; i++) {
	for (int j = 0; j < 29; j++) {
	    auto const map_e= arcade.newEntity();
	    auto const map_a = arcade.newAsset();
	    std::string tile = "./assets/Pacman/textures/";
	    switch (this->_pacmanmap[i][j]) {
	    case '#':
		tile += "wall.png";
		break;
	    case '_':
		tile += "gate.png";
		break;
	    case '.':
		tile += "pacgum.png";
		break;
	    case 'o':
		tile += "spacgum.png";
		break;
	    default:
		tile += "void.png";
	    }
	    map_a->setTexturePath(tile);
	    map_a->setAlternateRender(this->_pacmanmap[i][j]);
	    map_e->setPos(ANAL::Vector2(j + 1, i));
	    map_e->setAsset(*map_a);
	    renderer.drawEntity(*map_e);
	}
    }
    renderer.drawText("Player: AAAA", ANAL::Vector2(2, 0));
    renderer.drawText("Score: " + std::to_string(this->m_player.getScore()), ANAL::Vector2(2, 1));
    renderer.drawText("Best: " + std::to_string(this->m_best_score), ANAL::Vector2(20, 1));
    auto const pacman_e= arcade.newEntity();
    auto const pacman_a = arcade.newAsset();
    std::string pass = "./assets/Pacman/textures/pacman";
    if (this->m_player.getState() == Player::HIGH)
	pass += "_high";
    if (this->m_player.getLook() == Player::LEFT)
	pass += "_inv";
    pacman_a->setTexturePath(pass + ".png");
    pacman_a->setAlternateRender('@');
    pacman_e->setPos(this->m_player.getPos());
    pacman_e->setAsset(*pacman_a);
    renderer.drawEntity(*pacman_e);

    for (Ghost &g: this->m_ghosts) {
	auto const ghost_e= arcade.newEntity();
	auto const ghost_a = arcade.newAsset();
	std::string path = "./assets/Pacman/textures/ghost_";
	if (g.getState() == Ghost::DEAD) {
	    path += "eyes";
	} else if (g.getState() == Ghost::SCARED) {
	    path += "scared";
	} else {
	    path += g.getColor();
	}
	if (g.getLook() == Ghost::LEFT && g.getState() != Ghost::SCARED)
	    path += "_inv";
	ghost_a->setTexturePath(path + ".png");
	ghost_a->setAlternateRender('$');
	ghost_e->setPos(g.getPos());
	ghost_e->setAsset(*ghost_a);
	renderer.drawEntity(*ghost_e);
    }
    static int frame = 0;
    frame++;
    if (this->m_player.getState() == Player::DEAD) {
	if ((frame / 20) % 2 == 0) {
	    renderer.drawText(" Game Over", ANAL::Vector2(13, 13));
	    renderer.drawText("Player: AAAA", ANAL::Vector2(13, 14));
	    renderer.drawText("Score: " + std::to_string(this->m_player.getScore()), ANAL::Vector2(13, 15));
	    renderer.drawText("Best: " + std::to_string(this->m_best_score), ANAL::Vector2(13, 16));
	    renderer.drawText("Press R to restart", ANAL::Vector2(12, 17));
	}
    }
    if (frame >= 6000)
	frame = 0;
    renderer.render();
}

extern "C" std::unique_ptr<ANAL::IGame> uwu_entrypoint_game(void)
    { return std::make_unique<Game>(); }

ANAL::ModuleVersion uwu_get_module_version()
    { return ANAL::ModuleVersion::V1_1_0; }

ANAL::ModuleType uwu_get_module_type()
    { return ANAL::ModuleType::GAME; }
