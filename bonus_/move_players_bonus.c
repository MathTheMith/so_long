/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_players_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:57:29 by math              #+#    #+#             */
/*   Updated: 2025/04/11 06:43:15 by marvin           ###   ########.fr       */
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

void	render_steps_with_background(t_game *game, int steps)
{
	char	step_count[50];
	int		i;
	void	*bg_image;
	int		*data;
	t_position pos;

	pos.rect_height = 50;
	pos.rect_width = 150;
	bg_image = mlx_new_image(game->mlx, pos.rect_width, pos.rect_height);
	data = (int *)mlx_get_data_addr(bg_image, &(int){0},
			&(int){0}, &(int){0});
	sprintf(step_count, "Steps: %d", steps);
	i = 0;
	while (i < pos.rect_width * pos.rect_height)
	{
		data[i] = 0x000000;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, bg_image, 25, 25);
	mlx_string_put(game->mlx, game->win, 40, 40, 0xFFFFFF, step_count);
	mlx_destroy_image(game->mlx, bg_image);
}
