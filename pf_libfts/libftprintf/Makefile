# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/26 11:02:46 by lvasanoj          #+#    #+#              #
#    Updated: 2020/10/22 10:45:53 by lvasanoj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
LIBFT = libft.a

COMPILE = gcc -Wall -Werror -Wextra $(PRINTF_H) $(LIBFT_H) -c -o

PRINTF_H = -I include/
LIBFT_H = -I libft/includes

OBJ_DIR = obj/
SRC_DIR = sources/
LIB_DIR = libft/

FILES = ft_printf.c \
		check_letter.c \
		flags.c \
		initialize.c \
		putstrprecision.c \
		treat_cs.c \
		ft_itoa_new.c \
		treat_d.c \
		treat_o.c \
		treat_p.c \
		treat_u.c \
		treat_x.c \
		calc_hex.c \
		treatment.c \
		calc_octal.c \
		treat_f.c \
		calc_f.c \
		calc_f_helper.c \
		calc_f_helper2.c \
		typecast.c \

COMFIND = $(FILES:%=$(SRC_DIR)%)

OBJFIND = $(FILES:%.c=%.o)

OBJ = $(addprefix $(OBJ_DIR), $(OBJFIND))

all: $(NAME)

$(OBJ_DIR):
			@mkdir -p $(OBJ_DIR)
			@echo Creating library Object directory

$(NAME): $(OBJ_DIR) $(OBJ)
			@make -C $(LIB_DIR)
			@cp $(LIB_DIR)$(LIBFT) .
			@mv $(LIBFT) $(NAME)
			@ar rc $(NAME) $(addprefix $(OBJ_DIR), $(OBJFIND))
			@ranlib $(NAME)
			@echo Merged: $(NAME) with $(LIBFT)
			@echo LIBRARY COMPLETE

$(OBJ): $(COMFIND)
			@$(MAKE) $(OBJFIND)

$(OBJFIND):
			@$(COMPILE) $(OBJ_DIR)$@ $(SRC_DIR)$(@:%.o=%.c)

clean:
		@/bin/rm -rf $(OBJ_DIR)
		@make -C $(LIB_DIR) clean

fclean: clean
		@/bin/rm -f $(NAME)
		@make -C $(LIB_DIR) fclean
		@echo Cleaned $(NAME)

re: fclean all

.PHONY: all clean fclean re
