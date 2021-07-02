# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvasanoj <lvasanoj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/25 13:38:26 by lvasanoj          #+#    #+#              #
#    Updated: 2021/07/02 14:45:24 by lvasanoj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
ARCHIVE = libftlemin.a
CC := gcc
CFLAGS = -Wall -Wextra -Werror

GREEN = \033[32m
YELLOW = \033[33m
COLOR_RESET = \033[0m

SRCS_PATH := srcs/
OBJECTS_PATH := objs/

INCL_PATH := includes/
LIB = -L libft -lft

SRCS = 	main.c \
		initialize.c \
		store_data.c \
		test_structs.c \
		tree_making.c \
		gather_paths.c \
		free.c \
		store_data_utils.c \
		tree_making_utils.c \
		flow_management.c \
		flow_management_utils.c \
		gather_paths_utils.c \
		output.c \
		tunnel_making.c \
		tree_making2.c \

INCLUDES := -I $(INCL_PATH)

SOURCES := $(addprefix $(SRCS_PATH), $(SRCS))
OBJS := 	$(addprefix $(OBJECTS_PATH), $(SRCS:.c=.o))


all: library $(ARCHIVE) $(NAME)

lem: clean $(ARCHIVE) $(NAME)

$(OBJECTS_PATH)%.o: $(SRCS_PATH)%.c 
	@mkdir -p $(OBJECTS_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

library:
	@echo "$(YELLOW)Compiling Libft$(COLOR_RESET)"
	@make -C libft
	@echo "$(GREEN)Libft was compiled successfully!$(COLOR_RESET)"

$(ARCHIVE): $(OBJS)
	@echo "$(YELLOW)Compiling Lem-in$(COLOR_RESET)"
	@ar rc $(ARCHIVE) $(OBJS)
	@ranlib $(ARCHIVE)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(ARCHIVE) $(LIB)
	@echo "$(GREEN)Lem-in was compiled successfully!$(COLOR_RESET)"

help:
	@echo "Usage: make [options]"
	@echo "Options:"
	@echo "all: Compiles all libraries and project."
	@echo "library: Compiles libft."
	@echo "lem: Compiles project, assumes you have libft compiled."
	@echo "re: Cleans all files and remakes."
	@echo "clean: Cleans all library files."
	@echo "fclean: Cleans all library files and executable."

clean:
	@echo "$(YELLOW)Cleaning library files$(COLOR_RESET)"
	@rm -rf $(OBJS)
	@make -C libft clean
	@rmdir $(OBJS_PATH) 2> /dev/null || true
	@echo "$(GREEN)Done!$(COLOR_RESET)"

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(ARCHIVE)
	@make -C libft fclean

re: fclean all

.PHONY: help lem library clean fclean re all
