/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:11:19 by math              #+#    #+#             */
/*   Updated: 2025/02/26 00:58:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:11:19 by math              #+#    #+#             */
/*   Updated: 2024/12/12 22:55:02 by math             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_window(void *param)
{
	printf("%s", "The game was closed");
	(void)param;
	exit(0);
}

void initialize_game(t_game *game, void *mlx, char **map, int game_width, int game_height)
{
    int     final_width;
    int     final_height;
    void    *win;
    
    final_width = game_width * 98;
    final_height = game_height * 98;
    win = mlx_new_window(mlx, final_width - 98, final_height, "So_long");
    game->mlx = mlx;
    game->map = map;
    game->width = game_width;
    game->height = game_height;
    game->win = win;
    game->last_direction = 1;
}

int validate_game_map(char **map, int game_width, int game_height)
{
    if (!validate_path(map, game_width, game_height))
    {
        ft_printf("%s", "No valid path in the map\n");
        return (0);
    }
    if (!check_borders(map))
    {
        ft_printf("%s", "The walls aren't working properly\n");
        return (0);
    }
    if (!check_objects(map))
    {
        ft_printf("%s", "There are not the right number of objects\n");
        return (0);
    }
    return (1);
}

int setup_game_rendering(t_game *game)
{
    if (!render_static_map(game, game->win))
    {
        ft_printf("%s", "The walls weren't rendered properly");
        return (0);
    }
    if (!render_game(game, game->win))
    {
        ft_printf("%s", "The map is too small\n");
        return (0);
    }
    if (!mlx_key_hook(game->win, handle_keypress, game))
        return (0);
    mlx_hook(game->win, 17, 0, close_window, NULL);
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
    map = read_map("carte.ber");
    if (!map)
    {
        ft_printf("%s", "The map isn't working properly");
        return (0);
    }
    game_width = ft_strlen(map[0]);
    game_height = 0;
    while (map[game_height])
        game_height++;
    initialize_game(&game, mlx, map, game_width, game_height);
    if (!validate_game_map(map, game_width, game_height))
        return (0);
    if (!setup_game_rendering(&game))
        return (0);
    mlx_loop(mlx);
    return (0);
}