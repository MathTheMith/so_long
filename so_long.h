/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:06:46 by mvachon           #+#    #+#             */
/*   Updated: 2024/12/03 15:51:43 by mvachon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line/get_next_line.h" 
#include <mlx.h>
#include <string.h>

void free_map(char **map);
char **read_map(const char *filename);
int close_window(void *param);
int handle_keypress(int keycode, void *param);
int print_images(void *mlx, void *win,char *link_img, int x, int y, int img_width, int img_height);
int main(void);

#endif