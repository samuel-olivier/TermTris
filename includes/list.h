
typedef struct		s_listItem
{
  void*			data;
  struct s_listItem*	next;
}			listItem;

typedef listItem* list;

list	new_list();

void	list_append(list* this, void* data);
void	list_prepend(list* this, void* data);
int	list_length(list* this);

