/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:06:46 by mvachon           #+#    #+#             */
/*   Updated: 2024/12/04 01:52:49 by math             ###   ########lyon.fr   */
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

typedef struct s_game
{
    void    *mlx;
    void    *win;
    char    **map;
    int     player_x;
    int     player_y;
    int     width;
    int     height;
} t_game;

void free_map(char **map);
char **read_map(const char *filename);
int close_window(void *param);
int handle_keypress(int keycode, void *param);
int print_images(void *mlx, void *win,char *link_img, int x, int y, int img_width, int img_height);
int check_borders(char **map);
int main(void);
int check_objects(char **map);
void move_dragons(t_game *game);

#endif