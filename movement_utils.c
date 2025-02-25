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

void handle_movement(t_game *game, int new_x, int new_y, int *player_step)
{
    game->map[game->player_y][game->player_x] = '0';
    game->map[new_y][new_x] = 'P';
    game->player_x = new_x;
    game->player_y = new_y;
    (*player_step)++;
    render_game(game, game->win);
    move_monster(game, game);
    render_steps_with_background(game->mlx, game->win, *player_step);
}

int check_game_end(t_game *game, int new_x, int new_y, int player_step)
{
    if (game->map[new_y][new_x] == 'M')
    {
        printf("You are dead in %d moves\n", player_step);
        close_window(game);
        return (1);
    }

    if (game->map[new_y][new_x] == 'E' && !check_objects(game->map))
    {
        printf("Bien joué ! Tu as fini en %d moves\n", player_step);
        close_window(game);
        return (1);
    }

    return (0);
}

void process_key_direction(int keycode, t_game *game, int *new_x, int *new_y)
{
    if (keycode == KEY_W)
        (*new_y)--;
    else if (keycode == KEY_A)
    {
        (*new_x)--;
        game->last_direction = -1;
    }
    else if (keycode == KEY_D)
    {
        (*new_x)++;
        game->last_direction = 1;
    }
    else if (keycode == KEY_S)
        (*new_y)++;
}

int is_movement_key(int keycode)
{
    return (keycode == KEY_W || keycode == KEY_A || 
            keycode == KEY_S || keycode == KEY_D);
}

int is_valid_move(t_game *game, int new_x, int new_y)
{
    if (new_x < 0 || new_x >= game->width || 
        new_y < 0 || new_y >= game->height || 
        game->map[new_y][new_x] == '1')
    {
        return (0);
    }
    return (1);
}