
#include "game.h"

int main()
{
  game* g = new_game();

  game_init(g);

  game_launch(g);

  destroy_game(g);
  return 0;
}
