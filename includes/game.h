
#include <sys/time.h>
#include <ncurses.h>

#include "form.h"

#define FRAMERATE 30
#define SCREEN_HEIGHT 50
#define SCREEN_WIDTH 80
#define POINT_HEIGHT 2
#define POINT_WIDTH 3
#define MAP_HEIGHT ((SCREEN_HEIGHT - 2) / POINT_HEIGHT)
#define MAP_WIDTH ((SCREEN_WIDTH - 2) / POINT_WIDTH)
#define INITIAL_MOVE_STEP 0.8f;
typedef struct	s_game
{
  WINDOW*		win;
  int			exit;
  char			fixedScreen[MAP_HEIGHT][MAP_WIDTH];
  form*			currentForm;
  int			posX;
  int			posY;
  struct timeval	lastUpdate;
  float			currentMoveStep;
}			game;

game*	new_game();
void	destroy_game(game* this);

void	game_init(game* this);
void	game_launch(game* this);

