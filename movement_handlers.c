/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_handlers_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 06:57:19 by marvin            #+#    #+#             */
/*   Updated: 2025/04/11 06:57:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	process_movement(t_game *game, int keycode, int *player_step)
{
	if (!is_movement_key(keycode) || !is_valid_move(game))
		return (0);
	if (check_game_end(game,*player_step))
		return (0);
	render_player(game);
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
