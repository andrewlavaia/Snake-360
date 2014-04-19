
#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "gamestate.h"

class CPlayState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CGameEngine* game);
	void Update(CGameEngine* game);
	void Draw(CGameEngine* game);

	static CPlayState* Instance() {
		return &m_PlayState;
	}

protected:
	CPlayState() {
	}

private:
	static CPlayState m_PlayState;

};

#endif
