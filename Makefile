# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/29 14:38:04 by grevenko          #+#    #+#              #
#    Updated: 2017/12/29 14:46:59 by grevenko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fdf

CC		=	gcc

CFLAGS 	=	-Wall -Wextra -Werror

SOURCE	= 	source/color.c source/draw.c source/error.c source/event_handlers.c source/main.c source/mutate.c source/point_row.c source/point.c source/reading.c source/utils.c

HEADERS	=	source/header.h

LIBS	=	libft/libft.a minilibx_macos/libmlx.a

OBJ		=	$(SOURCE:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	make -C libft;
	make -C minilibx_macos;
	${CC} -o $(NAME) $(OBJ) ${LIBS} -framework OpenGL -framework AppKit
	
clean:
	make -C libft clean;
	make -C minilibx_macos clean;
	rm -f $(OBJ);

fclean: clean
	make -C libft fclean;
	rm -f $(NAME);

re: fclean all
