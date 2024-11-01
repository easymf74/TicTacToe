// app.cpp

#include "app.hpp"

bool MyApp::OnInit()
{
  wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
  frame = new wxFrame(
    (wxFrame *)NULL,
    -1,
    wxT("Tic Tac Toe"),
    wxPoint(500,100),
    wxSize(SIZE,SIZE+title_height)
    );
  
  game = new TicTacToe( (wxFrame*) frame, SIZE);
  sizer->Add(game, 1, wxEXPAND);
	
  frame->SetSizer(sizer);
  frame->SetAutoLayout(true);
	
  frame->Show();
  return true;
} 
