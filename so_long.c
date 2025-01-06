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

#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_ESC 65307

int close_window(void *param)
{
	printf("%s", "The game was closed");
	(void)param;
	exit(0);
}
int print_images(void *mlx, void *win, char *link_img, int x, int y, int img_width, int img_height)
{
    void *img;
    int width = img_width;
    int height = img_height;

    img = mlx_xpm_file_to_image(mlx, link_img, &width, &height);
    if (!img)
    {
        printf("ERROR: Image failed to load. Path: %s\n", link_img);
        perror("Image load error");
        return (0);
    }

    mlx_put_image_to_window(mlx, win, img, x, y);
    mlx_destroy_image(mlx, img);
    return (1);
}

void render_jump(t_game *game, int left_right)
{
    void *jump_sprite;
    int width = 64, height = 64;
    int i;

    if (left_right == 1)
        jump_sprite = mlx_xpm_file_to_image(game->mlx, "./images/player_jump_left.xpm", &width, &height);
    else
        jump_sprite = mlx_xpm_file_to_image(game->mlx, "./images/player_jump.xpm", &width, &height);
    
    if (!jump_sprite) {
        printf("Error: Failed to load jump sprite\n");
        return;
    }

    for (i = 0; i < 10; i++) {
        mlx_put_image_to_window(game->mlx, game->win, jump_sprite, game->player_x * 98, game->player_y * 98);
        mlx_do_sync(game->mlx);
        usleep(7000);
    }
    
    mlx_destroy_image(game->mlx, jump_sprite);
}

int handle_keypress(int keycode, void *param) {
    t_game *game = (t_game *)param;
    int new_x = game->player_x;
    int new_y = game->player_y;
    static int player_step = 0;

    if (keycode == KEY_W) {
        new_y--;
    } else if (keycode == KEY_A) {
        new_x--;
        game->last_direction = -1;
    } else if (keycode == KEY_D) {
        new_x++;
        game->last_direction = 1;
    } else if (keycode == KEY_S )
        new_y++;
    if (keycode == KEY_ESC)
    {
        close_window(param);
        return 1; 
    } 


    if (new_x < 0 || new_x >= game->width || new_y < 0 || new_y >= game->height || game->map[new_y][new_x] == '1') {
        move_monster(game, param);
        return 1;
    }

    if (game->map[new_y][new_x] == 'M') {
        printf("You are dead in %d moves\n", player_step);
        close_window(param);
        return 0;
    }
    if (game->map[new_y][new_x] == 'E' && !check_objects(game->map)) {
        printf("Bien joué ! Tu as fini en %d moves\n", player_step);
        close_window(param);
        return 0;
    }

    render_player(game, game->win);

    if (keycode == KEY_A)
        render_jump(game, 1);
    if (keycode == KEY_W)
    {
        if (game->last_direction == -1)
            render_jump(game, 1);
        else
            render_jump(game, 0); 
    }
    if (keycode == KEY_D)
        render_jump(game, 0);
    game->map[game->player_y][game->player_x] = '0';
    game->map[new_y][new_x] = 'P';
    game->player_x = new_x;
    game->player_y = new_y;
    player_step++;
    render_game(game, game->win);

    move_monster(game, param);
    render_steps_with_background(game->mlx, game->win, player_step);
    return 1;
}




int main(void)
{
    void    *mlx;
    void    *win;
    char    **map;
    int screen_width = 2560;  
    int screen_height = 1440; 
    int game_width; 
    int game_height;
    int final_width;
    int final_height;
    int img_width = 98;
    int img_height = 98;
    t_game game;

    mlx = mlx_init();
    map = read_map("carte.ber");
    if (!map)
    {
        ft_printf("%s", "The map isn't working properly", 7);
        return (0);
    }
    game_width = ft_strlen(map[0]);
    game_height = 0;
    while (map[game_height])
        game_height++;
    final_width = game_width * img_width;
    final_height = game_height * img_height;

    if (final_width > screen_width || final_height > screen_height)
    {
        ft_printf("%s", "Map too big\n");
        return (0);
    }
    win = mlx_new_window(mlx, final_width - 98, final_height, "So_long");
    game.mlx = mlx;
    game.map = map;
    game.width = game_width;
    game.height = game_height;
    game.win = win;





    game.last_direction = 1;

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
    if (!render_static_map(&game, win))
    {
        ft_printf("%s", "The walls weren't rendered properly");
        return (0);
    }
    if (!render_game(&game, win))
    {
        ft_printf("%s", "The map is too small\n");
        return (0);
    }
    if (!mlx_key_hook(win, handle_keypress, &game))
        return(0);
    mlx_hook(win, 17, 0, close_window, NULL);
    mlx_loop(mlx);
    return (0);
}
