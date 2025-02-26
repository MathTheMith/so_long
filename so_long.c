/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:11:19 by math              #+#    #+#             */
/*   Updated: 2025/02/26 01:44:32 by marvin           ###   ########.fr       */
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
    game->win = mlx_new_window(mlx, final_width - 98, final_height, "So_long");
    if (!game->win)
    {
        ft_printf("Error\nmlx_new_window() failed\n");
        exit(1);
    }
}


int validate_game_map(char **map, int game_width, int game_height)
{
    if (!validate_path(map, game_width, game_height))
    {
        ft_printf("%s", "Error\nNo valid path in the map\n");
        return (0);
    }
    if (!check_borders(map))
    {
        ft_printf("%s", "Error\nThe walls aren't working properly\n");
        return (0);
    }
    if (!check_objects(map))
    {
        ft_printf("%s", "Error\nThere are not the right number of objects\n");
        return (0);
    }
    return (1);
}

int setup_game_rendering(t_game *game)
{
    if (!render_static_map(game, game->win))
    {
        ft_printf("%s", "Error\nThe walls weren't rendered properly");
        return (0);
    }
    if (!render_game(game, game->win))
    {
        ft_printf("%s", "Error\nThe map is too small\n");
        return (0);
    }
    if (!mlx_key_hook(game->win, handle_keypress, game))
        return (0);
    mlx_hook(game->win, 17, 0, close_window, game);
    return (1);
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
    map = read_map("carte.ber");
    if (!map)
    {
        ft_printf("Error\nThe map isn't working properly\n");
        return (1);
    }
    game_width = ft_strlen(map[0]);
    game_height = 0;
    while (map[game_height])
        game_height++;
    initialize_game(&game, mlx, map, game_width, game_height);
    if (!validate_game_map(map, game_width, game_height))
    {
        cleanup(&game);
        return (1);
    }
    if (!setup_game_rendering(&game))
    {
        cleanup(&game);
        return (1);
    }
    mlx_loop(mlx);
    return (0);
}
