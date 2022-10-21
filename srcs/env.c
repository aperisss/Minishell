/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:03:08 by ppajot            #+#    #+#             */
/*   Updated: 2022/09/20 21:35:23 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*tab_to_list(char **env, t_data *data)
{
	int		i;

	i = -1;
	if (!env)
		return (0);
	while (env[++i])
		create_entry(env[i], data);
	return (data->envp);
}

char	**list_to_tab(t_list *env_list)
{
	char	**tab;
	int		i;
	t_dict	*entry;

	tab = (char **)ft_calloc(ft_lstsize(env_list) + 1, sizeof(char *));
	if (!tab)
		return (0);
	i = -1;
	while (env_list)
	{
		entry = (t_dict *)env_list->content;
		if (entry->print == 1)
			tab[++i] = ft_strjoin(entry->name, entry->value, "=");
		env_list = env_list->next;
	}
	if (check_free((void **)tab, i))
		return (0);
	return (tab);
}

char	*ft_getenv(char *name, t_list *env_list)
{
	t_dict	*entry;

	if (ft_strcmp(name, "?") == 0)
		return (ft_itoa(g_exit_status));
	while (env_list)
	{
		entry = (t_dict *)env_list->content;
		if (!ft_strcmp(name, entry->name))
			return (entry->value);
		env_list = env_list->next;
	}
	return ("");
}

t_dict	*new_entry(char *name, char *value, int print)
{
	t_dict	*entry;

	entry = (t_dict *)malloc(sizeof(t_dict));
	if (!entry)
		return (0);
	entry->name = ft_strdup(name);
	entry->value = ft_strdup(value);
	entry->print = print;
	if (!entry->name || !entry->value)
		return (free_entry(entry), (void *)0);
	return (entry);
}

void	put_env(char *name, char *value, int print, t_data *data)
{
	t_dict	*entry;
	t_list	*new_elem;
	t_list	*tmp;

	tmp = data->envp;
	while (tmp)
	{
		entry = (t_dict *)tmp->content;
		if (!ft_strcmp(entry->name, name))
		{
			free(entry->value);
			entry->value = ft_strdup(value);
			if (!entry->value)
				exit_error(0, data, -1, 0);
			entry->print = print;
			tmp->content = (void *)entry;
			return ;
		}
		tmp = tmp->next;
	}
	entry = new_entry(name, value, print);
	if (!entry)
		exit_error(0, data, -1, 0);
	new_elem = ft_lstnew((void *)entry);
	ft_lstadd_back(&data->envp, new_elem);
}
