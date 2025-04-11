/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:55:02 by math              #+#    #+#             */
/*   Updated: 2024/12/12 22:55:02 by math             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	process_movement(t_game *game, int keycode, int *player_step)
{
	if (!is_movement_key(keycode) || !is_valid_move(game))
		return (0);
	if (check_game_end(game,*player_step))
		return (0);
	render_player(game);
	handle_jump_animation(game, keycode);
	handle_movement(game, player_step);
	return (1);
}

int	handle_keypress(int keycode, void *param)
{
	t_game		*game;
	static int	player_step = 0;

	game = (t_game *)param;
	game->new_x = game->player_x;
	game->new_y = game->player_y;
	if (keycode == KEY_ESC)
	{
		close_window(param);
		return (1);
	}
	process_key_direction(keycode, game);
	process_movement(game, keycode, &player_step);
	return (1);
}
