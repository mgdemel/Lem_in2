
NAME = lem-in

SRCS = 	srcs/main.c srcs/initialize.c srcs/store_data.c srcs/test_structs.c \

OBJS = 	main.o initialize.o store_data.o test_structs.o\

INCS = -I includes/lem_in.h
CFLAGS = -Wall -Wextra -Werror
LIB = -L libft -lft

all: $(NAME)

$(NAME):
	@make -C libft
	@gcc $(CFLAGS) -g -c $(SRCS) $(INCS)
	@gcc $(CFLAGS) $(INCS) $(OBJS) $(LIB) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@make -C libft clean

fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean

re: fclean all

.PHONY: clean fclean re all