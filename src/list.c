
#include "list.h"

#include <unistd.h>
#include <stdlib.h>

listItem*	list_newItem(void* data);

list	new_list()
{
  return NULL;
}

void	list_append(list* this, void* data)
{
  listItem* item = list_newItem(data);
  if (*this == NULL) {
    *this = item;
    return ;
  }
  listItem* it = *this;
  while (it->next != NULL) {
    it = it->next;
  }
  it->next = item;
}

void	list_prepend(list* this, void* data)
{
  listItem* item = list_newItem(data);
  item->next = *this;
  *this = item;
}

int	list_length(list* this)
{
  listItem* it = *this;
  int length = 0;
  while (it != NULL) {
    it = it->next;
    ++length;
  }
  return length;
}

listItem*	list_newItem(void* data)
{
  listItem*	item = malloc(sizeof(*item));

  item->next = NULL;
  item->data = data;
  return item;
}
