/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:57:29 by math              #+#    #+#             */
/*   Updated: 2025/02/26 00:58:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void check_monster_collision(t_game *game, int row, int new_col, void *param)
{
    if (game->map[row][new_col] == 'P')
    {
        printf("You are dead \n");
        close_window(param);
        return;
    }
}

int handle_monster_movement(t_game *game, int row, int col, int *direction, void *param)
{
    int new_col;
    
    new_col = col + *direction;
    if (new_col >= 0 && new_col < game->width && game->map[row][new_col] != '1')
    {
        check_monster_collision(game, row, new_col, param);
        
        if (game->map[row][new_col] != '0')
        {
            *direction = -*direction;
            return (0);
        }
        game->map[row][col] = '0';
        game->map[row][new_col] = 'M';
        render_game(game, game->win);
        return (1);
    }
    else
    {
        *direction = -*direction;
        return (0);
    }
}

void move_monster(t_game *game, void *param)
{
    int row;
    int col;
    static int direction = 1;
    
    row = 0;
    while (row < game->height)
    {
        col = 0;
        while (col < game->width)
        {
            if (game->map[row][col] == 'M')
            {
                if (handle_monster_movement(game, row, col, &direction, param))
                    return;
                return;
            }
            col++;
        }
        row++;
    }
}

void find_player_position_for_render(t_game *game)
{
    int row;
    int col;
    
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
                return;
            }
            col++;
        }
        row++;
    }
}

void render_player(t_game *game, void *win)
{
    char *player_img;
    
    find_player_position_for_render(game);
    
    if (game->last_direction == -1)
        player_img = "./images/player_left.xpm";
    else
        player_img = "./images/player_right.xpm";
    
    print_images(game->mlx, win, player_img, 
                game->player_x * 98, game->player_y * 98);
}