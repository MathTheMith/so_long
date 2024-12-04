/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:02:39 by math              #+#    #+#             */
/*   Updated: 2024/11/19 16:02:19 by math             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

int ft_putchar(char c);
int ft_putstr(char *s);
int	ft_putnbr(int nb);
int	ft_putnbr_base(unsigned int nbr, char *base, int len);
int ft_ptoe(void *ptr);
int ft_specify(const char *conv, size_t i, va_list args);
int ft_printf(const char *conv, ...);


#endif