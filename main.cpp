#include "gameengine.h"
#include "playstate.h"
#include "menustate.h"
#include <SFML/Audio.hpp>


int main()
{

  CGameEngine game;

  // initialize the engine
	game.Init("Snake 360");

	game.PushState(CMenuState::Instance());

  //main game music
  sf::Music menumusic;
  if (!menumusic.openFromFile("wetlands.wav")) {
    //error opening music file
  }
  menumusic.setLoop(true);
  menumusic.setVolume(25);
  menumusic.play();


  // main loop
	while (game.Running())
	{
		game.HandleEvents();
		game.Update();
		game.Draw();
	}

  // cleanup the engine
	game.Cleanup();



  return 0;
}
