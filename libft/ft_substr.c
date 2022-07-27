/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 18:02:43 by ppajot            #+#    #+#             */
/*   Updated: 2022/05/04 12:58:03 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*res;
	size_t			size;

	i = 0;
	if (start >= ft_strlen(s))
		size = 0;
	else
	{
		if (ft_strlen(s) - start < len)
			size = ft_strlen(s) - start;
		else
			size = len;
	}
	res = (char *)malloc((size + 1) * sizeof(char));
	if (!res)
		return (0);
	while (i < size && s[start + i])
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = 0;
	return (res);
}
