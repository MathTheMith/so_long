/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:06:46 by mvachon           #+#    #+#             */
/*   Updated: 2025/04/11 02:58:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "get_next_line/get_next_line.h" 
# include "ft_printf/ft_printf.h"
# include <mlx.h>
# include <string.h>
# include <stdio.h>

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	int		last_direction;
	int		anim_state;
	int		anim_timer;
	int		collectibles;
	int		exit;
	int		new_x;
	int		new_y;
}	t_game;

typedef struct s_object_count
{
	int	count_e;
	int	count_p;
	int	count_c;
}	t_object_count;

typedef struct s_render
{
	void	*bg_image;
	int		*data;
	int		rect_width;
	int		rect_height;
}	t_render;

int		check_borders(t_game *game);
void	count_objects(t_game *game, t_object_count *count);
int		check_objects(t_game *game);
int		check_collectibles_without_exit(t_game *game);
void	find_player_position(t_game *game);
int		validate_game_map(t_game *game);
int		setup_game_rendering(t_game *game);
int		initialize_map(t_game *game, char **av);
int		setup_game(t_game *game);
void	flood_fill(char **map, int x, int y, t_game *game);
int		count_collectibles(t_game *game);
void	replace_exit_with_wall(char **map, t_game *game);
int		validate_path(t_game *game);
char	**duplicate_map(t_game *game);
void	find_player_position_for_render(t_game *game);
void	render_player(t_game *game);
int		process_movement(t_game *game, int keycode, int *player_step);
int		handle_keypress(int keycode, void *param);
void	handle_movement(t_game *game, int *player_step);
int		check_game_end(t_game *game, int player_step);
void	process_key_direction(int keycode, t_game *game);
int		is_movement_key(int keycode);
int		is_valid_move(t_game *game);
void	free_map(char **map);
int		handle_file_error(int fd, char **map);
char	**expand_map(char **map, int i, int *map_size, int fd);
int		open_map_file(const char *filename, int *fd,
			char ***map, int *map_size);
char	**read_map(const char *filename);
int		print_images(t_game *game, char *link_img, int x, int y);
void	render_jump_animation(t_game *game, void *jump_sprite);
void	render_jump(t_game *game, int left_right);
void	handle_jump_animation(t_game *game, int keycode);
int		render_static_map(t_game *game);
int		check_valid_characters(t_game *game);
int		render_game(t_game *game);
void	cleanup(t_game *game);
int check_ber_extension(const char *filename);
int		close_window(void *param);
void	initialize_game(t_game *game);

#endif