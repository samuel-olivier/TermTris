
typedef struct s_form
{
  char		type;
  int		width;
  int		height;
  float		center[2];
  int		points[4][2];
}		form;

form*	new_form();
void	destroy_form(form* this);

void	form_rotate(form* this);
