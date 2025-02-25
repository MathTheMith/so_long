/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:06:46 by mvachon           #+#    #+#             */
/*   Updated: 2024/12/12 22:37:32 by math             ###   ########lyon.fr   */
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

char **duplicate_map(char **map, int height);
void free_map(char **map);
char **read_map(const char *filename);
int close_window(void *param);
int handle_keypress(int keycode, void *param);
int print_images(void *mlx, void *win,char *link_img, int x, int y, int img_width, int img_height);
int check_borders(char **map);
int main(void);
int check_borders(char **map);
int check_objects(char **map);
void move_monster(t_game *game, void *param);
int render_game(t_game *game, void *win);
int game_loop(t_game *game);
int ft_printf(const char *conv, ...);
void render_player(t_game *game, void *win);
int render_static_map(t_game *game, void *win);
void render_steps_with_background(void *mlx, void *win, int steps);
void animate_player(t_game *game, void *win, int start_x, int start_y, int end_x, int end_y);



#endif