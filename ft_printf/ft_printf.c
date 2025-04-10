/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:58:58 by mvachon           #+#    #+#             */
/*   Updated: 2025/04/10 07:13:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_specify(const char *conv, size_t i, va_list args)
{
	if (conv[i] == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (conv[i] == 'c')
		return (ft_putchar((char)va_arg(args, int)));
	if (conv[i] == '%')
		return (ft_putchar('%'));
	if (conv[i] == 'd' || conv[i] == 'i')
		return (ft_putnbr(va_arg(args, int)));
	if (conv[i] == 'p')
		return (ft_ptoe(va_arg(args, void *)));
	if (conv[i] == 'u')
		return (ft_putnbr_base(va_arg(args, unsigned int), "0123456789", 10));
	if (conv[i] == 'x')
		return (ft_putnbr_base(va_arg(args, unsigned int),
				"0123456789abcdef", 16));
	if (conv[i] == 'X')
		return (ft_putnbr_base(va_arg(args, unsigned int),
				"0123456789ABCDEF", 16));
	return (0);
}

int	ft_printf(const char *conv, ...)
{
	va_list	args;
	size_t	i;
	int		len;

	i = 0;
	len = 0;
	va_start(args, conv);
	if (!conv)
		return (-1);
	while (conv[i])
	{
		if (conv[i] == '%' && conv[i + 1])
		{
			i++;
			len += ft_specify(conv, i, args);
		}
		else
		{
			len += ft_putchar(conv[i]);
		}
		i++;
	}
	va_end(args);
	return (len);
}
