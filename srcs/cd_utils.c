/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 20:25:33 by ppajot            #+#    #+#             */
/*   Updated: 2022/09/21 15:49:53 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_symlink(char *curpath, int i)
{
	struct stat	buf;
	int			ret;

	ret = 1;
	if (i == 0)
		return (1);
	curpath[i] = 0;
	if (stat(curpath, &buf) == -1)
		ret = 0;
	curpath[i] = '/';
	return (ret);
}

void	reduce_single_points(char *curpath)
{
	char	*tmp;

	while (1)
	{
		tmp = ft_strnstr(curpath, "/./", ft_strlen(curpath));
		if (!tmp)
			break ;
		while (*(tmp + 2))
		{
			*tmp = *(tmp + 2);
			tmp++;
		}
		*tmp = 0;
	}
}

int	reduce_double_points(char *curpath)
{
	char	*tmp;
	int		i;
	int		diff;

	while (1)
	{
		tmp = ft_strnstr(curpath, "/../", ft_strlen(curpath));
		if (!tmp)
			break ;
		i = tmp - curpath;
		if (check_symlink(curpath, i) == 0)
			return (0);
		i = get_prev_slash(curpath, i);
		diff = tmp - curpath - i + 3;
		while (curpath[i + diff])
		{
			curpath[i] = (curpath[i + diff]);
			i++;
		}
		curpath[i] = 0;
	}
	return (1);
}

char	*reduce_slashes(char *curpath)
{
	int	diff;
	int	i;
	int	slashes;

	i = 0;
	diff = 0;
	while (curpath[i + diff])
	{
		slashes = 1;
		while (curpath[i + diff] == '/' && curpath[i + diff + slashes] == '/')
			slashes++;
		diff += slashes - 1;
		curpath[i] = curpath[i + diff];
		i++;
	}
	curpath[i] = 0;
	return (curpath);
}

char	*reduce_points(char *curpath)
{
	reduce_slashes(curpath);
	reduce_single_points(curpath);
	if (reduce_double_points(curpath) == 0)
		return (0);
	return (curpath);
}
