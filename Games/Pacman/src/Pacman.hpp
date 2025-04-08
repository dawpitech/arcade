/*
** EPITECH PROJECT, 2025
** pacman
** File description:
** uwu
*/

#include <list>
#include <tuple>
#include "ANAL/IArcade.hpp"
#include "ANAL/IGame.hpp"
#include "ANAL/Vector2.hpp"
#define MAP_SIZE 32

class Player
{
    public:
	enum STATE {
	    NORMAL,
	    HIGH,
	    DEAD
	};

	enum LOOK {
	    RIGHT,
	    LEFT
	};
    
	Player();

	[[nodiscard]] int getScore() const;
	void setScore(int Score);
	[[nodiscard]] ANAL::Vector2<int> getPos() const; 
	void setPos(ANAL::Vector2<int> v);
	[[nodiscard]] Player::STATE getState() const;
	void setState(Player::STATE s);
	void tickHigh();
	void tickReset();
	[[nodiscard]] LOOK getLook() const;
	void setLook(LOOK);

    private:
	int m_score;
	ANAL::Vector2<int> m_player_pos{16, 18};
	Player::STATE m_state;
	int m_tick_to_normal;
	LOOK m_look;
};

class Ghost {
    public:
	enum STATE {
	    NORMAL,
	    SCARED,
	    DEAD
	};

	enum LOOK {
	    RIGHT,
	    LEFT
	};
    
	Ghost(ANAL::Vector2<int> pos, const std::string &color);

	[[nodiscard]] ANAL::Vector2<int> getPos() const; 
	[[nodiscard]] ANAL::Vector2<int> getOrgPos() const; 
	void setPos(ANAL::Vector2<int> v);
	[[nodiscard]] Ghost::STATE getState() const;
	void setState(Ghost::STATE s);
	void tickDead();
	void tickReset();
	[[nodiscard]] LOOK getLook() const;
	void setLook(LOOK);
	[[nodiscard]] std::string getColor() const;
	void setColor(std::string &col);
	[[nodiscard]] bool getPassedGate() const;
	void setPassedGate(const bool &p);

    private:
	ANAL::Vector2<int> m_ghost_pos{0, 0};
	ANAL::Vector2<int> m_ghost_org_pos{0, 0};
	Ghost::STATE m_state;
	int m_tick_to_normal;
	std::string m_color;
	bool m_passed_gate;
	LOOK m_look;
};

class Game : public ANAL::IGame
{
    public:
	Game();
	~Game() override;

	void processEvents(std::vector<ANAL::Event>&) override;
	void compute(ANAL::IArcade& arcade) override;
	void render(ANAL::IRenderer& renderer, const ANAL::IArcade& arcade) override;

    private:
	void deinit();
	void init();
	void restart();

	std::vector<std::string> _pacmanmap;
	Player m_player;
	std::string m_player_name;
	int m_time_ghosts = 0;
	int m_best_score;
	std::vector<Ghost> m_ghosts;
};
