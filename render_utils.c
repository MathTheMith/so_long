/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:55:02 by math              #+#    #+#             */
/*   Updated: 2024/12/12 22:55:02 by math             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	print_images(void *mlx, void *win, char *link_img, int x, int y)
{
	void	*img;
	int		width;
	int		height;

	width = 98;
	height = 98;
	img = mlx_xpm_file_to_image(mlx, link_img, &width, &height);
	if (!img)
	{
		printf("Error\nImage failed to load. Path: %s\n", link_img);
		return (0);
	}
	mlx_put_image_to_window(mlx, win, img, x, y);
	mlx_destroy_image(mlx, img);
	return (1);
}

void render_jump_animation(t_game *game, void *jump_sprite)
{
    int i;

    i = 0;
    while (i < 10)
    {
        mlx_put_image_to_window(game->mlx, game->win, jump_sprite, 
            game->player_x * 98, game->player_y * 98);
        mlx_do_sync(game->mlx);
        usleep(7000);
        i++;
    }
}

void render_jump(t_game *game, int left_right)
{
    void    *jump_sprite;
    int     width;
    int     height;

    width = 64;
    height = 64;
    jump_sprite = NULL;
    if (left_right == 1)
        jump_sprite = mlx_xpm_file_to_image(game->mlx, 
            "./images/player_jump_left.xpm", &width, &height);
    else
        jump_sprite = mlx_xpm_file_to_image(game->mlx, 
            "./images/player_jump.xpm", &width, &height);

    if (!jump_sprite)
    {
        printf("Error\nFailed to load jump sprite\n");
        return;
    }

    render_jump_animation(game, jump_sprite);
    mlx_destroy_image(game->mlx, jump_sprite);
}

void handle_jump_animation(t_game *game, int keycode)
{
    if (keycode == KEY_A)
    {
        render_jump(game, 1);
    }
    else if (keycode == KEY_W || keycode == KEY_S)
    {
        if (game->last_direction == -1)
            render_jump(game, 1);
        else
            render_jump(game, 0);
    }
    else if (keycode == KEY_D)
    {
        render_jump(game, 0);
    }
}