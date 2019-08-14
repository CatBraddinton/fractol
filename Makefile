# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/13 20:11:23 by kdudko            #+#    #+#              #
#    Updated: 2019/08/13 20:11:26 by kdudko           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := fractol
DB_NAME := db_fractol
FT := libft.a

CC := clang
DB_FLAGS := -g -fsanitize=address
FLAGS := -Wall -Wextra -Werror
MLXFLAGS := -lmlx -framework OpenGL -framework AppKit

INC_DIR := inc/
SRC_DIR := src/
LIB_DIR := libft/

INCLUDES := $(INC_DIR)fractol.h\
			$(INC_DIR)hooks.h

SOURCES := 	main.c\
 			$(SRC_DIR)error.c\
			$(SRC_DIR)utilits.c\
			$(SRC_DIR)julia_set.c\
			$(SRC_DIR)mandelbrot_set.c\
			$(SRC_DIR)sierpinski_triangle.c\
			$(SRC_DIR)hooks.c\

OBJECTS := 	main.o error.o utilits.o julia_set.o mandelbrot_set.o\
			sierpinski_triangle.o hooks.o

LIBFT := $(LIB_DIR)$(FT)

.PHONY: all  lib clean fclean re

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT)
	$(CC) $(FLAGS) $(MLXFLAGS) -o $(NAME) $(OBJECTS) $(LIBFT)

debug: $(DB_NAME)

$(DB_NAME): $(OBJECTS) $(LIBFT)
	$(CC) $(FLAGS) $(MLXFLAGS) $(DB_FLAGS) -o $(DB_NAME) $(OBJECTS) $(LIBFT)

$(OBJECTS): $(SOURCES) $(INCLUDES)
	$(CC) $(FLAGS) -c $(SOURCES) -I $(INCLUDES)

$(LIBFT): lib

lib:
	make -C $(LIB_DIR)

clean:
	rm -f $(OBJECTS) inc/*.gch
	make fclean -C $(LIB_DIR)


fclean: clean
	rm -f $(NAME) $(DB_NAME)
	make fclean -C $(LIB_DIR)

re: fclean all
