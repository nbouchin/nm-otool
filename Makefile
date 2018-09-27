# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/27 13:56:26 by nbouchin          #+#    #+#              #
#    Updated: 2018/09/27 17:15:31 by nbouchin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = 	libft.a
CC      = 	clang
HEADER  = 	includes/
FLAGS   = 	-Wall -Wextra -Werror
SRCDIR  = 	srcs/
OBJDIR  = 	objs/
SRC		=	main.c	

SRCS	= $(addprefix $(SRCDIR), $(SRC))
OBJS	= $(addprefix $(OBJDIR), $(SRC:.c=.o))

all: $(OBJDIR) $(NAME)

INDEX = 0

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "\nCompilation done for libft.a\n"
	@make -C srcs/ft_printf

$(OBJDIR):
	@mkdir -p objs objs/get_next_line objs/str objs/put objs/num objs/mem objs/lst objs/conv objs/check objs/tab

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADER)libft.h
	@$(CC) -o $@ -c $< $(FLAGS) -I $(HEADER)
	$(eval INDEX=$(shell printf "%d" $$(($(INDEX)+1))))
	@printf "[%02d/71] Compiling (C) %s...\n" $(INDEX) $@

clean:
	@rm -rf objs
	@echo "Cleaning objects..."
	@make -C srcs/ft_printf clean

fclean: clean
	@rm -rf $(NAME)
	@echo "Cleaning binaries..."
	@make -C srcs/ft_printf fclean

re: fclean all

.PHONY: all clean fclean re
