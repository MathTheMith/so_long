/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:29:46 by mvachon           #+#    #+#             */
/*   Updated: 2025/04/12 19:41:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	handle_file_error(int fd, char **map)
{
	if (fd < 0)
	{
		ft_printf("%s", "Error\n Impossible to open the file\n");
		return (1);
	}
	if (!map)
	{
		ft_printf("%s", "Error\nThere is no map\n");
		close(fd);
		return (1);
	}
	return (0);
}

char	**expand_map(char **map, int i, int *map_size, int fd)
{
	char	**new_map;
	int		j;

	j = 0;
	*map_size *= 2;
	new_map = malloc(sizeof(char *) * (*map_size + 1));
	if (!new_map)
	{
		ft_printf("%s", "Error\nAllocation didn't work\n");
		free_map(map);
		close(fd);
		return (NULL);
	}
	while (j < i)
	{
		new_map[j] = map[j];
		j++;
	}
	free(map);
	return (new_map);
}

int	open_map_file(const char *filename, int *fd, char ***map, int *map_size)
{
	*fd = open(filename, O_RDWR);
	if (*fd < 0)
	{
		ft_printf("Error\nAcces denied\n");
		return (0);
	}
	*map_size = 10;
	*map = malloc(sizeof(char *) * (*map_size + 1));
	if (!*map)
		return (0);
	return (1);
}

int	read_first_line(int fd, char **map, int *i)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
	{
		free(map);
		close(fd);
		return (0);
	}
	map[*i] = line;
	(*i)++;
	return (1);
}

char	**read_map(const char *filename)
{
	int		fd;
	char	*line;
	char	**map;
	int		i;
	int		map_size;

	i = 0;
	if (!open_map_file(filename, &fd, &map, &map_size)
		|| !read_first_line(fd, map, &i))
		return (NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (i >= map_size)
		{
			map = expand_map(map, i, &map_size, fd);
			if (!map)
				return (NULL);
		}
		map[i++] = line;
	}
	map[i] = NULL;
	return (close(fd), map);
}
