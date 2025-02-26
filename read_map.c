#include "so_long.h"

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

int handle_file_error(int fd, char **map)
{
	if (fd < 0)
	{
		ft_printf("%s", "impossible d'ouvrir le fichier\n");
		return (1);
	}
	if (!map)
	{
		ft_printf("%s", "L'allocation ne marche pas\n");
		close(fd);
		return (1);
	}
	return (0);
}

char **expand_map(char **map, int i, int *map_size, int fd)
{
	char **new_map;
	int j = 0;
	
	*map_size *= 2;
	new_map = malloc(sizeof(char *) * *map_size);
	if (!new_map)
	{
		ft_printf("%s", "L'allocation ne marche pas\n");
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

char **read_map(const char *filename)
{
	int fd = open(filename, O_RDONLY);
	char *line;
	char **map = malloc(sizeof(char *) * 10);
	int i = 0, map_size = 10;
	
	if (handle_file_error(fd, map))
		return (NULL);
	while ((line = get_next_line(fd)))
	{
		if (i >= map_size)
			if (!(map = expand_map(map, i, &map_size, fd)))
				return (NULL);
		map[i++] = line;
	}
	map[i] = NULL;
	close(fd);
	return (map);
}