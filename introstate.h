
#ifndef INTROSTATE_H
#define INTROSTATE_H

#include "gamestate.h"
#include "gamemode.h"

class CIntroState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CGameEngine* game);
	void Update(CGameEngine* game);
	void Draw(CGameEngine* game);

	static CIntroState* Instance() {
		return &m_IntroState;
	}


protected:
	CIntroState() { }

private:
	static CIntroState m_IntroState;

};

#endif
