
#ifndef HIGHSCORESTATE_H
#define HIGHSCORESTATE_H

#include "gamestate.h"
#include "gamemode.h"

class CHighScoreState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CGameEngine* game);
	void Update(CGameEngine* game);
	void Draw(CGameEngine* game);

	static CHighScoreState* Instance() {
		return &m_HighScoreState;
	}

  std::vector <int> m_survival_normal_scores;
  std::vector <int> m_survival_fast_scores;
  std::vector <int> m_endurance_normal_scores;
  std::vector <int> m_endurance_fast_scores;

protected:
	CHighScoreState() { }

private:
	static CHighScoreState m_HighScoreState;

};

#endif
