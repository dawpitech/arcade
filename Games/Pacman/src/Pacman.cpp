/*
** EPITECH PROJECT, 2025
** Pacman
** File description:
** uwu
*/

#include "Pacman.hpp"
#include "ANAL/IModule.hpp"
#include <iostream>
#include <string>

Game::Game() {
    
}

Game::~Game() {
    
}

void Game::processEvents(std::vector<ANAL::Event> &) {
    std::cout << "Pacman is processing Events" << std::endl;
}

void Game::compute() {
    std::cout << "Pacman is computing" << std::endl;
}

std::vector<std::string> pacmanmap =
{
        "                             ",
        "                             ",
        " ############################",
        " #..........................#",
        " #............##............#",
        " #.####.#####.##.#####.####.#",
        " #.####.#####.##.#####.####.#",
        " #..........................#",
        " #..........................#",
        " #..###.##.########.##.###..#",
        " #......##....##....##......#",
        " ##### .##### ## #####. #####",
        "     # .##          ##. #    ",
        "     # .## ######## ##. #    ",
        " ##### .## #      # ##. #####",
        " #     .   #      #   .     #",
        " ##### .## #      # ##. #####",
        "     # .## ######## ##. #    ",
        "     # .##          ##. #    ",
        " ##### .## ######## ##. #####",
        " #............##............#",
        " #..###.#####.##.#####.###..#",
        " #...##................##...#",
        " #...##................##...#",
        " ##..##.##.########.##.##..##",
        " #......##....##....##......#",
        " #.##########.##.##########.#",
        " #..........................#",
        " #..........................#",
        " ############################",
        "                             ",
        "                             "
};

void Game::render(ANAL::IRenderer& renderer, const ANAL::IArcade& arcade) {
    std::cout << "Pacman is rendering" << std::endl;
    renderer.clear();
    renderer.setWindowTitle("Pacman");
    for (int i = 0; i < 32; i++) {
	for (int j = 0; j < 29; j++) {
	    auto const map_e= arcade.newEntity();
	    auto const map_a = arcade.newAsset();
	    std::string tile = "./assets/Pacman/textures/";
	    switch (pacmanmap[i][j]) {
	    case '#':
		tile += "wall.png";
		break;
	    default:
		tile += "void.png";
	    }
	    map_a->setTexturePath(tile);
	    map_a->setAlternateRender(pacmanmap[i][j]);
	    map_e->setPos(ANAL::Vector2(j + 1, i));
	    map_e->setAsset(*map_a);
	    renderer.drawEntity(*map_e);
	}
    }
    renderer.render();
}

extern "C" std::unique_ptr<ANAL::IGame> uwu_entrypoint_game(void)
    { return std::make_unique<Game>(); }

ANAL::ModuleVersion uwu_get_module_version()
    { return ANAL::ModuleVersion::V1_1_0; }

ANAL::ModuleType uwu_get_module_type()
    { return ANAL::ModuleType::GAME; }
