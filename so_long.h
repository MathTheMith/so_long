/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:06:46 by mvachon           #+#    #+#             */
/*   Updated: 2025/02/26 04:10:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line/get_next_line.h" 
#include "ft_printf/ft_printf.h"
#include <mlx.h>
#include <string.h>
#include <stdio.h>

#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_ESC 65307

typedef struct s_game {
    void *mlx;
    void *win;
    char **map;
    int width;
    int height;
    int player_x;
    int player_y;
    int last_direction;
    int anim_state;
    int anim_timer;
} t_game;

typedef struct s_object_count
{
    int     count_e;
    int     count_p;
    int     count_c;
}   t_object_count;

/* Fonctions existantes */
int check_borders(char **map);

/* Nouvelles fonctions */
void count_objects(char **map, t_object_count *count);
int check_objects(char **map);

// so_long.c
int close_window(void *param);
void initialize_game(t_game *game, void *mlx, char **map, int game_width, int game_height);
int validate_game_map(char **map, int game_width, int game_height);
int setup_game_rendering(t_game *game);

// render_utils.c
int print_images(void *mlx, void *win, char *link_img, int x, int y);
void render_jump_animation(t_game *game, void *jump_sprite);
void render_jump(t_game *game, int left_right);
void handle_jump_animation(t_game *game, int keycode);

// map_validation.c
void flood_fill(char **map, int x, int y, int *collectibles, int *exit_found);
int count_collectibles(char **map, int width, int height);
void find_player_position(char **map, int width, int height, int *player_x, int *player_y);
int validate_path(char **map, int width, int height);
char **duplicate_map(char **map, int height);

// movement_utils.c
void handle_movement(t_game *game, int new_x, int new_y, int *player_step);
int check_game_end(t_game *game, int new_x, int new_y, int player_step);
void process_key_direction(int keycode, t_game *game, int *new_x, int *new_y);
int is_movement_key(int keycode);
int is_valid_move(t_game *game, int new_x, int new_y);

// movement_handlers.c
int process_movement(t_game *game, int keycode, int new_x, int new_y, int *player_step);
int handle_keypress(int keycode, void *param);

// Existing functions from original header
void free_map(char **map);
char **read_map(const char *filename);
int check_borders(char **map);
int check_objects(char **map);
void move_monster(t_game *game, void *param);
int render_game(t_game *game, void *win);
int game_loop(t_game *game);
void render_player(t_game *game, void *win);
int render_static_map(t_game *game, void *win);
void render_steps_with_background(void *mlx, void *win, int steps);
void animate_player(t_game *game, void *win, int start_x, int start_y, int end_x, int end_y);
int initialize_map(char ***map, int *width, int *height);
int setup_game(t_game *game, void *mlx, char **map, int width, int height);
void cleanup(t_game *game);



#endif