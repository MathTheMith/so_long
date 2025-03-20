/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:18:54 by math              #+#    #+#             */
/*   Updated: 2025/03/15 15:52:53 by mvachon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	render_static_map(t_game *game, void *win)
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
				if (!print_images(game->mlx, win, "./images/walls.xpm",
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

int	check_valid_characters(char **map, int height)
{
	int	x;
	int	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] != '0' && map[y][x] != '1' &&
				map[y][x] != 'P' && map[y][x] != 'C' &&
				map[y][x] != 'E' && map[y][x] != 'M' &&
				map[y][x] != '\n')
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

int	render_game(t_game *game, void *win)
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
				print_images(game->mlx, win, "./images/background.xpm",
					col * 98, row * 98);
			else if (game->map[row][col] == 'C')
				print_images(game->mlx, win, "./images/items.xpm",
					col * 98, row * 98);
			else if (game->map[row][col] == 'E')
				print_images(game->mlx, win, "./images/exit.xpm",
					col * 98, row * 98);
			else if (game->map[row][col] == 'M')
				print_images(game->mlx, win, "./images/monster.xpm",
					col * 98, row * 98);
			col++;
		}
		row++;
	}
	render_player(game, game->win);
	return (1);
}

void	render_steps_with_background(void *mlx, void *win, int steps)
{
	char	step_count[50];
	int		rect_width;
	int		rect_height;
	int		i;
	void	*bg_image;
	int		*data;

	rect_height = 50;
	rect_width = 150;
	bg_image = mlx_new_image(mlx, rect_width, rect_height);
	data = (int *)mlx_get_data_addr(bg_image, &(int){0},
			&(int){0}, &(int){0});
	sprintf(step_count, "Steps: %d", steps);
	i = 0;
	while (i < rect_width * rect_height)
	{
		data[i] = 0x000000;
		i++;
	}
	mlx_put_image_to_window(mlx, win, bg_image, 25, 25);
	mlx_string_put(mlx, win, 40, 40, 0xFFFFFF, step_count);
	mlx_destroy_image(mlx, bg_image);
}
