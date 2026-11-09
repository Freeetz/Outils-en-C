# Makefile

NAME = main

SRCS = main.c \
	config/config.c \
	features/*.c 

all: $(NAME)

$(NAME): $(SRCS)
	gcc $(SRCS) -o $(NAME)

fclean:
	rm -f $(NAME)

re: fclean all