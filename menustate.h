
#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "gamestate.h"
#include "gamemode.h"

class CMenuState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CGameEngine* game);
	void Update(CGameEngine* game);
	void Draw(CGameEngine* game);

	static CMenuState* Instance() {
		return &m_MenuState;
	}

  int hoverflag = 0;


protected:
	CMenuState() { }

private:
	static CMenuState m_MenuState;


};

#endif
