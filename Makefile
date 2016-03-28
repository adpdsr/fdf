# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/28 15:36:47 by adu-pelo          #+#    #+#              #
#    Updated: 2016/03/28 18:21:34 by adu-pelo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC = 	src/parsing.c \
		src/put_map.c \
		src/do_map.c \
		src/color.c \
		src/error.c \
		src/main.c \
		src/hook.c

OBJ = $(SRC:.c=.o)
	FLAGS = -Wall -Wextra -Werror
	LIBS = -L./libft -lft -lmlx -framework OpenGL -framework AppKit

$(NAME): $(OBJ)
	make -C ./libft
	gcc $(FLAGS) $(OBJ) $(LIBS) -o $(NAME)

all: $(NAME)

%.o: %.c
	gcc $(FLAGS) -o $@ -c $<

clean :
	rm -f $(OBJ)
	make -C libft/ clean

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft

re: fclean all

.PHONY : all clean fclean re
