/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:11:19 by math              #+#    #+#             */
/*   Updated: 2025/04/14 08:27:14 by mvachon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	cleanup(t_game *game)
{
	if (game)
	{
		if (game->win && game->mlx)
			mlx_destroy_window(game->mlx, game->win);
		if (game->map)
		{
			free_map(game->map);
			game->map = NULL;
		}
		if (game->mlx)
		{
			mlx_destroy_display(game->mlx);
			free(game->mlx);
		}
	}
}

int	close_window(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	ft_printf("%s", "The game was closed");
	cleanup(game);
	exit(0);
	return (0);
}

void	initialize_game(t_game *game)
{
	int	final_width;
	int	final_height;

	final_width = game->width * 98;
	final_height = game->height * 98;
	if (game->width < 3 || game->height < 3
		|| final_height > 2160 || final_width > 3840)
	{
		ft_printf("Error\nThe map is too small/big\n");
		cleanup(game);
		exit(1);
	}
	game->width = game->width;
	game->height = game->height;
	game->last_direction = 1;
	game->win = mlx_new_window(game->mlx, final_width - 98,
			final_height, "So_long");
	if (!game->win)
	{
		ft_printf("Error\nmlx_new_window() failed\n");
		cleanup(game);
		exit(1);
	}
}

int	main(int ac, char **av)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (ac != 2)
	{
		ft_printf("Error\nUsage: %s <map_file>\n", av[0]);
		return (1);
	}
	if (!check_ber_extension(av[1]))
		return (ft_printf("Error\nBad extension\n"), 1);
	if (!initialize_map(&game, av))
		return (1);
	game.mlx = mlx_init();
	if (!game.mlx)
	{
		ft_printf("Error\nmlx_init() failed\n");
		free_map(game.map);
		return (1);
	}
	if (!setup_game(&game))
		return (1);
	mlx_loop(game.mlx);
	cleanup(&game);
	return (0);
}
