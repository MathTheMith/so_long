/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:18:54 by math              #+#    #+#             */
/*   Updated: 2025/04/14 08:15:33 by mvachon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	render_static_map(t_game *game)
{
	int	row;
	int	col;

	row = 0;
	while (game->map[row])
	{
		col = 0;
		while (game->map[row][col])
		{
			if (game->map[row][col] == '1')
			{
				if (!print_images(game, "./images/walls.xpm",
						col * 98, row * 98))
				{
					ft_printf("Error\nFailed to render wall at row %d,col %d\n",
						row, col);
					return (0);
				}
			}
			col++;
		}
		row++;
	}
	return (1);
}

int	check_valid_characters(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (game->map[y][x] != '\0')
		{
			if (game->map[y][x] != '0' && game->map[y][x] != '1' &&
				game->map[y][x] != 'P' && game->map[y][x] != 'C' &&
				game->map[y][x] != 'E' && game->map[y][x] != '\n')
			{
				ft_printf("Error\nInvalid character found\n");
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	render_game(t_game *game)
{
	int	row;
	int	col;

	row = 0;
	render_player(game);
	while (game->map[row])
	{
		col = 0;
		while (game->map[row][col])
		{
			if (game->map[row][col] == '0')
				print_images(game, "./images/background.xpm",
					col * 98, row * 98);
			else if (game->map[row][col] == 'C')
				print_images(game, "./images/items.xpm",
					col * 98, row * 98);
			else if (game->map[row][col] == 'E')
				print_images(game, "./images/exit.xpm",
					col * 98, row * 98);
			col++;
		}
		row++;
	}
	return (1);
}
