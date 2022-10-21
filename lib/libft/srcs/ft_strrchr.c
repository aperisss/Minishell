/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:04:14 by ppajot            #+#    #+#             */
/*   Updated: 2022/05/04 12:27:18 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *str, int c)
{
	const char	*start;

	start = str;
	while (*str)
		str++;
	if (c == 0)
		return ((char *)str);
	str--;
	while (str >= start)
	{
		if (*str == (char)c)
			return ((char *)str);
		str--;
	}
	return (0);
}
