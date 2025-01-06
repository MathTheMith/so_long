/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:57:29 by math              #+#    #+#             */
/*   Updated: 2024/12/12 23:06:27 by math             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void move_monster(t_game *game, void *param)
{
	int row = 0, col;
	static int direction = 1;

	while (row < game->height)
	{
		col = 0;
		while (col < game->width)
		{
			if (game->map[row][col] == 'M')
			{
				int new_col = col + direction;

				if (new_col >= 0 && new_col < game->width && game->map[row][new_col] != '1')
				{
					if (game->map[row][new_col] == 'P')
					{
						printf("You are dead \n");
						close_window(param);
						return ;
					}
					if (game->map[row][new_col] != '0')
					{
						direction = -direction;
						return ;
					}
					game->map[row][col] = '0';
					game->map[row][new_col] = 'M';
					render_game(game, game->win);
					return ;
				}
				else
				{
					direction = -direction;
					return ;
				}
			}
			col++;
		}
		row++;
	}
}
void render_player(t_game *game, void *win)
{
    char *player_img;
    int row, col;

    row = 0;
    while (row < game->height)
    {
        col = 0;
        while (col < game->width)
        {
            if (game->map[row][col] == 'P')
            {
                game->player_x = col;
                game->player_y = row;
                break;
            }
            col++;
        }
        row++;
    }

    if (game->last_direction == -1)
        player_img = "./images/player_left.xpm";
    else
        player_img = "./images/player_right.xpm";

    print_images(game->mlx, win, player_img, game->player_x * 98, game->player_y * 98, 98, 98);
}
