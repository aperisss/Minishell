/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:59:20 by ppajot            #+#    #+#             */
/*   Updated: 2022/05/04 12:57:23 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;
	int	n;

	i = 0;
	n = ft_strlen(str);
	if (!c)
		return ((char *)(str + n));
	while (i < n)
	{
		if (str[i] == (char)c)
			return ((char *)(str + i));
		i++;
	}
	return (0);
}
