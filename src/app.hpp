/// @file app.hpp

#ifndef APP_HPP
#define APP_HPP APP_HPP

#include "game.hpp"

class MyApp: public wxApp
{
  bool OnInit();
  wxFrame *frame;
  TicTacToe * game;

  //____________
  const unsigned int SIZE = 400;
  const unsigned int title_height = 20;
};

#endif //APP_HPP
