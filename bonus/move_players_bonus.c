/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_players_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:57:29 by math              #+#    #+#             */
/*   Updated: 2025/04/14 08:20:26 by mvachon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	find_player_position_for_render(t_game *game)
{
	int	row;
	int	col;

	row = 0;
	while (row < game->height)
	{
		col = 0;
		while (col < game->width)
		{
			if (game->map[row][col] == 'P')
			{
				game->player_x = col;
				game->player_y = row;
				return ;
			}
			col++;
		}
		row++;
	}
}

void	render_player(t_game *game)
{
	char	*player_img;

	find_player_position_for_render(game);
	if (game->last_direction == -1)
		player_img = "./images/player_left.xpm";
	else
		player_img = "./images/player_right.xpm";
	print_images(game, player_img,
		game->player_x * 98, game->player_y * 98);
}

void	clear_image_background(int *data, int width, int height)
{
	int	i;

	i = 0;
	while (i < width * height)
	{
		data[i] = 0x000000;
		i++;
	}
}

void	render_steps_with_background(t_game *game, int steps)
{
	char		step_count[50];
	void		*bg_image;
	int			*data;
	t_position	pos;

	pos.rect_height = 50;
	pos.rect_width = 150;
	bg_image = mlx_new_image(game->mlx, pos.rect_width, pos.rect_height);
	if (!bg_image)
	{
		ft_printf("Error\nNo background image\n");
		cleanup(game);
		exit(1);
	}
	data = (int *)mlx_get_data_addr(bg_image, &(int){0}, &(int){0}, &(int){0});
	sprintf(step_count, "Steps: %d", steps);
	clear_image_background(data, pos.rect_width, pos.rect_height);
	mlx_put_image_to_window(game->mlx, game->win, bg_image, 25, 25);
	mlx_string_put(game->mlx, game->win, 40, 40, 0xFFFFFF, step_count);
	mlx_destroy_image(game->mlx, bg_image);
}

void	find_player_position(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}
