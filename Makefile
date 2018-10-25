# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/27 13:56:26 by nbouchin          #+#    #+#              #
#    Updated: 2018/10/25 14:03:29 by nbouchin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = 	ft_nm
CC      = 	clang
HEADER  = 	includes/
LFTDIR	=	srcs/libft/
LFTPDIR =	srcs/libft/srcs/ft_printf/
FLAGS   = 	-Wall -Wextra -Werror -g
SRCDIR  = 	srcs/
OBJDIR  = 	objs/
SRC		= nm.c \
		  symtab_utils.c \
		  process_header.c \
		  process_fat_header.c \
		  general_utils.c \
		  segment_utils.c

SRCS	= $(addprefix $(SRCDIR), $(SRC))
OBJS	= $(addprefix $(OBJDIR), $(SRC:.c=.o))

all: $(OBJDIR) $(NAME)

INDEX = 0

$(NAME): $(OBJS)
	make -C srcs/libft
	$(CC) $(FLAGS) -L./$(LFTDIR) -lft -L./$(LFTPDIR) -lftprintf -I $(HEADER) -o $(NAME) $(OBJS)

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

.PHONY: all clean fclean re
