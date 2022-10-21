/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis <aperis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 19:07:41 by ppajot            #+#    #+#             */
/*   Updated: 2022/09/21 16:00:45 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_entry(char *name, t_list **envp)
{
	t_dict	*entry;

	if (*envp == 0)
		return ;
	entry = (t_dict *)((*envp)->content);
	if (ft_strcmp(name, entry->name) == 0)
		ft_lstdel_first(envp, &free_entry);
	else
		remove_entry(name, &(*envp)->next);
}

void	create_entry(char *str, t_data *data)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	str[i] = 0;
	put_env(str, str + i + 1, 1, data);
	str[i] = '=';
}

int	env_var_exists(char *name, t_data *data)
{
	t_dict	*entry;
	t_list	*tmp;

	tmp = data->envp;
	while (tmp)
	{
		entry = tmp->content;
		if (ft_strcmp(name, entry->name) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
