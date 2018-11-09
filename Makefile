# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/27 13:56:26 by nbouchin          #+#    #+#              #
#    Updated: 2018/11/09 12:56:04 by nbouchin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NM_NAME    = 	ft_nm
OTOOL_NAME = 	ft_otool
CC      = 	clang
HEADER  = 	includes/
LFTDIR	=	srcs/libft/
LFTPDIR =	srcs/libft/srcs/ft_printf/
FLAGS   = 	-Wall -Wextra -Werror -g
SRCDIR  = 	srcs/
NM_OBJDIR  = 		nm_objs/
OTOOL_OBJDIR  = 	otool_objs/

NM_SRC		= nm/nm.c \
		  nm/sort.c \
		  nm/utils.c \
		  nm/nm_utils.c \
		  nm/process_file.c \
		  nm/sym_processing.c \
		  nm/print_utils.c \
		  nm/alloc_utils.c \
		  nm/symtab_utils.c \
		  nm/process_header.c \
		  nm/process_fat_header.c \
		  nm/general_utils.c \
		  nm/int_utils.c \
		  nm/segment_utils.c

OTOOL_SRC	= otool/otool.c \
		  otool/section_print.c \
		  nm/utils.c \
		  nm/nm_utils.c \
		  otool/process_header.c \
		  otool/process_fat_header.c \
		  nm/process_file.c \
		  nm/general_utils.c \
		  nm/int_utils.c \
		  nm/segment_utils.c \
		  nm/alloc_utils.c \
		  otool/segment_utils.c

NM_SRCS	= $(addprefix $(SRCDIR), $(NM_SRC))
NM_OBJS	= $(addprefix $(NM_OBJDIR), $(NM_SRC:.c=.o))

OTOOL_SRCS	= $(addprefix $(SRCDIR), $(OTOOLSRC))
OTOOL_OBJS	= $(addprefix $(OTOOL_OBJDIR), $(OTOOL_SRC:.c=.o))

all: $(NM_OBJDIR) $(OTOOL_OBJDIR) $(OTOOL_NAME) $(NM_NAME) nm otool

nm: $(NM_OBJDIR) $(NM_NAME)

$(NM_NAME): $(NM_OBJS)
	make -C srcs/libft
	$(CC) $(FLAGS) -L./$(LFTDIR) -lft -L./$(LFTPDIR) -lftprintf -I $(HEADER) -o $(NM_NAME) $(NM_OBJS)

$(NM_OBJDIR):
	mkdir -p nm_objs/nm/

$(NM_OBJDIR)%.o: $(SRCDIR)%.c $(HEADER)libft_nm.h
	$(CC) -o $@ -c $< $(FLAGS) -I $(HEADER)


otool: $(OTOOL_OBJDIR) $(OTOOL_NAME)

$(OTOOL_NAME): $(OTOOL_OBJS)
	make -C srcs/libft
	$(CC) $(FLAGS) -L./$(LFTDIR) -lft -L./$(LFTPDIR) -lftprintf -I $(HEADER) -o $(OTOOL_NAME) $(OTOOL_OBJS)

$(OTOOL_OBJDIR):
	mkdir -p otool_objs/otool
	mkdir -p otool_objs/nm

$(OTOOL_OBJDIR)%.o: $(SRCDIR)%.c $(HEADER)libft_nm.h
	$(CC) -o $@ -c $< $(FLAGS) -I $(HEADER)

clean:
	rm -rf otool_objs
	rm -rf nm_objs
	make -C srcs/libft clean

fclean: clean
	rm -rf $(OTOOL_NAME)
	rm -rf $(NM_NAME)
	make -C srcs/libft fclean

re: fclean all

.PHONY: all clean fclean re
