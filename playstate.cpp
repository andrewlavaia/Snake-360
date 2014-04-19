
#include "gamestate.h"
#include "gameengine.h"
#include "playstate.h"
#include "menustate.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp> // OpenGL for antialiasing?
#include <Windows.h> //GetTickCount()
#include <math.h> //sin and cos
#include <random> //random generator
#include <queue>
#include <deque>
#include <vector>
#include <iostream>
#include <string>
#include <sstream> //used in int to string conversion
#include <fstream>



CPlayState CPlayState::m_PlayState;

void CPlayState::Init()
{
  std::cout << "Play State started." << std::endl ;

}

void CPlayState::Cleanup()
{

  std::cout << "Play State ended." << std::endl ;

}

void CPlayState::Pause()
{

}

void CPlayState::Resume()
{

}

void CPlayState::HandleEvents(CGameEngine* game)
{
    sf::Event event;
    while (game->window.pollEvent(event))
    {
      switch (event.type)
      {
        case sf::Event::Closed:
          game->window.close();
          game->Quit();
          break;
      }
    }
}

void CPlayState::Update(CGameEngine* game)
{
  sf::Vector2u window_size = game->window.getSize();

	//System Constants
  unsigned WINDOW_WIDTH = window_size.x;
  unsigned WINDOW_HEIGHT = window_size.y;
  unsigned FPS = 60;
  double PI = 3.14159265;

  //Window Settings
  /*
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Runner", sf::Style::Default, settings);
  window.setVerticalSyncEnabled(true);
  */

  sf::RenderWindow& window = game->window;

  double lastFrameTimeStamp = GetTickCount(); // GetTickCount is for Windows only
  double frame_length = 1000/FPS;

  //random generator
  std::default_random_engine rand_generator;
  rand_generator.seed(time(0)); // seed will only change once per second
  std::uniform_int_distribution<unsigned> random_x(25,WINDOW_WIDTH-25);
  std::uniform_int_distribution<unsigned> random_y(25,WINDOW_HEIGHT-25);


//-----------------------------------
  //LOAD SOUND FILES

  sf::SoundBuffer buffer;
  if (!buffer.loadFromFile("eat.wav")) {
    //error loading file
  }
  sf::Sound eatsound;
  eatsound.setBuffer(buffer);
  eatsound.setVolume(30);

  sf::SoundBuffer buffer2;
  if (!buffer2.loadFromFile("gameover.wav")) {
    //error loading file
  }
  sf::Sound gameoversound;
  gameoversound.setBuffer(buffer2);
  gameoversound.setVolume(30);


//-----------------------------------
  //LOAD FONT AND TEXT

  //Set Default font and text settings
  sf::Font font;
  font.loadFromFile("arial.ttf");
  sf::Text default_text_settings;
  default_text_settings.setFont(font);
  default_text_settings.setColor(sf::Color(254,255,221,100));
  default_text_settings.setStyle(sf::Text::Bold);
  default_text_settings.setCharacterSize(24);

  sf::Text displayscore = default_text_settings;
  displayscore.setPosition(500,50);

//--------------------------------------
  //INITIALIZE GAME OBJECTS

  //game variables
  bool collision = false;
  bool game_running = true;
  double snake_speed = game->m_GameMode.getGameSpeed();
  std::string gamespeed = "normal";
  unsigned directional_speed = 10;
  double hitbox = 2.2;
  unsigned score = 0;
  if(game->m_GameMode.getGameSpeed() == .30) {
      gamespeed = "fast";
      directional_speed = 15;
      hitbox = 3.3;
  }

  //snake
  unsigned snake_width = 10;
  unsigned snake_height = 10;
  int snake_length = 0;
  float snake_direction = 0;
  sf::Vector2f snake_coord;

  //snake head
  sf::RectangleShape snake(sf::Vector2f(snake_width*2, snake_height*2));
  snake.setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
  snake.setOrigin(snake_width, snake_height);

  //snake head
  sf::Texture snakehead;
  if (!snakehead.loadFromFile("snake_head.gif")) {
                // error...
  }
  snakehead.setSmooth(true);
  snake.setTexture(&snakehead);

  //snake skin
  sf::Texture snaketexture;
  if (!snaketexture.loadFromFile("snake_skin.gif")) {
                // error...
  }
  snaketexture.setSmooth(true);
  //snake.setTexture(&snaketexture);

  //snake body
  std::deque<sf::RectangleShape> snake_body{};
  sf::Vector2f snake_body_coord;

  //store past snake coordinates
  std::queue<sf::Vector2f> snake_history;

  //food
  sf::RectangleShape food(sf::Vector2f(6, 6));
  food.setFillColor(sf::Color(255,153,0));
  food.setPosition(random_x(rand_generator), random_y(rand_generator));
  sf::Vector2f food_coord;

  //background
  sf::Texture bgtexture;
  if (!bgtexture.loadFromFile("grassbackground2.jpg",sf::IntRect(0,0,640,480))) {
  //error
  }
  sf::Sprite bgsprite;
  bgsprite.setTexture(bgtexture);


//---------------------------------------



  //GAME LOOP

    while(game_running)
    {
      double currentTimeStamp = GetTickCount();
      if(currentTimeStamp - lastFrameTimeStamp >= frame_length)
      {

        //EVENT HANDLER
        sf::Event event;
        while (window.pollEvent(event))
        {
          switch (event.type)
          {
            case sf::Event::Closed:
              window.close();
              game->Quit();
              break;
          }
        }

        //USER INPUT HANDLER
        if(game->m_ControlMode.getControlType() == "keyboard") {
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            snake_direction -= directional_speed;// move left
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            snake_direction += directional_speed; // move right
          }
        }

        if(game->m_ControlMode.getControlType() == "mouse") {
          if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            snake_direction -= directional_speed; // move left
          }
          if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            snake_direction += directional_speed;// move right
          }
        }


        //GAME LOGIC

        //store past coordinates
        snake_coord = snake.getPosition();
        snake_history.push(snake_coord);

        //limit size of history queue so it doesn't grow too large
        if (snake_history.size() > snake_length + 10)
        {
          snake_history.pop();
        }

        //Create new snake shape
        sf::RectangleShape snake_temp(sf::Vector2f(snake_width, snake_height));
        //snake_temp.setFillColor(sf::Color(128,128,0));
        snake_temp.setPosition(snake_history.back());
        snake_temp.setOrigin(snake_width/2, snake_height/2);
        snake_temp.setTexture(&snaketexture);

        //Add new temporary snake shape to vector
        snake_body.push_back(snake_temp);

        //remove oldest snake shape from snake body if snake did not grow
        if(snake_body.size() > snake_length)
        {
          snake_body.pop_front();
        }

        //change snake head angle
        snake.setRotation(snake_direction);

        //move snake head forward
        snake.move((snake_speed * frame_length)*sin(snake_direction * PI / 180),
                   (snake_speed * frame_length)*-cos(snake_direction * PI / 180));


        //check if snake hit edge of window
        snake_coord = snake.getPosition();
        if(snake_coord.x - snake_width < 0)
        {
          std::cout<< "Game Over: left edge hit" << std::endl;
          collision = true;
        }
        if(snake_coord.y - snake_height < 0)
        {
          std::cout<< "Game Over: top edge hit" << std::endl;
          collision = true;
        }
        if(snake_coord.x + snake_width > WINDOW_WIDTH)
        {
          std::cout<< "Game Over: right edge hit" << std::endl;
          collision = true;
        }
        if(snake_coord.y + snake_height> WINDOW_HEIGHT)
        {
          std::cout<< "Game Over: bottom edge hit" << std::endl;
          collision = true;
        }

        //SURVIVAL GAME MODE
        if(game->m_GameMode.getGameType() == "survival") {
          snake_length++;
        }

        //check if snake ate food
        snake_coord = snake.getPosition();
        food_coord = food.getPosition();

        if ((snake_coord.x <= food_coord.x + snake_width) &&
            (snake_coord.x >= food_coord.x - snake_width) &&
            (snake_coord.y <= food_coord.y + snake_height) &&
            (snake_coord.y >= food_coord.y - snake_height))
        {
          food.setPosition(random_x(rand_generator), random_y(rand_generator));
          snake_length += 5;
          eatsound.play();
          score++;
        }

        //check for snake head and snake body collision
        for(std::deque<sf::RectangleShape>::size_type i = 0; i != snake_body.size(); i++) {
          snake_body_coord = snake_body[i].getPosition();


          if ((snake_coord.x <= snake_body_coord.x + hitbox) &&
              (snake_coord.x >= snake_body_coord.x - hitbox) &&
              (snake_coord.y <= snake_body_coord.y + hitbox) &&
              (snake_coord.y >= snake_body_coord.y - hitbox))   {
                  std::cout << "Game Over: Collision with body piece: #" << i << std::endl;
                  collision = true;
                  break;
          }
        }

        //GAME OVER CONDITION
        if (collision) {
          gameoversound.play();

          //Store the score in the file
          std::ofstream file;
          file.open ("highscores.txt", std::ios_base::app | std::ios_base::out);
          file << game->m_GameMode.getGameType() << "," << gamespeed << "," << score << "\r";
          file.close();

          Sleep(1000);
          game_running = false;
          game->PopState();
          game->PopState();
          break;
        }

        std::ostringstream ss;
        ss << score;
        displayscore.setString( std::string( "Score: "+ss.str() ) );

        //RENDER
        window.clear();

        window.draw(bgsprite);

        for(std::deque<sf::RectangleShape>::size_type i = snake_body.size(); i != 0; --i) {
          window.draw(snake_body[i-1]); //i != vector.size
        }
        window.draw(snake); //head drawn after body so it is on top
        window.draw(food);
        window.draw(displayscore);
        window.display();

        lastFrameTimeStamp = currentTimeStamp;

        //DEBUG
        //std::cout << snake_body.size();

      }

      Sleep(1); // saves some cpu

    } //end core game loop

}

void CPlayState::Draw(CGameEngine* game)
{





}

