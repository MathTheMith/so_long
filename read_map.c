#include "so_long.h"

void free_map(char **map)
{
	int i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

char **read_map(const char *filename)
{
	int fd;
	char *line;
	char **map;
	int i = 0;
	int map_size = 10;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("%s", "impossible d'ouvrir le fichier\n");
		return (NULL);
	}

	map = malloc(sizeof(char *) * map_size);
	if (!map)
	{
		ft_printf("%s", "L'allocation ne marche pas\n");
		close(fd);
		return (NULL);
	}

	while ((line = get_next_line(fd)))
	{
		if (i >= map_size)
		{
			map_size *= 2;
			char **new_map = malloc(sizeof(char *) * map_size);
			if (!new_map)
			{
				ft_printf("%s", "L'allocation ne marche pas\n");
				free_map(map);
				close(fd);
				return (NULL);
			}

			int j = 0;
			while (j < i)
			{
				new_map[j] = map[j];
				j++;
			}
			free(map);
			map = new_map;
		}

		map[i] = line;
		i++;
	}
	map[i] = NULL;

	close(fd);
	return (map);
}
