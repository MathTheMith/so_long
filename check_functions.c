/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:07:00 by math              #+#    #+#             */
/*   Updated: 2024/12/04 00:24:26 by math             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int check_borders(char **map)
{
    int row = 0;
    int col;
    int len;

    col = 0;
    while (map[0][col] && map[0][col] == '1')
        col++;
    if (map[0][col] != '\n')
        return 0; 
    row++;
    len = col;
    while (map[row + 1])
    {
        if (map[row][0] != '1' || map[row][col - 1] != '1' || map[row][col] != '\n')
            return (0);
        row++;
    }

    col = 0;
    while (map[row][col] && map[row][col] == '1')
        col++;
    if (col != len)
        return (0);
    if (map[row][col] != '\0')
        return 0;
    return (1);
}
int check_objects(char **map)
{
    int row = 0;
    int col;
    int count_e = 0;
    int count_p = 0;
    int count_c = 0;

    while (map[row])
    {
        col = 0;
        while (map[row][col])
        {
            if (map[row][col] == 'E')
                count_e++;
            else if (map[row][col] == 'P')
                count_p++;
            else if (map[row][col] == 'C')
                count_c++;
            col++;
        }
        row++;
    }
    
    if (count_e != 1 || count_p != 1 || count_c < 1)
        return (0);
    return (count_c);
}