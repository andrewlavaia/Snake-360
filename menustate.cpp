

#include "gameengine.h"
#include "gamestate.h"
#include "menustate.h"
#include "introstate.h"
#include "highscorestate.h"
#include <iostream>


CMenuState CMenuState::m_MenuState;

void CMenuState::Init()
{

std::cout << "Menu State started." << std::endl;

}

void CMenuState::Cleanup()
{
  std::cout << "Menu State ended." << std::endl ;
}

void CMenuState::Pause()
{

}

void CMenuState::Resume()
{

}

void CMenuState::HandleEvents(CGameEngine* game)
{
    sf::Event event;

    while (game->window.pollEvent(event)) {

      switch (event.type) {

        case sf::Event::Closed:
          game->window.close();
          game->Quit();
          break;

        case sf::Event::KeyPressed:
          if (event.key.code == sf::Keyboard::Space) {
              game->PushState( CIntroState::Instance() );
          }

        case sf::Event::MouseMoved:
          if(event.mouseMove.x >= 20 && event.mouseMove.x <= 70 &&
             event.mouseMove.y >= 171 && event.mouseMove.y <= 221) {
                game->m_ControlMode.setControlType("keyboard");
          }

          if(event.mouseMove.x >= 120 && event.mouseMove.x <= 170 &&
             event.mouseMove.y >= 171 && event.mouseMove.y <= 221) {
                game->m_ControlMode.setControlType("mouse");
          }

          if(event.mouseMove.x >= 20 && event.mouseMove.x <= 70 &&
             event.mouseMove.y >= 291 && event.mouseMove.y <= 341) {
                game->m_GameMode.setGameType("endurance");
          }

          if(event.mouseMove.x >= 120 && event.mouseMove.x <= 170 &&
             event.mouseMove.y >= 291 && event.mouseMove.y <= 341) {
                game->m_GameMode.setGameType("survival");
          }

          if(event.mouseMove.x >= 20 && event.mouseMove.x <= 70 &&
             event.mouseMove.y >= 411 && event.mouseMove.y <= 461) {
                game->m_GameMode.setGameSpeed(.20);
          }

          if(event.mouseMove.x >= 120 && event.mouseMove.x <= 170 &&
             event.mouseMove.y >= 411 && event.mouseMove.y <= 461) {
                game->m_GameMode.setGameSpeed(.30);
          }

          if(event.mouseMove.x >= 303 && event.mouseMove.x <= 513 &&
             event.mouseMove.y >= 355 && event.mouseMove.y <= 406) {
                hoverflag = 1; //play button hovered
          } else if(event.mouseMove.x >= 303 && event.mouseMove.x <= 513 &&
             event.mouseMove.y >= 427 && event.mouseMove.y <= 472) {
                hoverflag = 2; //high score button hovered
          } else {
                hoverflag = 0;
          }

        case sf::Event::MouseButtonPressed:
          if(event.mouseButton.button == sf::Mouse::Left) {
            switch (hoverflag) {
              case 0:
                break;
              case 1:
                game->PushState( CIntroState::Instance() );
                break;
             case 2:
                game->PushState( CHighScoreState::Instance() );
                break;

            }
          }

      }//end event switch
    }//end window->pollEvent
} //end CMenuState::HandleEvents

void CMenuState::Update(CGameEngine* game)
{

}

void CMenuState::Draw(CGameEngine* game)
{

  sf::Texture texture;
  if (!texture.loadFromFile("titlescreen.jpg", sf::IntRect(0,0,640,480))) {
      //error
  }
  sf::Sprite menusprite;
  menusprite.setTexture(texture);


  sf::RectangleShape controlshape(sf::Vector2f(50, 50));
  controlshape.setPosition(20,171);
  controlshape.setOutlineThickness(5);
  controlshape.setOutlineColor(sf::Color(250, 150, 100));
  controlshape.setFillColor(sf::Color::Transparent);
  if(game->m_ControlMode.getControlType() == "mouse") {
      controlshape.setPosition(120,171);
  }


  sf::RectangleShape modeshape = controlshape; //copy shape
  modeshape.setPosition(20,291);
  if(game->m_GameMode.getGameType() == "survival") {
      modeshape.setPosition(120,291);
  }

  sf::RectangleShape speedshape = controlshape; //copy shape
  speedshape.setPosition(20,411);
  if(game->m_GameMode.getGameSpeed() == .30 ) {
      speedshape.setPosition(120,411);
  }

  sf::RectangleShape playshape = controlshape; //copy shape
  playshape.setSize(sf::Vector2f(210, 45));
  playshape.setPosition(303,355);
  playshape.setOutlineColor(sf::Color::Transparent);
  if(hoverflag == 1) {
    playshape.setPosition(303,355);
    playshape.setOutlineColor(sf::Color(7, 151, 223));
  }
  if(hoverflag == 2) {
    playshape.setPosition(303,415);
    playshape.setOutlineColor(sf::Color(7, 151, 223));
  }



  game->window.clear(sf::Color::White);
  game->window.draw(menusprite);
  game->window.draw(controlshape);
  game->window.draw(modeshape);
  game->window.draw(speedshape);
  game->window.draw(playshape);
  game->window.display();

}
