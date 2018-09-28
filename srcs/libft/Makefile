# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/27 13:56:26 by nbouchin          #+#    #+#              #
#    Updated: 2018/09/28 15:58:43 by nbouchin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = 	libft.a
CC      = 	clang
HEADER  = 	includes/
FLAGS   = 	-Wall -Wextra -Werror
SRCDIR  = 	srcs/
OBJDIR  = 	objs/
SRC		=	check/ft_isalnum.c				\
			check/ft_isalpha.c				\
			check/ft_isascii.c				\
			check/ft_isdigit.c				\
			check/ft_islower.c				\
			check/ft_isprint.c				\
			check/ft_isspace.c				\
			check/ft_isupper.c				\
			conv/ft_atoi.c					\
			conv/ft_itoa.c					\
			conv/ft_tolower.c				\
			conv/ft_toupper.c				\
			tab/ft_sort_params.c			\
			tab/ft_tabcpy.c					\
			get_next_line/get_next_line.c	\
			lst/ft_lstadd.c					\
			lst/ft_lstaddend.c				\
			lst/ft_lstdel.c					\
			lst/ft_lstdelone.c				\
			lst/ft_lstiter.c				\
			lst/ft_lstmap.c					\
			lst/ft_lstnew.c					\
			mem/ft_memalloc.c				\
			mem/ft_memccpy.c				\
			mem/ft_memchr.c					\
			mem/ft_memcmp.c					\
			mem/ft_memcpy.c					\
			mem/ft_memdel.c					\
			mem/ft_memmove.c				\
			mem/ft_memset.c					\
			mem/ft_realloc.c				\
			num/ft_bzero.c					\
			num/ft_nblen.c					\
			num/ft_power.c					\
			put/ft_putchar.c				\
			put/ft_putchar_fd.c				\
			put/ft_putendl.c				\
			put/ft_putendl_fd.c				\
			put/ft_putnbr.c					\
			put/ft_putnbr_fd.c				\
			put/ft_putstr.c					\
			put/ft_putstr_fd.c				\
			str/ft_charjoin.c				\
			str/ft_queuestr.c				\
			str/ft_strcat.c					\
			str/ft_strchr.c					\
			str/ft_strclr.c					\
			str/ft_strcmp.c					\
			str/ft_strcpy.c					\
			str/ft_strdel.c					\
			str/ft_strdup.c					\
			str/ft_strequ.c					\
			str/ft_striter.c				\
			str/ft_striteri.c				\
			str/ft_strjoin.c				\
			str/ft_strlcat.c				\
			str/ft_strlen.c					\
			str/ft_strmap.c					\
			str/ft_strmapi.c				\
			str/ft_strncat.c				\
			str/ft_strncmp.c				\
			str/ft_strncpy.c				\
			str/ft_strnequ.c				\
			str/ft_strnew.c					\
			str/ft_strnstr.c				\
			str/ft_strrchr.c				\
			str/ft_strrev.c					\
			str/ft_strsplit.c				\
			str/ft_strstr.c					\
			str/ft_strsub.c					\
			str/ft_strtrim.c


SRCS	= $(addprefix $(SRCDIR), $(SRC))
OBJS	= $(addprefix $(OBJDIR), $(SRC:.c=.o))

all: $(OBJDIR) $(NAME)

INDEX = 0

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)
	make -C srcs/ft_printf

$(OBJDIR):
	mkdir -p objs objs/get_next_line objs/str objs/put objs/num objs/mem objs/lst objs/conv objs/check objs/tab

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADER)libft.h
	$(CC) -o $@ -c $< $(FLAGS) -I $(HEADER)

clean:
	rm -rf objs
	make -C srcs/ft_printf clean

fclean: clean
	rm -rf $(NAME)
	make -C srcs/ft_printf fclean

re: fclean all

.PHONY: all clean fclean re
