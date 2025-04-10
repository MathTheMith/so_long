/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:07:00 by math              #+#    #+#             */
/*   Updated: 2025/04/10 06:21:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_borders(t_game *game)
{
	int	row;
	int	col;
	int	len;

	row = 0;
	col = 0;
	while (game->map[0][col] && game->map[0][col] == '1')
		col++;
	if (game->map[0][col] != '\n')
		return (0);
	row++;
	len = col;
	while (game->map[row + 1])
	{
		if (game->map[row][0] != '1' || game->map[row][col - 1] != '1'
		|| game->map[row][col] != '\n')
			return (0);
		row++;
	}
	col = 0;
	while (game->map[row] && game->map[row][col] && game->map[row][col] == '1')
		col++;
	if (col != len || game->map[row][col] != '\0')
		return (0);
	return (1);
}

void	count_objects(t_game *game, t_object_count *count)
{
	int	row;
	int	col;

	row = 0;
	count->count_e = 0;
	count->count_p = 0;
	count->count_c = 0;
	while (game->map[row])
	{
		col = 0;
		while (game->map[row][col])
		{
			if (game->map[row][col] == 'E')
				count->count_e++;
			else if (game->map[row][col] == 'P')
				count->count_p++;
			else if (game->map[row][col] == 'C')
				count->count_c++;
			col++;
		}
		row++;
	}
}

int	check_objects(t_game *game)
{
	t_object_count	count;

	count_objects(game, &count);
	if (count.count_e != 1 || count.count_p != 1 || count.count_c < 1)
		return (0);
	return (count.count_c);
}

int	check_collectibles_without_exit(t_game *game)
{
	char	**map_copy;

	game->exit = 0;
	map_copy = duplicate_map(game);
	if (!map_copy)
		return (0);
	replace_exit_with_wall(map_copy, game);
	game->collectibles = count_collectibles(game);
	find_player_position(game);
	flood_fill(map_copy, game->player_x, game->player_y, game);
	free_map(map_copy);
	return (game->collectibles == 0);
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
