
#include <string>
#include "gameengine.h"
#include "gamestate.h"
#include "menustate.h"
#include "introstate.h"
#include "playstate.h"
#include "gamemode.h"
#include "controlmode.h"
#include <iostream>


CIntroState CIntroState::m_IntroState;

void CIntroState::Init()
{

  std::cout << "Intro State started." << std::endl ;

}

void CIntroState::Cleanup()
{

  std::cout << "Intro State ended." << std::endl ;

}

void CIntroState::Pause()
{

}

void CIntroState::Resume()
{

}

void CIntroState::HandleEvents(CGameEngine* game)
{
    sf::Event event;

    while (game->window.pollEvent(event)) {

      switch (event.type) {

        case sf::Event::Closed:
          game->window.close();
          game->Quit();
          break;

        case sf::Event::KeyPressed:
              game->PushState( CPlayState::Instance() );
              break;

        case sf::Event::MouseButtonPressed:
              game->PushState( CPlayState::Instance() );
              break;

        }

      }

}

void CIntroState::Update(CGameEngine* game)
{

}

void CIntroState::Draw(CGameEngine* game)
{


  //Fetch current game settings
  std::string gamespeed;
  if(game->m_GameMode.getGameSpeed() == .20) {gamespeed = "normal"; };
  if(game->m_GameMode.getGameSpeed() == .30) {gamespeed = "fast"; };

  std::string gametype = game->m_GameMode.getGameType();
  std::string controltype = game->m_ControlMode.getControlType();

  //Set Default font and text settings
  sf::Font font;
  font.loadFromFile("arial.ttf");
  sf::Text default_text_settings;
  default_text_settings.setFont(font);
  default_text_settings.setColor(sf::Color::Black);
  default_text_settings.setStyle(sf::Text::Bold);
  default_text_settings.setCharacterSize(16);


  sf::Text title = default_text_settings;
  title.setCharacterSize(28);
  title.setStyle(sf::Text::Bold|sf::Text::Underlined); //not working right now
  title.setString("How to Play");
  title.setPosition(225,50);

  sf::Text line1 = default_text_settings;
  if(controltype == "keyboard") {
    line1.setString(std::string("Controls: You chose the KEYBOARD. Use the right and left arrow keys to turn."));
  } else if (controltype == "mouse") {
    line1.setString(std::string("Controls: You chose the MOUSE. Use the left and right mouse buttons to turn."));
  } else {
    //throw error
  }
  line1.setPosition(15,150);

  sf::Text line2 = default_text_settings;
  if(gametype == "survival") {
    line2.setString(std::string("Objective: You chose SURVIVAL mode.Try to survive as long as you can."));
  } else if (gametype == "endurance") {
    line2.setString(std::string("Objective: You chose ENDURANCE mode. Eat as many mice as you can."));
  } else {
    //throw error
  }
  line2.setPosition(15,200);

  sf::Text line3 = default_text_settings;
  if(gamespeed == "normal") {
    line3.setString(std::string("Speed: You chose NORMAL speed. A wise choice."));
  } else if (gamespeed == "fast") {
    line3.setString(std::string("Speed: You chose FAST speed. Good Luck."));
  } else {
    //throw error
  }
  line3.setPosition(15,250);

  sf::Text line4 = default_text_settings;
  line4.setCharacterSize(20);
  line4.setStyle(sf::Text::Bold);
  line4.setString("Click anywhere or press any key when you are ready to play!");
  line4.setPosition(20,350);


  //background
  sf::Texture bgtexture;
  if (!bgtexture.loadFromFile("grassbackground2.jpg",sf::IntRect(0,0,640,480))) {
  //error
  }
  sf::Sprite bgsprite;
  bgsprite.setTexture(bgtexture);

  game->window.clear(sf::Color::White);
  game->window.draw(bgsprite);
  game->window.draw(title);
  game->window.draw(line1);
  game->window.draw(line2);
  game->window.draw(line3);
  game->window.draw(line4);
  game->window.display();

}
