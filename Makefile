
NAME = lem-in

SRCS = 	srcs/main.c srcs/initialize.c srcs/store_data.c srcs/test_structs.c srcs/error.c srcs/utils.c srcs/tree_making.c srcs/gather_paths.c srcs/free.c \

OBJS = 	main.o initialize.o store_data.o test_structs.o error.o utils.o tree_making.o gather_paths.o free.o\

INCS = -I includes/lem_in.h
CFLAGS = -Wall -Wextra -Werror
LIB = -L libft -lft

all: $(NAME)

$(NAME):
	@make -C libft
	@gcc $(CFLAGS) -g -c $(SRCS) $(INCS)
	@gcc $(CFLAGS) $(INCS) $(OBJS) $(LIB) -o $(NAME)
	@mkdir objs 
	@mv $(OBJS) objs 

lem: clean
	@gcc $(CFLAGS) -g -c $(SRCS) $(INCS)
	@gcc $(CFLAGS) $(INCS) $(OBJS) $(LIB) -o $(NAME)
	@mkdir objs
	@mv $(OBJS) objs 

clean:
	@rm -rf objs
	@make -C libft clean

fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean

re: fclean all

.PHONY: clean fclean re all