/// @file ki.hpp

#ifndef KI_HPP
#define KI_HPP KI_HPP
#include <array>
#include <vector>
class Ki {
public:
  static const int KI=1;
  static const int HUM=2;
  
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

  Move max(
    std::array<std::array<unsigned int,3>,3> &field,
    int alpha,
    int beta
    ) const;

  Move min(
    std::array<std::array<unsigned int,3>,3> &field,
    int alpha,
    int beta
    ) const;
  
  int game_over(
    std::array<std::array<unsigned int,3>,3>&,
    int,
    const Move&
    ) const;
};

#endif //KI_HPP
