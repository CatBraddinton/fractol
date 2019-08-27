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
MLX := libmlx.a

CC := clang
DB_FLAGS := -g -fsanitize=address
FLAGS := -Wall -Wextra -Werror -O3
MLXFLAGS := -lmlx -framework OpenGL -framework AppKit

INC_DIR := inc/
SRC_DIR := src/
LIB_DIR := libft/
MLX_DIR := minilibx_macos/

INCLUDES := $(INC_DIR)fractol.h\
			$(INC_DIR)hooks.h\
			$(INC_DIR)mandelbrot_and_julia.h\
			$(INC_DIR)colorize_it.h\

SOURCES := 	main.c\
 			$(SRC_DIR)error.c\
			$(SRC_DIR)utilits.c\
			$(SRC_DIR)mandelbrot_set.c\
			$(SRC_DIR)hooks.c\
			$(SRC_DIR)julia_set.c\
			$(SRC_DIR)colorizer.c\

OBJECTS := 	main.o error.o utilits.o mandelbrot_set.o hooks.o colorizer.o\
			julia_set.o

LIBFT := $(LIB_DIR)$(FT)
MINILIBX := $(MLX_DIR)$(MLX)

.PHONY: all lib libmlx clean fclean re debug

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT) $(MINILIBX)
	@printf "Compiling $(NAME)\n"
	@$(CC) $(FLAGS) $(MLXFLAGS) -o $(NAME) $(OBJECTS) $(LIBFT) $(MINILIBX)
	@printf "$(NAME) created\n"

debug: $(DB_NAME)

$(DB_NAME): $(OBJECTS) $(LIBFT) $(MINILIBX)
	@printf "Compiling $(DB_NAME)\n"
	$(CC) $(FLAGS) $(MLXFLAGS) $(DB_FLAGS) -o $(DB_NAME) $(OBJECTS) $(LIBFT) $(MINILIBX)
	@printf "$(DB_NAME) created\n"

$(OBJECTS): $(SOURCES) $(INCLUDES)
	@$(CC) $(FLAGS) -c $(SOURCES) -I $(INCLUDES)

$(LIBFT): lib
$(MINILIBX): libmlx

lib:
	@make -C $(LIB_DIR)

libmlx:
	@make -C $(MLX_DIR)

clean:
	@rm -f $(OBJECTS) inc/*.gch
	@make fclean -C $(LIB_DIR)
	@make clean -C $(MLX_DIR)

fclean: clean
	@rm -f $(NAME) $(DB_NAME)
	@printf "$(NAME)removed\n"
	@rm -f $(DB_NAME)
	@printf "$(DB_NAME)removed\n"
re: fclean all
