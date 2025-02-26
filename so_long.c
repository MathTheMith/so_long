/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:11:19 by math              #+#    #+#             */
/*   Updated: 2025/02/26 03:25:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void cleanup(t_game *game)
{
    if (game)
    {
        if (game->win && game->mlx)
            mlx_destroy_window(game->mlx, game->win);
        if (game->map)
            free_map(game->map);
        if (game->mlx)
        {
            mlx_destroy_display(game->mlx);
            free(game->mlx);
        }
    }
}

int close_window(void *param)
{
    t_game *game;

    game = (t_game *)param;
    printf("%s", "The game was closed");
    cleanup(game);
    exit(0);
    return (0);
}

void initialize_game(t_game *game, void *mlx, char **map, int game_width, int game_height)
{
    int     final_width;
    int     final_height;
    if (!mlx)
    {
        ft_printf("Error\nmlx is NULL\n");
        exit(1);
    }
    final_width = game_width * 98;
    final_height = game_height * 98;
    game->mlx = mlx;
    game->map = map;
    game->width = game_width;
    game->height = game_height;
    game->last_direction = 1;
    game->win = mlx_new_window(mlx, final_width, final_height, "So_long");
    if (!game->win)
    {
        ft_printf("Error\nmlx_new_window() failed\n");
        exit(1);
    }
}

int main(void)
{
    void *mlx;
    char **map;
    int game_width;
    int game_height;
    t_game game;
    mlx = mlx_init();
    if (!mlx)
    {
        ft_printf("Error\nmlx_init() failed\n");
        return (1);
    }
    
    if (!initialize_map(&map, &game_width, &game_height))
        return (1);
    if (game_width <= 2 && game_height <= 2)
    {
        ft_printf("Error\nthe map is too small");
        return (1);
    }
    if (!setup_game(&game, mlx, map, game_width, game_height))
        return (1);
    mlx_loop(mlx);
    return (0);
}