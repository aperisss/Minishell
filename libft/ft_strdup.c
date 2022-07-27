/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:52:37 by ppajot            #+#    #+#             */
/*   Updated: 2022/05/03 19:18:17 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*res;

	i = 0;
	while (s[i])
		i++;
	res = (char *)malloc(i + 1);
	if (!res)
		return (0);
	res[i] = 0;
	i = 0;
	while (*(s + i))
	{
		*(res + i) = *(s + i);
		i++;
	}
	return (res);
}
