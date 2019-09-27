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
FLAGS := -Wall -Wextra -Werror -O3
MLXFLAGS := -lmlx -framework OpenGL -framework AppKit

INC_DIR := inc/
SRC_DIR := src/
LIB_DIR := libft/

INCLUDES := $(INC_DIR)fractol.h\
			$(INC_DIR)hooks.h\
			$(INC_DIR)colorize_it.h\

SOURCES := 	main.c\
 			$(SRC_DIR)error.c\
			$(SRC_DIR)utilits.c\
			$(SRC_DIR)hooks.c\
			$(SRC_DIR)mandelbrot_set.c\
			$(SRC_DIR)burning_ship_fractal.c\
			$(SRC_DIR)julia_set.c\
			$(SRC_DIR)tricorn_fractal.c\
			$(SRC_DIR)count_points.c\
			$(SRC_DIR)colorizer.c\
			$(SRC_DIR)drawers.c\
			$(SRC_DIR)zoom.c\

OBJECTS := 	main.o error.o utilits.o hooks.o colorizer.o drawers.o \
			mandelbrot_set.o julia_set.o tricorn_fractal.o count_points.o\
			burning_ship_fractal.o zoom.o\

LIBFT := $(LIB_DIR)$(FT)

.PHONY: all lib libmlx clean fclean re debug

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT)
	@printf "Compiling $(NAME)\n"
	@$(CC) $(FLAGS) $(MLXFLAGS) -o $(NAME) $(OBJECTS) $(LIBFT)
	@printf "$(NAME) created\n"

debug: $(DB_NAME)

$(DB_NAME): $(OBJECTS) $(LIBFT)
	@printf "Compiling $(DB_NAME)\n"
	$(CC) $(FLAGS) $(MLXFLAGS) $(DB_FLAGS) -o $(DB_NAME) $(OBJECTS) $(LIBFT)
	@printf "$(DB_NAME) created\n"

$(OBJECTS): $(SOURCES) $(INCLUDES)
	@$(CC) $(FLAGS) -c $(SOURCES) -I $(INCLUDES)

$(LIBFT): lib

lib:
	@make -C $(LIB_DIR)

clean:
	@rm -f $(OBJECTS) inc/*.gch
	@make fclean -C $(LIB_DIR)

fclean: clean
	@rm -f $(NAME) $(DB_NAME)
	@printf "$(NAME)removed\n"
	@rm -f $(DB_NAME)
	@printf "$(DB_NAME)removed\n"
re: fclean all
