
#ifndef GAMEMODE_H
#define GAMEMODE_H

#include <string>

class GameMode
{
public:
  GameMode(std::string type="endurance", double speed=.20);
  int getHighScore() { return highscore; };
  std::string getGameType() { return gametype; };
  double getGameSpeed() { return gamespeed; };


  void setHighScore(int score) { this->highscore = score; };
  void setGameType(std::string type) { this->gametype = type; };
  void setGameSpeed(double speed) { this->gamespeed = speed; };

private:
  int highscore;
  std::string gametype;
  double gamespeed;
};


#endif
