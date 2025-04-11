/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_functions_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:07:00 by math              #+#    #+#             */
/*   Updated: 2025/04/11 18:30:44 by mvachon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	check_middle_lines(t_game *game, int row, int col)
{
	if ((int)ft_strlen(game->map[row]) < col + 1)
		return (0);
	if (game->map[row][0] != '1' || game->map[row][col - 1] != '1'
	|| game->map[row][col] != '\n')
		return (0);
	return (1);
}

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
		if (!check_middle_lines(game, row, col))
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
