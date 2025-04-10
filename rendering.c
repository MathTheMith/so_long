/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:18:54 by math              #+#    #+#             */
/*   Updated: 2025/04/10 06:19:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	render_static_map(t_game *game)
{
	int	row;
	int	col;

	row = 0;
	while (game->map[row])
	{
		col = 0;
		while (game->map[row][col])
		{
			if (game->map[row][col] == '1')
			{
				if (!print_images(game, "./images/walls.xpm",
						col * 98, row * 98))
				{
					printf("Error\nFailed to render wall at row %d,col %d\n",
						row, col);
					return (0);
				}
			}
			col++;
		}
		row++;
	}
	return (1);
}

int	check_valid_characters(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (game->map[y][x] != '\0')
		{
			if (game->map[y][x] != '0' && game->map[y][x] != '1' &&
				game->map[y][x] != 'P' && game->map[y][x] != 'C' &&
				game->map[y][x] != 'E' && game->map[y][x] != '\n')
			{
				printf("Error\nInvalid character found\n");
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	render_game(t_game *game)
{
	int	row;
	int	col;

	row = 0;
	while (game->map[row])
	{
		col = 0;
		while (game->map[row][col])
		{
			if (game->map[row][col] == '0')
				print_images(game, "./images/background.xpm",
					col * 98, row * 98);
			else if (game->map[row][col] == 'C')
				print_images(game, "./images/items.xpm",
					col * 98, row * 98);
			else if (game->map[row][col] == 'E')
				print_images(game, "./images/exit.xpm",
					col * 98, row * 98);
			col++;
		}
		row++;
	}
	render_player(game);
	return (1);
}

void	render_steps_with_background(void *mlx, void *win, int steps)
{
	t_render	render;
	char		step_count[50];
	int			i;

	render.rect_width = 150;
	render.rect_height = 50;
	render.bg_image = mlx_new_image(mlx, render.rect_width, render.rect_height);
	render.data = (int *)mlx_get_data_addr(render.bg_image, &(int){0},
			&(int){0}, &(int){0});
	sprintf(step_count, "Steps: %d", steps);
	i = 0;
	while (i < render.rect_width * render.rect_height)
	{
		render.data[i] = 0x000000;
		i++;
	}
	mlx_put_image_to_window(mlx, win, render.bg_image, 25, 25);
	mlx_string_put(mlx, win, 40, 40, 0xFFFFFF, step_count);
	mlx_destroy_image(mlx, render.bg_image);
}
