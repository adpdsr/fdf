# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/28 15:36:47 by adu-pelo          #+#    #+#              #
#    Updated: 2016/11/09 13:45:04 by adu-pelo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC = 	sources/parsing.c \
		sources/put_map.c \
		sources/do_map.c \
		sources/color.c \
		sources/error.c \
		sources/main.c \
		sources/hook.c

OBJ		= $(SRC:.c=.o)
FLAGS	= -Wall -Wextra -Werror
LIBS	= -L./libft -lft -lmlx -framework OpenGL -framework AppKit

$(NAME): $(OBJ)
	@echo "Creating $(NAME)"
	@make -C ./libft
	@gcc $(FLAGS) $(OBJ) $(LIBS) -o $(NAME)

all: $(NAME)

%.o: %.c
	@echo "Creating object : $@"
	@gcc $(FLAGS) -o $@ -c $<

clean :
	@echo "Deleting objects"
	@rm -f $(OBJ)
	@make -C libft/ clean

fclean: clean
	@echo "Deleting $(NAME)"
	@rm -rf $(NAME)
	@make fclean -C libft

re: fclean all

.PHONY : all clean fclean re
