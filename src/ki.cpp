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
  int alpha = -INF;
  int beta  =  INF;

  leafnotes = 0;
  Move best_move = sim_ki_turn(alpha, beta);
  grid[best_move.x][best_move.y] = KI; 

  return best_move;
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


Ki::Move Ki::sim_ki_turn(int alpha, int beta){
  int value = -INF;
  Move best;
  best.value = score(); // score the turn the human made
  if(best.value == WIN) best.value = LOOSE;

  // basecase
  if(best.value && ++leafnotes)
    return best;

  std::vector<Move> possible_moves = get_possible_moves(grid);

  for(const Move &move : possible_moves){
    grid[move.x][move.y] = KI;
    Move human_move = sim_human_turn(alpha, beta);
    grid[move.x][move.y] = RESET;

    // rank faster wins higher 
    if(human_move.value == WIN)
      human_move.value += possible_moves.size();

    //rank faster draws lower
    if(human_move.value == TIE)
      human_move.value -= possible_moves.size();

    // rank faster flops lower
    if(human_move.value == LOOSE)
      human_move.value -= possible_moves.size();
    
    if(human_move.value > value){
      value = human_move.value;
      best = {move.x, move.y, value};
    }
    
    if(human_move.value >= beta)
      break; // beta-cutoff skip other moves with same level

    if(human_move.value > alpha)
      alpha = human_move.value;
    
  }// end for all possible moves
    
  return best;
};

Ki::Move Ki::sim_human_turn(int alpha, int beta){
  int value = INF;
  Move low;
  low.value = score();// score the turn the ki made
  
  // basecase
  if( low.value && ++leafnotes)
    return low;

  std::vector<Move> possible_moves = get_possible_moves(grid);
  for(Move move : possible_moves){
    grid[move.x][move.y] = HUM;
    Move ki_move = sim_ki_turn(alpha, beta);
    grid[move.x][move.y] = RESET;

    if(ki_move.value < value){
      value = ki_move.value;
      low = {move.x,move.y,value};
    }

    if(ki_move.value <= alpha)
      break; // alpha-cutoff skip other moves with same level

    if (ki_move.value < beta)
      beta = ki_move.value;
    
  }// end for all possible moves
  
  return low;
}

int Ki::score() const{

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
};

