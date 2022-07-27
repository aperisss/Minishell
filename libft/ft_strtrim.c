/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 18:18:45 by ppajot            #+#    #+#             */
/*   Updated: 2022/05/03 20:18:41 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isinset(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	long	i;
	long	begin;
	long	end;
	char	*res;

	i = 0;
	begin = 0;
	while (s1[begin] && isinset(s1[begin], set))
		begin++;
	end = ft_strlen(s1) - 1;
	while (end > 0 && isinset(s1[end], set))
		end--;
	if (end < begin)
		end = begin - 1;
	res = (char *)malloc(end - begin + 2);
	if (!res)
		return (0);
	while (begin + i <= end)
	{
		res[i] = s1[begin + i];
		i++;
	}
	res[i] = 0;
	return (res);
}
