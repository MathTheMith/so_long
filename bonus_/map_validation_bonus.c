/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 06:57:05 by marvin            #+#    #+#             */
/*   Updated: 2025/04/11 06:57:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	flood_fill(char **map, int x, int y, t_game *game)
{
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	if (map[y][x] == 'C')
		(game->collectibles)--;
	if (map[y][x] == 'E')
		game->exit = 1;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y, game);
	flood_fill(map, x - 1, y, game);
	flood_fill(map, x, y + 1, game);
	flood_fill(map, x, y - 1, game);
}

int	count_collectibles(t_game *game)
{
	int	x;
	int	y;
	int	collectibles;

	collectibles = 0;
	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map[y][x] == 'C')
				collectibles++;
			x++;
		}
		y++;
	}
	return (collectibles);
}

void	replace_exit_with_wall(char **map, t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'E')
				map[y][x] = '1';
			x++;
		}
		y++;
	}
}

int	validate_path(t_game *game)
{
	char	**map_copy;

	if (!check_collectibles_without_exit(game))
		return (0);
	game->collectibles = count_collectibles(game);
	game->exit = 0;
	map_copy = duplicate_map(game);
	if (!map_copy)
		return (0);
	find_player_position(game);
	flood_fill(map_copy, game->player_x, game->player_y, game);
	free_map(map_copy);
	return (game->collectibles == 0 && game->exit);
}

char	**duplicate_map(t_game *game)
{
	int		i;
	char	**copy;

	copy = malloc(sizeof(char *) * (game->height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < game->height)
	{
		copy[i] = strdup(game->map[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[game->height] = NULL;
	return (copy);
}
