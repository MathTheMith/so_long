/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2025/02/26 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	validate_game_map(char **map, int game_width, int game_height)
{
	if (!check_borders(map))
	{
		ft_printf("%s", "Error\nThe walls aren't working properly\n");
		return (0);
	}
	if (!check_objects(map))
	{
		ft_printf("%s", "Error\nThere are not the right number of objects\n");
		return (0);
	}
	if (!check_valid_characters(map, game_height))
		return (0);
	if (!validate_path(map, game_width, game_height))
	{
		ft_printf("%s", "Error\nNo valid path in the map\n");
		return (0);
	}
	return (1);
}

int	setup_game_rendering(t_game *game)
{
	if (!render_static_map(game, game->win))
	{
		ft_printf("%s", "Error\nThe walls weren't rendered properly");
		return (0);
	}
	if (!render_game(game, game->win))
	{
		ft_printf("%s", "Error\nThe map is too small\n");
		return (0);
	}
	if (!mlx_key_hook(game->win, handle_keypress, game))
		return (0);
	mlx_hook(game->win, 17, 0, close_window, game);
	return (1);
}

int	initialize_map(char ***map, int *width, int *height)
{
	*map = read_map("carte.ber"); //av[1]
	if (!*map)
	{
		ft_printf("Error\nThe map isn't working properly\n");
		return (0);
	}
	*width = ft_strlen((*map)[0]);
	*height = 0;
	while ((*map)[*height])
		(*height)++;
	return (1);
}

int	setup_game(t_game *game, void *mlx, char **map, int width, int height)
{
	initialize_game(game, mlx, map, width, height);
	if (!validate_game_map(map, width, height))
	{
		cleanup(game);
		return (0);
	}
	if (!setup_game_rendering(game))
	{
		cleanup(game);
		return (0);
	}
	return (1);
}
