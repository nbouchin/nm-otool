# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/27 13:56:26 by nbouchin          #+#    #+#              #
#    Updated: 2018/10/16 12:53:23 by nbouchin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = 	ft_nm
CC      = 	clang
HEADER  = 	includes/
LFTDIR	=	srcs/libft/
LFTPDIR =	srcs/libft/srcs/ft_printf/
FLAGS   = 	-Wall -Wextra -Werror
SRCDIR  = 	srcs/
OBJDIR  = 	objs/
SRC		= nm.c

SRCS	= $(addprefix $(SRCDIR), $(SRC))
OBJS	= $(addprefix $(OBJDIR), $(SRC:.c=.o))

all: $(OBJDIR) $(NAME)

INDEX = 0

$(NAME): $(OBJS)
	make -C srcs/libft
	$(CC) $(FLAGS) -L./$(LFTDIR) -lft -I $(HEADER) -o $(NAME) $(OBJS)

$(OBJDIR):
	mkdir -p objs

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADER)libft_nm.h
	$(CC) -o $@ -c $< $(FLAGS) -I $(HEADER)

clean:
	rm -rf objs
	make -C srcs/libft clean

fclean: clean
	rm -rf $(NAME)
	make -C srcs/libft fclean

re: fclean all
	make -C srcs/libft re

.PHONY: all clean fclean re
