/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 05:30:11 by marvin            #+#    #+#             */
/*   Updated: 2025/04/11 05:30:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	print_images(t_game *game, char *link_img, int x, int y)
{
	void	*img;
	int		width;
	int		height;

	width = 98;
	height = 98;
	img = mlx_xpm_file_to_image(game->mlx, link_img, &width, &height);
	if (!img)
	{
		ft_printf("Error\nImage failed to load. Path: %s\n", link_img);
		cleanup(game);
		exit(1);
	}
	mlx_put_image_to_window(game->mlx, game->win, img, x, y);
	mlx_destroy_image(game->mlx, img);
	return (1);
}

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}
