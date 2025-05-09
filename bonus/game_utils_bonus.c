/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 06:56:59 by marvin            #+#    #+#             */
/*   Updated: 2025/04/11 06:56:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	validate_game_map(t_game *game)
{
	if (!check_borders(game))
	{
		ft_printf("Error\nThe walls aren't working properly\n");
		return (0);
	}
	if (!check_objects(game))
	{
		ft_printf("Error\nThere are not the right number of objects\n");
		return (0);
	}
	if (!check_valid_characters(game))
		return (0);
	if (!validate_path(game))
	{
		ft_printf("Error\nNo valid path in the game->map\n");
		return (0);
	}
	return (1);
}

int	setup_game_rendering(t_game *game)
{
	if (!render_static_map(game))
	{
		ft_printf("Error\nThe walls weren't rendered properly\n");
		return (0);
	}
	if (!render_game(game))
	{
		ft_printf("Error\nThe map is too small\n");
		return (0);
	}
	if (!mlx_key_hook(game->win, handle_keypress, game))
	{
		ft_printf("Error\n mlx_key_hook is NULL\n");
		return (0);
	}
	mlx_hook(game->win, 17, 0, close_window, game);
	return (1);
}

int	initialize_map(t_game *game, char **av)
{
	if (!check_ber_extension(av[1]))
	{
		ft_printf("Error\nBad extension\n");
		return (0);
	}
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

int	check_ber_extension(const char *filename)
{
	size_t		len;
	const char	*last_slash;

	if (!filename)
		return (0);
	last_slash = ft_strrchr(filename, '/');
	if (!last_slash)
		last_slash = filename;
	if (last_slash[1] == '.')
		return (0);
	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	if (ft_strcmp(last_slash + ft_strlen(last_slash) - 4, ".ber") != 0)
		return (0);
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
