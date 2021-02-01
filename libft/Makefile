# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/26 11:02:46 by lvasanoj          #+#    #+#              #
#    Updated: 2021/01/29 13:48:11 by lvasanoj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAGS = -Wall -Werror -Wextra
CC := gcc

SRC = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c \
ft_memcmp.c ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c \
ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c ft_strnstr.c \
ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_memalloc.c ft_memdel.c \
ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c \
ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c \
ft_strsplit.c ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c \
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c \
ft_deletecontent.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c \
ft_lstmap.c ft_isupper.c ft_islower.c ft_isspace.c ft_words.c get_next_line.c \
ft_isalldigit.c \
ft_printf.c \
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
		
INCLUDES_PATH	:= include/
INCLUDES		:= -I $(INCLUDES_PATH)
HEADERS			:= $(addprefix $(INCLUDES_PATH), $(HEADERS_FILES))


SOURCES_PATH	:= sources/
SOURCES			:= $(addprefix $(SOURCES_PATH), $(SRC))


OBJS_PATH		:= obj/
OBJECTS			:= $(addprefix $(OBJS_PATH), $(SRC:.c=.o))




.PHONY: all clean fclean re

all: $(NAME)

$(OBJS_PATH)%.o: $(SOURCES_PATH)%.c 
		@mkdir -p $(OBJS_PATH) 2> /dev/null || true
		$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

$(NAME): $(OBJECTS)
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)

clean:
	@rm -fv $(OBJECTS)
	@rmdir $(OBJS_PATH) 2> /dev/null || true

fclean: clean
	@rm -fv $(NAME)

re:	fclean all
