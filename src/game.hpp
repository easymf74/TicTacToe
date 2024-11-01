/// @file draw.hpp

#ifndef DRAW_HPP
#define DRAW_HPP DRAW_HPP

#include "wx/wx.h"
#include "ki.hpp"
#include <array>

class TicTacToe : public wxPanel
{
    
public:
  TicTacToe(wxFrame* parent, unsigned int size);
private:
  Ki ki;
  void ki_move();
  void adjust_size();
  void init();
  void reset();
  void move_result();
  bool check_win();
  bool same_player_on(
    unsigned int a,
    unsigned int b,
    unsigned int c);
  void paintEvent(wxPaintEvent & evt);
  void paintNow();
  void onResize(wxSizeEvent &evt);
  void render(wxDC& dc);
  void rightKlick(wxMouseEvent& event);
  void mouseKlick(wxMouseEvent& event);
  const unsigned int FREE = 3;
  unsigned int size;
  unsigned int square_size;
  unsigned int boarder_size;
  bool ready = false;
  unsigned int moves=9;
  void drawFigure(wxDC&,unsigned int position,unsigned int player);
  bool player=0;
  std::array<std::array<unsigned int,3>,3> grid;
};

#endif //DRAW_HPP
