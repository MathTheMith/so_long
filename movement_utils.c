/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:55:02 by math              #+#    #+#             */
/*   Updated: 2024/12/12 22:55:02 by math             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	handle_movement(t_game *game, int *player_step)
{
	game->map[game->player_y][game->player_x] = '0';
	game->map[game->new_y][game->new_x] = 'P';
	game->player_x = game->new_x;
	game->player_y = game->new_y;
	(*player_step)++;
	render_game(game);
	ft_printf("Steps: %d\n", *player_step);
}

int	check_game_end(t_game *game, int player_step)
{
	if (game->map[game->new_y][game->new_x] == 'E' && !check_objects(game))
	{
		printf("Well played !! You finished in %d moves\n", player_step);
		close_window(game);
		return (1);
	}
	return (0);
}

void	process_key_direction(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		(game->new_y)--;
	else if (keycode == KEY_A)
	{
		(game->new_x)--;
		game->last_direction = -1;
	}
	else if (keycode == KEY_D)
	{
		(game->new_x)++;
		game->last_direction = 1;
	}
	else if (keycode == KEY_S)
		(game->new_y)++;
}

int	is_movement_key(int keycode)
{
	return (keycode == KEY_W || keycode == KEY_A
		|| keycode == KEY_S || keycode == KEY_D);
}

int	is_valid_move(t_game *game)
{
	if (game->map[game->new_y][game->new_x] == 'E' && check_objects(game))
		return (0);
	if (game->new_x < 0 || game->new_x >= game->width
		|| game->new_y < 0 || game->new_y >= game->height
		|| game->map[game->new_y][game->new_x] == '1')
		return (0);
	return (1);
}
