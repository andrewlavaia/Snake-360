

#include "gameengine.h"
#include "gamestate.h"
#include "menustate.h"
#include "highscorestate.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>


CHighScoreState CHighScoreState::m_HighScoreState;

void CHighScoreState::Init()
{

  std::cout << "High Score State started." << std::endl;
  std::cout<<"Reading in all scores." <<std::endl;

  std::ifstream file;
  file.open( "highscores.txt" );
  std::string s;

  std::vector <int> survival_normal_scores;
  std::vector <int> survival_fast_scores;
  std::vector <int> endurance_normal_scores;
  std::vector <int> endurance_fast_scores;

  while (std::getline(file, s, '\r').good()) {

    std::istringstream ss(s);
    std::string token;
    std::string gametype = "";
    std::string speed = "";
    std::string score = "";
    int score_int;

    while(std::getline(ss, token, ',')) {
      if( token.compare("survival") == 0 ) { gametype = token; }
      else if( token.compare("endurance") == 0) { gametype = token; }
      else if( token.compare("fast") == 0) { speed = token; }
      else if( token.compare("normal") == 0) { speed = token; }
      else { score = token;}
    }

    //convert score saved as string to int
    std::stringstream convert(score);
    if ( !(convert >> score_int) ) { //set to 0 if conversion fails
        score_int = 0;
    }

    //put scores into each respective vector
    if((gametype=="survival") && (speed=="normal")){
      this->m_survival_normal_scores.push_back(score_int);
    }
    if((gametype=="survival") && (speed=="fast")){
      this->m_survival_fast_scores.push_back(score_int);
    }
    if((gametype=="endurance") && (speed=="normal")){
      this->m_endurance_normal_scores.push_back(score_int);
    }
    if((gametype=="endurance") && (speed=="fast")){
      this->m_endurance_fast_scores.push_back(score_int);
    }

    std::cout<<"Gametype: "<<gametype<<". Speed: "<< speed <<". Score: "<< score_int << std::endl;

  } //end read file loop

  std::cout<<"All scores have been read in." <<std::endl;

  //sort vectors
  if(this->m_endurance_normal_scores.size() > 0) {
    sort(this->m_endurance_normal_scores.begin(), this->m_endurance_normal_scores.end());
  }
  if(this->m_endurance_fast_scores.size() > 0) {
    sort(this->m_endurance_fast_scores.begin(), this->m_endurance_fast_scores.end());
  }
  if(this->m_survival_normal_scores.size() > 0) {
    sort(this->m_survival_normal_scores.begin(), this->m_survival_normal_scores.end());
  }
  if(this->m_survival_fast_scores.size() > 0) {
    sort(this->m_survival_fast_scores.begin(), this->m_survival_fast_scores.end());
  }


}

void CHighScoreState::Cleanup()
{
  //Clear vectors so that they aren't duplicated everytime highscore screen is visited
  this->m_survival_normal_scores.clear();
  this->m_survival_fast_scores.clear();
  this->m_endurance_normal_scores.clear();
  this->m_endurance_fast_scores.clear();

  std::cout << "High Score State ended." << std::endl;
}

void CHighScoreState::Pause()
{

}

void CHighScoreState::Resume()
{

}

void CHighScoreState::HandleEvents(CGameEngine* game)
{
    sf::Event event;

    while (game->window.pollEvent(event)) {

      switch (event.type) {

        case sf::Event::Closed:
          game->window.close();
          game->Quit();
          break;

        case sf::Event::KeyPressed:
          game->PopState();
          break;

        case sf::Event::MouseButtonPressed:
          game->PopState();
          break;

        }

      }

}

void CHighScoreState::Update(CGameEngine* game)
{

}

void CHighScoreState::Draw(CGameEngine* game)
{
  //create sstreams to convert numbers to strings for output
  std::stringstream best_e_n_ss;
  std::stringstream best_e_f_ss;
  std::stringstream best_s_n_ss;
  std::stringstream best_s_f_ss;
  std::stringstream avg_e_n_ss;
  std::stringstream avg_e_f_ss;
  std::stringstream avg_s_n_ss;
  std::stringstream avg_s_f_ss;
  std::stringstream cnt_e_n_ss;
  std::stringstream cnt_e_f_ss;
  std::stringstream cnt_s_n_ss;
  std::stringstream cnt_s_f_ss;


  //Fetch all values
  if(this->m_endurance_normal_scores.size() > 0) {
    best_e_n_ss << this->m_endurance_normal_scores.back();
    double avg = std::accumulate(this->m_endurance_normal_scores.begin(),
                                 this->m_endurance_normal_scores.end(), 0.0) / this->m_endurance_normal_scores.size();
    avg_e_n_ss.precision(3);
    avg_e_n_ss << avg;
    cnt_e_n_ss << this->m_endurance_normal_scores.size();
  } else {
    best_e_n_ss << 0;
    avg_e_n_ss << 0;
    cnt_e_n_ss << 0;
  }

  if(this->m_endurance_fast_scores.size() > 0) {
    best_e_f_ss << this->m_endurance_fast_scores.back();
    double avg = std::accumulate(this->m_endurance_fast_scores.begin(),
                                 this->m_endurance_fast_scores.end(), 0.0) / this->m_endurance_fast_scores.size();
    avg_e_f_ss.precision(3);
    avg_e_f_ss << avg;
    cnt_e_f_ss << this->m_endurance_fast_scores.size();
  } else {
    best_e_f_ss << 0;
    avg_e_f_ss << 0;
    cnt_e_f_ss << 0;
  }

  if(this->m_survival_normal_scores.size() > 0) {
    best_s_n_ss << this->m_survival_normal_scores.back();
    double avg = std::accumulate(this->m_survival_normal_scores.begin(),
                                 this->m_survival_normal_scores.end(), 0.0) / this->m_survival_normal_scores.size();
    avg_s_n_ss.precision(3);
    avg_s_n_ss << avg;
    cnt_s_n_ss << this->m_survival_normal_scores.size();
  } else {
    best_s_n_ss << 0;
    avg_s_n_ss << 0;
    cnt_s_n_ss << 0;
  }

  if(this->m_survival_fast_scores.size() > 0) {
    best_s_f_ss << this->m_survival_fast_scores.back();
    double avg = std::accumulate(this->m_survival_fast_scores.begin(),
                                 this->m_survival_fast_scores.end(), 0.0) / this->m_survival_fast_scores.size();
    avg_s_f_ss.precision(3);
    avg_s_f_ss << avg;
    cnt_s_f_ss << this->m_survival_fast_scores.size();
  } else {
    best_s_f_ss << 0;
    avg_s_f_ss << 0;
    cnt_s_f_ss << 0;
  }


  //Set Default font and text settings
  sf::Font font;
  font.loadFromFile("arial.ttf");
  sf::Text default_text_settings;
  default_text_settings.setFont(font);
  default_text_settings.setColor(sf::Color::Black);
  default_text_settings.setStyle(sf::Text::Bold);
  default_text_settings.setCharacterSize(18);

  //Text for bests
  sf::Text best_e_n = default_text_settings;
  best_e_n.setString(best_e_n_ss.str());
  best_e_n.setPosition(185,165);

  sf::Text best_e_f = default_text_settings;
  best_e_f.setString(best_e_f_ss.str());
  best_e_f.setPosition(315,165);

  sf::Text best_s_n = default_text_settings;
  best_s_n.setString(best_s_n_ss.str());
  best_s_n.setPosition(445,165);

  sf::Text best_s_f = default_text_settings;
  best_s_f.setString(best_s_f_ss.str());
  best_s_f.setPosition(570,165);

  //Text for averages
  sf::Text avg_e_n = default_text_settings;
  avg_e_n.setString(avg_e_n_ss.str());
  avg_e_n.setPosition(175,245);

  sf::Text avg_e_f = default_text_settings;
  avg_e_f.setString(avg_e_f_ss.str());
  avg_e_f.setPosition(305,245);

  sf::Text avg_s_n = default_text_settings;
  avg_s_n.setString(avg_s_n_ss.str());
  avg_s_n.setPosition(435,245);

  sf::Text avg_s_f = default_text_settings;
  avg_s_f.setString(avg_s_f_ss.str());
  avg_s_f.setPosition(560,245);

  //Text for counts
  sf::Text cnt_e_n = default_text_settings;
  cnt_e_n.setString(cnt_e_n_ss.str());
  cnt_e_n.setPosition(185,325);

  sf::Text cnt_e_f = default_text_settings;
  cnt_e_f.setString(cnt_e_f_ss.str());
  cnt_e_f.setPosition(315,325);

  sf::Text cnt_s_n = default_text_settings;
  cnt_s_n.setString(cnt_s_n_ss.str());
  cnt_s_n.setPosition(445,325);

  sf::Text cnt_s_f = default_text_settings;
  cnt_s_f.setString(cnt_s_f_ss.str());
  cnt_s_f.setPosition(570,325);

  //background
  sf::Texture bgtexture;
  if (!bgtexture.loadFromFile("highscorebg.jpg",sf::IntRect(0,0,640,480))) {
  //error
  }
  sf::Sprite bgsprite;
  bgsprite.setTexture(bgtexture);

  game->window.clear(sf::Color::White);
  game->window.draw(bgsprite);
  game->window.draw(best_e_n);
  game->window.draw(best_e_f);
  game->window.draw(best_s_n);
  game->window.draw(best_s_f);
  game->window.draw(avg_e_n);
  game->window.draw(avg_e_f);
  game->window.draw(avg_s_n);
  game->window.draw(avg_s_f);
  game->window.draw(cnt_e_n);
  game->window.draw(cnt_e_f);
  game->window.draw(cnt_s_n);
  game->window.draw(cnt_s_f);

  game->window.display();

}
