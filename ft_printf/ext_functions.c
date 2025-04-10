/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ext_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:37:10 by math              #+#    #+#             */
/*   Updated: 2025/04/10 07:10:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *s)
{
	int	len;

	len = 0;
	if (!s)
		return (write(1, "(null)", 6));
	while (s[len])
		len++;
	write(1, s, len);
	return (len);
}

int	ft_putnbr(int nb)
{
	int	len;

	len = 0;
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (nb < 0)
	{
		len += ft_putchar('-');
		nb = -nb;
	}
	if (nb >= 10)
	{
		len += ft_putnbr(nb / 10);
		len += ft_putchar(nb % 10 + '0');
	}
	else
	{
		len += ft_putchar(nb + '0');
	}
	return (len);
}

int	ft_putnbr_base(unsigned int nbr, char *base, int base_len)
{
	int	len;

	len = 0;
	if ((int)nbr >= base_len)
	{
		len += ft_putnbr_base(nbr / base_len, base, base_len);
		len += ft_putnbr_base(nbr % base_len, base, base_len);
	}
	else
	{
		ft_putchar(base[nbr]);
		len++;
	}
	return (len);
}

int	ft_ptoe(void *ptr)
{
	int	len;

	len = 0;
	if (!ptr)
		return (ft_putstr("(nil)"));
	len += ft_putstr("0x");
	len += ft_putnbr_base((uintptr_t)ptr, "0123456789abcdef", 16);
	return (len);
}
