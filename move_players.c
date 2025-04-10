/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:57:29 by math              #+#    #+#             */
/*   Updated: 2025/04/10 06:14:03 by marvin           ###   ########.fr       */
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
	char	*player_img;

	find_player_position_for_render(game);
	if (game->last_direction == -1)
		player_img = "./images/player_left.xpm";
	else
		player_img = "./images/player_right.xpm";
	print_images(game, player_img,
		game->player_x * 98, game->player_y * 98);
}
