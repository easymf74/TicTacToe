/// @file ki.hpp

#ifndef KI_HPP
#define KI_HPP KI_HPP
#include <array>
#include <vector>
class Ki {
public:
  static const int INF    = 100;
  static const int KI     =   1;
  static const int HUM    =   2;
  static const int WIN    =  11;
  static const int TIE    =  10;
  static const int GO     =   0;
  static const int LOOSE  =  -1;
  static const int RESET  =   0;

  unsigned int leafnotes;
  
  struct Move{
    unsigned int x=2;
    unsigned int y=0;
    int value=-9;
  };
  
  Ki();
  void init();
  void set_player_move
  (
    unsigned int x,
    unsigned int y
    );
  Move make_move();
private:
  std::array<std::array<unsigned int,3>,3> grid;

  std::vector<Move>
  get_possible_moves
  (
    const
    std::array<std::array<unsigned int,3>,3>
    &field
    ) const;

  Move sim_ki_turn
  (int alpha, int beta);

  Move sim_human_turn
  (int alpha, int beta);

  int score() const;

};

#endif //KI_HPP
