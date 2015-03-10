#include "form.h"

#include <stdlib.h>
#include <string.h>

static form	factory[] =
  {
    {'I', 1, 4, {-1.0, 1.0}, {{-1, 0}, {-1, 1}, {-1, 2}, {-1, 3}}},
    {'O', 2, 2, {-1.5, 0.5}, {{-2, 0}, {-2, 1}, {-1, 0}, {-1, 1}}},
    {'T', 3, 2, {-1.0, 0.0}, {{-2, 0}, {-1, 0}, {0, 0}, {-1, 1}}},
    {'L', 3, 2, {-1.0, 1.0}, {{0, 0}, {-2, 1}, {-1, 1}, {0, 1}}},
    {'J', 3, 2, {-1.0, 1.0}, {{-2, 0}, {-2, 1}, {-1, 1}, {0, 1}}},
    {'Z', 3, 2, {-1.0, 0.0}, {{-2, 0}, {-1, 1}, {-1, 0}, {0, 1}}},
    {'S', 3, 2, {-1.0, 0.0}, {{-2, 1}, {-1, 1}, {-1, 0}, {0, 0}}},
  };

form*	new_form()
{
  form* this = malloc(sizeof(*this));

  memcpy(this, &factory[rand() % (sizeof(factory) / (sizeof(*factory)))],
	 sizeof(*this));
  return this;
}

void	destroy_form(form* this)
{
  free(this);
}

void	form_rotate(form* this)
{
  for (int i = 0; i < 4; ++i) {
    float new[2] = {this->points[i][0] - this->center[0],
  		    this->points[i][1] - this->center[1]};
    this->points[i][0] = this->center[0] - new[1];
    this->points[i][1] = this->center[1] + new[0];
  }
}
