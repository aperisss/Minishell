/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:00:47 by ppajot            #+#    #+#             */
/*   Updated: 2022/05/24 15:17:21 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	putchar_flags(va_list arg, t_flags flags, int *count)
{
	int	c;

	c = va_arg(arg, int);
	if (!flags.rightfill && flags.minsize > 1)
		ft_fill(' ', flags.minsize - 1, count);
	ft_putchar_fd(c, 1);
	if (flags.rightfill && flags.minsize > 1)
		ft_fill(' ', flags.minsize - 1, count);
	(*count)++;
}

void	putstring_flags(va_list arg, t_flags flags, int *count)
{
	char	*str;
	int		n;

	str = va_arg(arg, char *);
	if (str)
		n = ft_strlen(str);
	else
		n = 6;
	if (flags.precision >= 0 && flags.precision < n)
		n = flags.precision;
	if (!flags.rightfill && flags.minsize > n)
		ft_fill(' ', flags.minsize - n, count);
	if (str)
	{
		write(1, str, n);
		*count += n;
	}
	else if (n >= 6)
	{
		write(1, "(null)", 6);
		*count += 6;
	}
	if (flags.rightfill && flags.minsize > n)
		ft_fill(' ', flags.minsize - n, count);
}

void	ft_putnbr_long(unsigned long nbr, char *base, int *count)
{
	unsigned long	n;

	n = ft_strlen(base);
	if (nbr < n)
	{
		write(1, base + nbr, 1);
		(*count)++;
	}
	else
	{
		ft_putnbr_long(nbr / n, base, count);
		write(1, base + nbr % n, 1);
		(*count)++;
	}
}

void	putnbrleftzero(long i, t_flags flags, int *count, char convert)
{
	int	minsize;

	minsize = getsize_base(i, flags, convert);
	minsize += hassign(i, flags, convert);
	putsign(&i, flags, count, convert);
	if (flags.minsize > minsize)
		ft_fill('0', flags.minsize - minsize, count);
	ft_putnbr(i, convert, count);
}
