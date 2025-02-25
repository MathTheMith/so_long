/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:11:19 by math              #+#    #+#             */
/*   Updated: 2025/02/26 00:50:06 by marvin           ###   ########.fr       */
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
// #include "so_long.h"

// #define KEY_W 119
// #define KEY_A 97
// #define KEY_S 115
// #define KEY_D 100
// #define KEY_ESC 65307

// int	close_window(void *param)
// {
// 	printf("%s", "The game was closed");
// 	(void)param;
// 	exit(0);
// }

// int	print_images(void *mlx, void *win, char *link_img, int x, int y, int img_width, int img_height)
// {
// 	void	*img;
// 	int		width;
// 	int		height;

// 	width = img_width;
// 	height = img_height;
// 	img = mlx_xpm_file_to_image(mlx, link_img, &width, &height);
// 	if (!img)
// 	{
// 		printf("ERROR: Image failed to load. Path: %s\n", link_img);
// 		perror("Image load error");
// 		return (0);
// 	}
// 	mlx_put_image_to_window(mlx, win, img, x, y);
// 	mlx_destroy_image(mlx, img);
// 	return (1);
// }

// void flood_fill(char **map, int x, int y, int *collectibles, int *exit_found)
// {
// 	if (map[y][x] == '1' || map[y][x] == 'F' || map[y][x] == 'M')
// 		return;
// 	if (map[y][x] == 'C')
// 		(*collectibles)--;  
// 	if (map[y][x] == 'E')
// 		*exit_found = 1;
// 	map[y][x] = 'F';
// 	flood_fill(map, x + 1, y, collectibles, exit_found);
// 	flood_fill(map, x - 1, y, collectibles, exit_found);
// 	flood_fill(map, x, y + 1, collectibles, exit_found);
// 	flood_fill(map, x, y - 1, collectibles, exit_found);
// }

// int count_collectibles(char **map, int width, int height)
// {
// 	int x;
// 	int y;
// 	int collectibles;

// 	collectibles = 0;
// 	y = 0;
// 	while (y < height)
// 	{
// 	    x = 0;
// 	    while (x < width)
// 	    {
// 	        if (map[y][x] == 'C')
// 	            collectibles++;
// 	        x++;
// 	    }
// 	    y++;
// 	}
// 	return (collectibles);
// }

// void find_player_position(char **map, int width, int height, int *player_x, int *player_y)
// {
//     int x;
//     int y;

//     y = 0;
//     while (y < height)
//     {
//         x = 0;
//         while (x < width)
//         {
//             if (map[y][x] == 'P')
//             {
//                 *player_x = x;
//                 *player_y = y;
//                 return;
//             }
//             x++;
//         }
//         y++;
//     }
// }

// int validate_path(char **map, int width, int height)
// {
//     int     collectibles;
//     int     exit_found;
//     int     player_x;
//     int     player_y;
//     char    **map_copy;

//     collectibles = count_collectibles(map, width, height);
//     exit_found = 0;
//     map_copy = duplicate_map(map, height);
//     if (!map_copy)
//         return (0);
//     find_player_position(map, width, height, &player_x, &player_y);
//     flood_fill(map_copy, player_x, player_y, &collectibles, &exit_found);
//     free_map(map_copy);
//     return (collectibles == 0 && exit_found);
// }

// char **duplicate_map(char **map, int height)
// {
//     int     i;
//     char    **copy;

//     copy = malloc(sizeof(char *) * (height + 1));
//     if (!copy)
//         return (NULL);
//     i = 0;
//     while (i < height)
//     {
//         copy[i] = strdup(map[i]);
//         if (!copy[i])
//         {
//             while (--i >= 0)
//                 free(copy[i]);
//             free(copy);
//             return (NULL);
//         }
//         i++;
//     }
//     copy[height] = NULL;
//     return (copy);
// }

// void render_jump_animation(t_game *game, void *jump_sprite)
// {
//     int i;

//     i = 0;
//     while (i < 10)
//     {
//         mlx_put_image_to_window(game->mlx, game->win, jump_sprite, 
//             game->player_x * 98, game->player_y * 98);
//         mlx_do_sync(game->mlx);
//         usleep(7000);
//         i++;
//     }
// }

// void render_jump(t_game *game, int left_right)
// {
//     void    *jump_sprite;
//     int     width;
//     int     height;

//     width = 64;
//     height = 64;
//     jump_sprite = NULL;
//     if (left_right == 1)
//         jump_sprite = mlx_xpm_file_to_image(game->mlx, 
//             "./images/player_jump_left.xpm", &width, &height);
//     else
//         jump_sprite = mlx_xpm_file_to_image(game->mlx, 
//             "./images/player_jump.xpm", &width, &height);

//     if (!jump_sprite)
//     {
//         printf("Error: Failed to load jump sprite\n");
//         return;
//     }

//     render_jump_animation(game, jump_sprite);
//     mlx_destroy_image(game->mlx, jump_sprite);
// }

// void handle_movement(t_game *game, int new_x, int new_y, int *player_step)
// {
//     game->map[game->player_y][game->player_x] = '0';
//     game->map[new_y][new_x] = 'P';
//     game->player_x = new_x;
//     game->player_y = new_y;
//     (*player_step)++;
//     render_game(game, game->win);
//     move_monster(game, game);
//     render_steps_with_background(game->mlx, game->win, *player_step);
// }

// int check_game_end(t_game *game, int new_x, int new_y, int player_step)
// {
//     if (game->map[new_y][new_x] == 'M')
//     {
//         printf("You are dead in %d moves\n", player_step);
//         close_window(game);
//         return (1);
//     }

//     if (game->map[new_y][new_x] == 'E' && !check_objects(game->map))
//     {
//         printf("Bien joué ! Tu as fini en %d moves\n", player_step);
//         close_window(game);
//         return (1);
//     }

//     return (0);
// }

// void handle_jump_animation(t_game *game, int keycode)
// {
//     if (keycode == KEY_A)
//     {
//         render_jump(game, 1);
//     }
//     else if (keycode == KEY_W || keycode == KEY_S)
//     {
//         if (game->last_direction == -1)
//             render_jump(game, 1);
//         else
//             render_jump(game, 0);
//     }
//     else if (keycode == KEY_D)
//     {
//         render_jump(game, 0);
//     }
// }

// void process_key_direction(int keycode, t_game *game, int *new_x, int *new_y)
// {
//     if (keycode == KEY_W)
//         (*new_y)--;
//     else if (keycode == KEY_A)
//     {
//         (*new_x)--;
//         game->last_direction = -1;
//     }
//     else if (keycode == KEY_D)
//     {
//         (*new_x)++;
//         game->last_direction = 1;
//     }
//     else if (keycode == KEY_S)
//         (*new_y)++;
// }

// int is_movement_key(int keycode)
// {
//     return (keycode == KEY_W || keycode == KEY_A || 
//             keycode == KEY_S || keycode == KEY_D);
// }

// int is_valid_move(t_game *game, int new_x, int new_y)
// {
//     if (new_x < 0 || new_x >= game->width || 
//         new_y < 0 || new_y >= game->height || 
//         game->map[new_y][new_x] == '1')
//     {
//         return (0);
//     }
//     return (1);
// }

// int process_movement(t_game *game, int keycode, int new_x, int new_y, int *player_step)
// {
//     if (!is_movement_key(keycode) || !is_valid_move(game, new_x, new_y))
//     {
//         if (is_movement_key(keycode))
//             move_monster(game, game);
//         return (0);
//     }

//     if (check_game_end(game, new_x, new_y, *player_step))
//         return (0);

//     render_player(game, game->win);
//     handle_jump_animation(game, keycode);
//     handle_movement(game, new_x, new_y, player_step);

//     return (1);
// }

// int handle_keypress(int keycode, void *param)
// {
//     t_game *game;
//     int new_x;
//     int new_y;
//     static int player_step = 0;

//     game = (t_game *)param;
//     new_x = game->player_x;
//     new_y = game->player_y;

//     if (keycode == KEY_ESC)
//     {
//         close_window(param);
//         return (1);
//     }

//     process_key_direction(keycode, game, &new_x, &new_y);
//     process_movement(game, keycode, new_x, new_y, &player_step);

//     return (1);
// }

// void initialize_game(t_game *game, void *mlx, char **map, int game_width, int game_height)
// {
//     int     final_width;
//     int     final_height;
//     void    *win;
    
//     final_width = game_width * 98;
//     final_height = game_height * 98;
//     win = mlx_new_window(mlx, final_width - 98, final_height, "So_long");
//     game->mlx = mlx;
//     game->map = map;
//     game->width = game_width;
//     game->height = game_height;
//     game->win = win;
//     game->last_direction = 1;
// }

// int validate_game_map(char **map, int game_width, int game_height)
// {
//     if (!validate_path(map, game_width, game_height))
//     {
//         ft_printf("%s", "No valid path in the map\n");
//         return (0);
//     }
//     if (!check_borders(map))
//     {
//         ft_printf("%s", "The walls aren't working properly\n");
//         return (0);
//     }
//     if (!check_objects(map))
//     {
//         ft_printf("%s", "There are not the right number of objects\n");
//         return (0);
//     }
//     return (1);
// }

// int setup_game_rendering(t_game *game)
// {
//     if (!render_static_map(game, game->win))
//     {
//         ft_printf("%s", "The walls weren't rendered properly");
//         return (0);
//     }
//     if (!render_game(game, game->win))
//     {
//         ft_printf("%s", "The map is too small\n");
//         return (0);
//     }
//     if (!mlx_key_hook(game->win, handle_keypress, game))
//         return (0);
//     mlx_hook(game->win, 17, 0, close_window, NULL);
//     return (1);
// }

// int main(void)
// {
//     void *mlx;
//     char **map;
//     int game_width;
//     int game_height;
//     t_game game;
    
//     mlx = mlx_init();
//     map = read_map("carte.ber");
//     if (!map)
//     {
//         ft_printf("%s", "The map isn't working properly");
//         return (0);
//     }
//     game_width = ft_strlen(map[0]);
//     game_height = 0;
//     while (map[game_height])
//         game_height++;
//     initialize_game(&game, mlx, map, game_width, game_height);
//     if (!validate_game_map(map, game_width, game_height))
//         return (0);
//     if (!setup_game_rendering(&game))
//         return (0);
//     mlx_loop(mlx);
//     return (0);
// }