NAME	= tetris

CC	= gcc

RM	= rm -f

CFLAGS	= -W -Wall -I includes -std=c99 -g

LDFLAGS	= -lncurses -ltermcap -ltcl8.6

SRC	= src/main.c \
	  src/list.c \
	  src/game.c \
	  src/form.c \

OBJ	= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
