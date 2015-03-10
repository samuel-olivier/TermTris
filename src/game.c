
#include "game.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	game_update(game* this);
void	game_draw(game* this);
int	game_canMoveForm(game* game, form* form, int x, int y);
void	game_drawCell(game* this, int posX, int posY, char c);
void	game_generateNewForm(game* this);
int	game_applyFormTranslation(game* this, int x, int y);
void	game_moveFormToBottom(game* this);
void	game_removeCompleteLines(game* this);
void	game_removeLine(game* this, int y);

game*   new_game() {
  game*	this = malloc(sizeof(*this));

  memset(this, 0, sizeof(*this));
  return this;
}

void    destroy_game(game* this)
{
  delwin(this->win);
  endwin();
  free(this);
}

void    game_init(game* this)
{
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  halfdelay(5);
  this->win = newwin(SCREEN_HEIGHT, SCREEN_WIDTH, 0, 0);
  memset(this->fixedScreen, 0, sizeof(this->fixedScreen));
  this->exit = 0;
  this->currentMoveStep = INITIAL_MOVE_STEP;
}

void    game_launch(game* this)
{
  gettimeofday(&this->lastUpdate, NULL);
  while (this->exit == 0) {
    game_update(this);
    game_draw(this);
  }
}

void	game_update(game* this)
{
  int			ch = getch();
  struct timeval	now;  
  float			lastUpdate;

  if (this->currentForm == NULL) {
    game_generateNewForm(this);
  }
  if (ch == KEY_F(1))
    this->exit = 1;
  int x = 0, y = 0;
  gettimeofday(&now, NULL);
  switch (ch) {
  case KEY_LEFT:
    --x;
    break;
  case KEY_RIGHT:
    ++x;
    break;
  case KEY_UP:
    game_moveFormToBottom(this);
    break;
  case KEY_DOWN:
    y++;
    this->lastUpdate = now;
    break;
  case 'a':
    form_rotate(this->currentForm);
    break;
  }
  game_applyFormTranslation(this, x, y);

  lastUpdate = now.tv_sec - this->lastUpdate.tv_sec + ((float)(now.tv_usec - this->lastUpdate.tv_usec) / 1000000);
  if (lastUpdate > this->currentMoveStep) {
    this->lastUpdate = now;
    game_applyFormTranslation(this, 0, 1);    
  }
}

void	game_draw(game* this)
{
  wclear(this->win);
  wborder(this->win, '|', '|', '-', '-', '*', '*', '*', '*');
  for (int i = 0; i < 4; ++i) {
    game_drawCell(this, this->posX + this->currentForm->points[i][0],
		  this->posY + this->currentForm->points[i][1],
		  this->currentForm->type);
  }
  for (int y = 0; y < MAP_HEIGHT; ++y) {
    for (int x = 0; x < MAP_WIDTH; ++x) {
      if (this->fixedScreen[y][x] != 0) {
	game_drawCell(this, x, y, this->fixedScreen[y][x]);
      }
    }
  }
  wrefresh(this->win);
}

int	game_canMoveForm(game* this, form* form, int x, int y)
{
  for (int i = 0; i < 4; ++i) {
    int newX = x + form->points[i][0];
    int newY = y + form->points[i][1];

    if (newX < 0 || newY < 0 || newX >= MAP_WIDTH || newY >= MAP_HEIGHT ||
	this->fixedScreen[newY][newX] != 0) {
      return 0;
    }
  }
  return 1;
}

void	game_drawCell(game* this, int posX, int posY, char c)
{
  if (posX < 0 || posX >= MAP_WIDTH || posY < 0 || posY >= MAP_HEIGHT) {
    return ;
  }
  for (int x = 0; x < POINT_WIDTH; ++x) {
    for (int y = 0; y < POINT_HEIGHT; ++y) {
      mvwaddch(this->win, posY * POINT_HEIGHT + y + 1,
	       posX * POINT_WIDTH + x + 1, c);
    }
  }
}

void	game_generateNewForm(game* this)
{
  destroy_form(this->currentForm);
  this->currentForm = new_form();
  this->posX = (MAP_WIDTH + this->currentForm->width) / 2;
  this->posY = 0;
  if (game_canMoveForm(this, this->currentForm, this->posX, this->posY) == 0) {
    this->exit = 1;
  }
}

int	game_applyFormTranslation(game* this, int x, int y)
{
  if (game_canMoveForm(this, this->currentForm,
		       this->posX + x, this->posY + y) == 1) {
    this->posX += x;
    this->posY += y;
  } else if (y > 0) {
    for (int i = 0; i < 4; ++i) {
      this->fixedScreen[this->posY + this->currentForm->points[i][1]]
	[this->posX + this->currentForm->points[i][0]] =
	this->currentForm->type;
    }
    game_removeCompleteLines(this);
    game_generateNewForm(this);
    return 1;
  }
  return 0;
}

void	game_moveFormToBottom(game* this)
{
  while (game_applyFormTranslation(this, 0, 1) == 0);
}

void	game_removeCompleteLines(game* this)
{
  for (int y = 0; y < MAP_HEIGHT; ++y) {
    int full = 1;
    for (int x = 0; full && x < MAP_WIDTH; ++x) {
      if (this->fixedScreen[y][x] == 0) {
	full = 0;
      }
    }
    if (full == 1) {
      game_removeLine(this, y);
    }
  }
}

void	game_removeLine(game* this, int y)
{
  for (int j = y; j >= 0; --j) {
    for (int x = 0; x < MAP_WIDTH; ++x) {
      this->fixedScreen[j][x] = (j == 0) ? 0 : this->fixedScreen[j - 1][x];
    }
  }
}
