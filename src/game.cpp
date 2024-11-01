// draw.cpp

#include "game.hpp"

void TicTacToe::adjust_size(){
  square_size = size / 3;
  boarder_size = size / 100;
}

void TicTacToe::init(){
  square_size = size / 3;
  boarder_size = size / 100;
  for(unsigned int i=0;i<3;++i)
    for(unsigned int j=0;j<3;++j)
      grid[i][j]=FREE;
  ready=false;
  moves=9;
  int replay = wxMessageBox("Do you want to begin?","Who begins?",wxYES_NO,this);
  if(replay == wxYES){
    player=1;
  } else {
    player = 0;
  }
}


void TicTacToe::ki_move(){
  if(ready) return;
  Ki::Move m = ki.make_move();
  grid[m.x][m.y] = player;
  std::cout << "Ki plays field " << m.x << ',' << m.y << ": " << m.value << std::endl;
  move_result();
};

TicTacToe::TicTacToe(wxFrame* parent, unsigned int size)
  :wxPanel(parent),size(size) {
  adjust_size();
  init();
  if(!player) ki_move();
  Bind(wxEVT_LEFT_DOWN,&TicTacToe::mouseKlick,this);
  Bind(wxEVT_PAINT,&TicTacToe::paintEvent,this);
  Bind(wxEVT_SIZE,&TicTacToe::onResize,this);
  Bind(wxEVT_RIGHT_DOWN,&TicTacToe::rightKlick,this);
}

void TicTacToe::rightKlick(wxMouseEvent& event){
  wxUnusedVar(event);
  int replay = wxMessageBox("Do you want to play again?","Replay?",wxYES_NO,this);
  if(replay == wxYES){
    reset();
  }
    
}

void TicTacToe::onResize(wxSizeEvent &evt){
  size = evt.GetSize().GetHeight();
  if((unsigned int)evt.GetSize().GetWidth() < size)
    size = evt.GetSize().GetWidth();
  adjust_size();
  paintNow();
}


/*
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */
void TicTacToe::paintEvent(wxPaintEvent & evt)
{
    wxPaintDC dc(this);
    render(dc);
}

void TicTacToe::paintNow()
{
    wxClientDC dc(this);
    render(dc);
}


/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */
void TicTacToe::render(wxDC&  dc)
{
  // draw a Grid
  dc.SetBrush(*wxWHITE_BRUSH); // white filling
  dc.SetPen( wxPen( wxColor(0,0,0), boarder_size ) ); 
  for(unsigned int row=0;row<3;++row)
    for (unsigned int col = 0; col < 3; ++col) {
      dc.DrawRectangle(row*square_size, col*square_size, square_size, square_size);
    }
  for(unsigned int row = 0;row<3;++row)
    for(unsigned int col=0;col<3;++col)
      if(grid[row][col] < 2)
	 drawFigure(dc, col+row*3, grid[row][col]);
}

void TicTacToe::reset(){
  init();
  ki.init();
  if (!player) {
    ki_move();
    paintNow();
  }
}


void TicTacToe::move_result(){
  std::array<std::string,2> names = {"Red","Blue"};
  int replay=-1;
  wxString msg;
  if (check_win()) {
    std::cout << "Player " << names[player] << " wins!" << std::endl;
    ready = true;
    msg = "Player ";
    msg += names[player];
    msg += " wins!\nDo you want to play again?";
    replay = wxMessageBox(msg,"Replay?",wxYES_NO,this);
    if(replay == wxYES){
      reset();
  }
  }else if(!--moves){
    std::cout << "Tie - Nobody wins!" << std::endl;
    ready = true;
    msg = "Tie - Nobody wins! \nDo you want to play again?";
    replay = wxMessageBox(msg,"Replay?",wxYES_NO,this);
    if(replay == wxYES){
      reset();
    } 
  }else {
    player =!player;
    if(!player) ki_move();
  }

   paintNow();
}

void TicTacToe::mouseKlick(wxMouseEvent& event){
  if(ready) return;
  unsigned int x = event.GetX();
  unsigned int y = event.GetY();
  if(x>=3*square_size || y>=3*square_size) return;
  x =  x / square_size;
  y =  y / square_size;
  if(grid[y][x] != FREE) return;
  grid[y][x] = player;
  ki.set_player_move(y, x);
  move_result();
}

bool TicTacToe::same_player_on(unsigned int a, unsigned int b, unsigned int c){
  return
    a != 3
    &&
    a == b
    &&
    a ==c;
}

bool TicTacToe::check_win(){
  bool result = false;
  for(unsigned int rc = 0; rc<3 && !result; ++rc)
    result =
      same_player_on(grid[rc][0], grid[rc][1], grid[rc][2])
      ||
      same_player_on(grid[0][rc], grid[1][rc], grid[2][rc]);
  result = result
    ||
    same_player_on(grid[0][0],grid[1][1],grid[2][2])
    ||
    same_player_on(grid[0][2], grid[1][1], grid[2][0]);
  return result;
}

void TicTacToe::drawFigure(wxDC&  dc, unsigned int position,unsigned int who){

  const std::array<const wxBrush,2> player = {*wxRED_BRUSH,*wxBLUE_BRUSH};
  unsigned int row = (position/3+0.5)*square_size;
  unsigned int col = (position%3+0.5)*square_size;
  dc.SetBrush(player[who]); // filling with playercolor
  dc.SetPen( wxPen( wxColor(0,100,0), boarder_size ) ); 
  dc.DrawCircle( wxPoint(col,row), square_size/3 /* radius */ );
}
