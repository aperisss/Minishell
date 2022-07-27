/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:51:52 by ppajot            #+#    #+#             */
/*   Updated: 2022/05/03 17:37:03 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	sizedest;
	size_t	sizesrc;
	size_t	i;

	i = 0;
	sizedest = ft_strlen(dest);
	sizesrc = ft_strlen(src);
	if (sizedest >= size || size == 0)
		return (size + sizesrc);
	while (i < size - 1 - sizedest && src [i] != '\0')
	{
		dest[sizedest + i] = src[i];
		i++;
	}
	dest[i + sizedest] = '\0';
	return (sizedest + sizesrc);
}
