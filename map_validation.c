/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:55:02 by math              #+#    #+#             */
/*   Updated: 2024/12/12 22:55:02 by math             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void flood_fill(char **map, int x, int y, int *collectibles, int *exit_found)
{
	if (map[y][x] == '1' || map[y][x] == 'F' || map[y][x] == 'M')
		return;
	if (map[y][x] == 'C')
		(*collectibles)--;  
    if (map[y][x] == 'E')
		*exit_found = 1;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y, collectibles, exit_found);
	flood_fill(map, x - 1, y, collectibles, exit_found);
	flood_fill(map, x, y + 1, collectibles, exit_found);
	flood_fill(map, x, y - 1, collectibles, exit_found);
}

int count_collectibles(char **map, int width, int height)
{
	int x;
	int y;
	int collectibles;

	collectibles = 0;
	y = 0;
	while (y < height)
	{
	    x = 0;
	    while (x < width)
	    {
	        if (map[y][x] == 'C')
	            collectibles++;
	        x++;
	    }
	    y++;
	}
	return (collectibles);
}

void find_player_position(char **map, int width, int height, int *player_x, int *player_y)
{
    int x;
    int y;

    y = 0;
    while (y < height)
    {
        x = 0;
        while (x < width)
        {
            if (map[y][x] == 'P')
            {
                *player_x = x;
                *player_y = y;
                return;
            }
            x++;
        }
        y++;
    }
}
void replace_exit_with_wall(char **map, int height)
{
    int x;
    int y;
    
    y = 0;
    while (y < height)
    {
        x = 0;
        while (map[y][x] != '\0')
        {
            if (map[y][x] == 'E')
                map[y][x] = '1';
            x++;
        }
        y++;
    }
}

int check_collectibles_without_exit(char **map, int width, int height)
{
    int collectibles;
    int dummy_exit_found = 0;
    int player_x, player_y;
    char **map_copy;
    
    map_copy = duplicate_map(map, height);
    if (!map_copy)
        return (0);
    replace_exit_with_wall(map_copy, height);
    collectibles = count_collectibles(map, width, height);
    find_player_position(map, width, height, &player_x, &player_y);
    flood_fill(map_copy, player_x, player_y, &collectibles, &dummy_exit_found);
    free_map(map_copy);
    return (collectibles == 0);
}


int validate_path(char **map, int width, int height)
{
    int collectibles;
    int exit_found;
    int player_x, player_y;
    char **map_copy;
    
    if (!check_collectibles_without_exit(map, width, height))
        return (0);
    collectibles = count_collectibles(map, width, height);
    exit_found = 0;
    map_copy = duplicate_map(map, height);
    if (!map_copy)
        return (0);
    
    find_player_position(map, width, height, &player_x, &player_y);
    flood_fill(map_copy, player_x, player_y, &collectibles, &exit_found);
    
    free_map(map_copy);
    return (collectibles == 0 && exit_found);
}

char **duplicate_map(char **map, int height)
{
    int     i;
    char    **copy;

    copy = malloc(sizeof(char *) * (height + 1));
    if (!copy)
        return (NULL);
    i = 0;
    while (i < height)
    {
        copy[i] = strdup(map[i]);
        if (!copy[i])
        {
            while (--i >= 0)
                free(copy[i]);
            free(copy);
            return (NULL);
        }
        i++;
    }
    copy[height] = NULL;
    return (copy);
}