NAME	=	fdf

CC		=	gcc

CFLAGS 	=	-Wextra -Werror -Wall

SOURCE	= 	draw.c funcs_to_delete.c get_next_line.c main.c point_row.c rotate.c reading.c point.c segment.c flat.c utils.c

HEADERS	=	header.h

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
