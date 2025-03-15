/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:07:00 by math              #+#    #+#             */
/*   Updated: 2025/03/15 15:21:05 by mvachon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_borders(char **map)
{
	int	row;
	int	col;
	int	len;

	row = 0;
	col = 0;
	while (map[0][col] && map[0][col] == '1')
		col++;
	if (map[0][col] != '\n')
		return (0);
	row++;
	len = col;
	while (map[row + 1])
	{
		if (map[row][0] != '1' || map[row][col - 1] != '1'
		|| map[row][col] != '\n')
			return (0);
		row++;
	}
	col = 0;
	while (map[row] && map[row][col] && map[row][col] == '1')
		col++;
	if (col != len || map[row][col] != '\0')
		return (0);
	return (1);
}

void	count_objects(char **map, t_object_count *count)
{
	int	row;
	int	col;

	row = 0;
	count->count_e = 0;
	count->count_p = 0;
	count->count_c = 0;
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			if (map[row][col] == 'E')
				count->count_e++;
			else if (map[row][col] == 'P')
				count->count_p++;
			else if (map[row][col] == 'C')
				count->count_c++;
			col++;
		}
		row++;
	}
}

int	check_objects(char **map)
{
	t_object_count	count;

	count_objects(map, &count);
	if (count.count_e != 1 || count.count_p != 1 || count.count_c < 1)
		return (0);
	return (count.count_c);
}
