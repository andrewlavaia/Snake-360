
#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <SFML/Graphics.hpp>

#include <vector>
#include "gamemode.h"
#include "controlmode.h"

class CGameState;

class CGameEngine
{
public:

	void Init(const char* title, int width=640, int height=480,
           bool fullscreen=false);
	void Cleanup();

	void ChangeState(CGameState* state);
	void PushState(CGameState* state);
	void PopState();

	void HandleEvents();
	void Update();
	void Draw();

	bool Running() { return m_running; }
	void Quit() { m_running = false; }

	sf::RenderWindow window;

	GameMode m_GameMode;
	ControlMode m_ControlMode;


private:
	// the stack of states
	std::vector<CGameState*> states;

	bool m_running;
	bool m_fullscreen;
};

#endif
