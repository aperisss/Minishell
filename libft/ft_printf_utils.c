/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:56:41 by ppajot            #+#    #+#             */
/*   Updated: 2022/05/24 15:17:25 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_convert(long l, char convert)
{
	if (convert == 'i' || convert == 'd')
		return ((int)l);
	else if (convert == 'u' || convert == 'x' || convert == 'X')
		return ((unsigned int)l);
	else
		return ((unsigned long)l);
}

void	setflags(t_flags *flags)
{
	flags->hexprefix = 0;
	flags->leftzero = 0;
	flags->minsize = 0;
	flags->precision = -1;
	flags->rightfill = 0;
	flags->spacesign = 0;
}

int	atoi_move(char **str)
{
	int	res;

	res = 0;
	while (**str >= '0' && **str <= '9')
	{
		res = res * 10 + **str - 48;
		(*str)++;
	}
	return (res);
}

int	ft_max(int i, int j)
{
	if (i >= j)
		return (i);
	else
		return (j);
}

int	isflags(char c)
{
	if (c == '#' || c == ' ' || c == '+' || c == '0' || c == '-')
		return (1);
	return (0);
}
