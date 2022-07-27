/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:59:03 by ppajot            #+#    #+#             */
/*   Updated: 2022/05/24 15:17:23 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_fill(char c, int len, int *count)
{
	int	i;

	i = 0;
	while (i < len)
	{
		write(1, &c, 1);
		(*count)++;
		i++;
	}
	return (i);
}

int	hassign(long i, t_flags flags, char convert)
{
	if (convert == 'x' || convert == 'X' || convert == 'p')
	{
		if (i && flags.hexprefix)
			return (2);
		else
			return (0);
	}
	if (i < 0)
		return (1);
	else if (flags.spacesign == 2)
		return (1);
	else if (flags.spacesign == 1)
		return (1);
	return (0);
}

void	putsign(long *i, t_flags flags, int *count, char convert)
{
	if (!hassign(*i, flags, convert))
		return ;
	if (convert == 'x' || convert == 'X' || convert == 'p')
	{
		if (i && flags.hexprefix)
		{
			if (convert == 'X')
				ft_putstr_fd("0X", 1);
			else
				ft_putstr_fd("0x", 1);
			*count += 2;
		}
		return ;
	}
	if (*i < 0)
	{
		ft_putchar_fd('-', 1);
		*i *= -1;
	}
	else if (flags.spacesign == 2)
		ft_putchar_fd('+', 1);
	else if (flags.spacesign == 1)
		ft_putchar_fd(' ', 1);
	(*count)++;
}

int	getsize_base(long l, t_flags flags, char convert)
{
	int				result;
	unsigned long	ul;

	result = 0;
	if (!l && flags.precision)
		return (1);
	if (convert == 'p')
	{
		ul = (unsigned long)l;
		while (ul)
		{
			result++;
			ul /= 16;
		}
		return (result);
	}
	while (l)
	{
		result++;
		if (convert == 'u' || convert == 'i' || convert == 'd')
			l /= 10;
		else
			l /= 16;
	}
	return (result);
}
