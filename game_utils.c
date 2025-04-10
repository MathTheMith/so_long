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

int	validate_game_map(t_game *game)
{
	if (!check_borders(game))
	{
		ft_printf("%s", "Error\nThe walls aren't working properly\n");
		return (0);
	}
	if (!check_objects(game))
	{
		ft_printf("%s", "Error\nThere are not the right number of objects\n");
		return (0);
	}
	if (!check_valid_characters(game))
		return (0);
	if (!validate_path(game))
	{
		ft_printf("%s", "Error\nNo valid path in the game->map\n");
		return (0);
	}
	return (1);
}

int	setup_game_rendering(t_game *game)
{
	if (!render_static_map(game))
	{
		ft_printf("%s", "Error\nThe walls weren't rendered properly");
		return (0);
	}
	if (!render_game(game))
	{
		ft_printf("%s", "Error\nThe map is too small\n");
		return (0);
	}
	if (!mlx_key_hook(game->win, handle_keypress, game))
		return (0);
	mlx_hook(game->win, 17, 0, close_window, game);
	return (1);
}

int	initialize_map(t_game *game, char **av)
{
	game->map = read_map(av[1]);
	if (!game->map)
	{
		ft_printf("Error\nThis map doesnt exist\n");
		return (0);
	}
	game->width = ft_strlen((game->map)[0]);
	game->height = 0;
	while ((game->map)[game->height])
		(game->height)++;
	return (1);
}

int	setup_game(t_game *game)
{
	initialize_game(game);
	if (!validate_game_map(game))
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
