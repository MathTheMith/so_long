/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 02:27:14 by marvin            #+#    #+#             */
/*   Updated: 2025/04/11 02:27:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void ft_memset(void *b, int c, size_t len)
{
    unsigned char *ptr;
    size_t i;

    ptr = (unsigned char *)b;
    i = 0;
    while (i < len)
    {
        ptr[i] = (unsigned char)c;
        i++;
    }
}

int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}