/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:56:19 by mvachon           #+#    #+#             */
/*   Updated: 2024/12/03 12:12:15 by mvachon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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
    int i;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        write(2, "Error: Unable to open file\n", 27);
        return (NULL);
    }

    map = malloc(sizeof(char *) * 1024);
    if (!map)
    {
        write(2, "Error: Memory allocation failed\n", 33);
        close(fd);
        return (NULL);
    }

    i = 0;
    while ((line = get_next_line(fd)))
    {
        map[i] = line;
        i++;
    }
    map[i] = NULL; 
    close(fd);

    return (map);
}
