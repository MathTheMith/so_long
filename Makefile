# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 07:28:08 by math              #+#    #+#              #
#    Updated: 2025/02/26 01:53:13 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    =   so_long
HEADER  =   so_long.h
CFLAGS  =   -Wall -Wextra -Werror

MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_INC = -I$(MLX_DIR)
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11

SRC     =   so_long.c \
			render_utils.c \
			game_utils.c \
			map_validation.c \
			movement_utils.c \
			movement_handlers.c \
			read_map.c \
			check_functions.c \
			rendering.c \
			move_players.c \
			get_next_line/get_next_line_utils.c \
			get_next_line/get_next_line.c \
			ft_printf/ft_printf.c \
            ft_printf/ext_functions.c \

DIR_OBJ = obj/
OBJ     = $(SRC:%.c=$(DIR_OBJ)%.o)

CC      = gcc
AR      = ar rcs

all: $(NAME)

$(NAME): $(MLX_LIB) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) -o $@

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

$(DIR_OBJ)%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(MLX_INC) -c $< -o $@

clean:
	@rm -rf $(DIR_OBJ)
	@$(MAKE) clean -C $(MLX_DIR)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(MLX_DIR)

re: fclean all

.PHONY: all clean fclean re