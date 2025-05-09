/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:57:29 by math              #+#    #+#             */
/*   Updated: 2025/04/11 19:04:52 by mvachon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	find_player_position_for_render(game);
	print_images(game, "./images/player_right.xpm",
		game->player_x * 98, game->player_y * 98);
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
