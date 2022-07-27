/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:25:09 by ppajot            #+#    #+#             */
/*   Updated: 2022/05/03 20:34:09 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	len(int n)
{
	size_t	size;

	size = 0;
	if (n <= 0)
		size++;
	while (n)
	{
		size++;
		n /= 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*res;
	long	ln;
	size_t	size;

	ln = (long)n;
	size = len(n);
	res = (char *)malloc(size + 1);
	res[size] = 0;
	if (ln < 0)
	{
		ln *= -1;
		res[0] = '-';
	}
	if (!ln)
		res[0] = '0';
	while (ln)
	{
		res[size - 1] = ln % 10 + 48;
		ln /= 10;
		size--;
	}
	return (res);
}
