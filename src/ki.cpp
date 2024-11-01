// ki.cpp

#include "ki.hpp"

Ki::Ki(){
  init();
}

void Ki::init(){
  for(unsigned int i=0;i<3;++i)
    for(unsigned int j=0;j<3;++j)
      grid[i][j] = 0;
}

void Ki::set_player_move(unsigned int x, unsigned int y){
  grid[x][y] = HUM;
}

Ki::Move Ki::make_move(){
  int alpha = -9;
  int beta  =  9;
  
  Move m = max(grid, alpha, beta);
  grid[m.x][m.y] = KI; 

  return m;
}

std::vector<Ki::Move>
Ki::get_possible_moves
(const std::array<std::array<unsigned int,3>,3> &field) const{
  const unsigned int POSSIBLE = 0;
  std::vector<Move> possible_moves;
  for(unsigned int x =0;x<3;++x)
    for(unsigned int y=0;y<3;++y)
      if(field[x][y] == POSSIBLE)
        possible_moves.push_back({x, y});

  return possible_moves;     
}


Ki::Move Ki::max(
  std::array<std::array<unsigned int,3>,3> &field,
  int alpha,
  int beta
  ) const{
  int value=-9;
  Move m;
  
  std::vector<Move> possible_moves = get_possible_moves(field);

  for( Move move : possible_moves){
    //auto new_field = field; // reset the move in the same level

    /*  Game over?
	0: NO
	1: TIE
	2: WIN
     */
    int result = game_over(field,KI,move);
    if(result){ // Basecase TIE::1 or WIN::2
      field[move.x][move.y] = 0;
      if (result > value){ 
	value = result; 
	m = move; 
	m.value = value; 
      }
      if (result >= beta) 
        break; // beta-cutoff
      if(result > alpha) alpha = result;
    }// end basecase
    else{ // no basecase
      Move d = min(field, alpha, beta);
      field[move.x][move.y] = 0;
      if (d.value > value) { 
        value = d.value; 
	m = move; 
	m.value = d.value;
      }
      if (d.value >= beta) 
        break; // beta-cutoff : try no other move on this level
     
      if (value > alpha)
	alpha = value;
      } // end not base condition
  }// end for all possible moves

  return m;
}

Ki::Move Ki::min(
  std::array<std::array<unsigned int,3>,3> &field,
  int alpha,
  int beta
  ) const{
  int value = 9;
  Move m;
  
  std::vector<Move> possible_moves = get_possible_moves(field);

  for( Move move : possible_moves){
    int result = game_over(field,HUM,move);
    
    if(result){
      field[move.x][move.y] = 0;
      // basecase
      // if result=WIN::2: we loose = least case
      if(result == 2) result = -1;
      if (result < value){
	value = result;
	m = move;
	m.value = value;
      }
      if (result <= alpha) 
        break; // alpha-cutoff
      
      if( result < beta) beta = result;
    }// end basecase
    else{ // no basecae
      Move u = max(field, alpha, beta);
      field[move.x][move.y] = 0;
      if (u.value < value) {
        value = u.value;
	m = move;
	m.value = u.value;
      }
      if (u.value <= alpha) 
        break; // alpha-cutoff
      
      if (value < beta)
	beta = value;
      } // end not base condition

  }// end for all possible moves
  return m;
}

int Ki::game_over(
    std::array<std::array<unsigned int,3>,3> &grid,
    int player,
    const Move& move
  ) const{
  
  const int GO     =  0;
  const int TIE    =  1;
  const int WIN    =  2;
  grid[move.x][move.y] = player;

  for(unsigned int i = 0; i<3;++i)
    if(
      (
	grid[0][i] != 0
	&&
	grid[0][i] == grid[1][i]
	&&
	grid[0][i] == grid[2][i]
	)
      ||
      (
	grid[i][0] !=0
	&&
	grid[i][0] == grid[i][1]
	&&
	grid[i][0] == grid[i][2]
	)) return WIN;
  
  if(
    
    grid[1][1] != 0
    &&
    (
      (
	grid[0][0] == grid[1][1]
	&&
	grid[0][0] == grid[2][2]
	)
      ||
      (
	grid[0][2] == grid[1][1]
	&&
	grid[0][2] == grid[2][0]
	)
      
      )

    ) return WIN;

  for(unsigned int i =0;i<3;++i)
    for(unsigned int j =0;j<3;++j)
      if(!grid[i][j]) return GO;
  
  return TIE;
}
