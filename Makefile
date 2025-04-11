# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvachon <mvachon@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 07:28:08 by math              #+#    #+#              #
#    Updated: 2025/04/11 23:57:01 by mvachon          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME    =   so_long
NAME_BONUS = so_long_bonus

HEADER    = so_long.h
BONUS_HEADER = bonus/so_long_bonus.h 

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
			get_next_line/utils.c \
			ft_printf/ft_printf.c \
            ft_printf/ext_functions.c \

BONUS_DIR = bonus
BONUS_SRC =	$(BONUS_DIR)/so_long_bonus.c \
			  $(BONUS_DIR)/map_validation_bonus.c \
			  $(BONUS_DIR)/render_utils_bonus.c \
              $(BONUS_DIR)/game_utils_bonus.c \
              $(BONUS_DIR)/movement_utils_bonus.c \
              $(BONUS_DIR)/movement_handlers_bonus.c \
              $(BONUS_DIR)/read_map_bonus.c \
              $(BONUS_DIR)/check_functions_bonus.c \
              $(BONUS_DIR)/rendering_bonus.c \
              $(BONUS_DIR)/move_players_bonus.c \
              $(BONUS_DIR)/get_next_line/get_next_line_utils_bonus.c \
              $(BONUS_DIR)/get_next_line/get_next_line_bonus.c \
              $(BONUS_DIR)/get_next_line/utils_bonus.c \
              $(BONUS_DIR)/ft_printf/ft_printf_bonus.c \
              $(BONUS_DIR)/ft_printf/ext_functions_bonus.c \

DIR_OBJ = obj
OBJ     = $(SRC:%.c=$(DIR_OBJ)/%.o)
BONUS_OBJ = $(BONUS_SRC:$(BONUS_DIR)/%.c=$(DIR_OBJ)/bonus_/%.o)

CC      = gcc
AR      = ar rcs

GREEN	= \033[0;32m
BLUE	= \033[0;34m
GRAY	= \033[1;30m
RED		= \033[0;31m
NC		= \033[0m

all: $(NAME)
	@echo "$(GREEN)✅ Compilation terminée !$(NC)"

$(NAME): $(MLX_LIB) $(OBJ)
	@echo "$(BLUE)🔧 Linking...$(NC)"
	$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) -o $@

$(NAME_BONUS): $(MLX_LIB) $(BONUS_OBJ)
	@echo "$(BLUE)🔧 Linking (bonus)...$(NC)"
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(MLX_FLAGS) -o $@

bonus: $(NAME_BONUS)
	@echo "$(GREEN)✅ Bonus compilation terminée !$(NC)"

$(MLX_LIB):
	@echo "$(BLUE)📦 Compilation de la minilibx...$(NC)"
	@$(MAKE) -C $(MLX_DIR)

$(DIR_OBJ)/%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	@echo "$(GRAY)🛠️  Compilation de $<$(NC)"
	@$(CC) $(CFLAGS) $(MLX_INC) -c $< -o $@


$(DIR_OBJ)/bonus_/%.o: $(BONUS_DIR)/%.c $(BONUS_HEADER)
	@mkdir -p $(dir $@)
	@echo "$(GRAY)🛠️  Compilation de $< (bonus)$(NC)"
	@$(CC) $(CFLAGS) $(MLX_INC) -c $< -o $@

clean:
	@echo "$(RED)🧹 Suppression des fichiers objets...$(NC)"
	@rm -rf $(DIR_OBJ)
	@$(MAKE) clean -C $(MLX_DIR)

fclean: clean
	@echo "$(RED)🗑️ Suppression de l'exécutable...$(NC)"
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)	

re: fclean all

.PHONY: all clean fclean re bonus
