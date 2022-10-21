/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_wildcards.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:40:30 by aperis            #+#    #+#             */
/*   Updated: 2022/09/12 18:59:06 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_cmd(t_btree **cmd)
{
	(*cmd)->content.token_type = SIMPLE_COMMAND;
	(*cmd)->content.string = 0;
	(*cmd)->right = 0;
	(*cmd)->left = 0;
}

t_btree	*create_node_wildcards(t_btree **node, t_data *data)
{
	int		i;
	char	**wild_tab;
	t_btree	*tmp;

	i = 0;
	tmp = (*node)->left;
	wild_tab = wildcards((*node)->content.string, data);
	while (wild_tab && wild_tab[i])
	{
		add_node_left(node);
		(*node)->right = NULL;
		(*node)->left->content.token_type = (WORDS | (1 << 9));
		(*node)->left->content.string = wild_tab[i];
		*node = (*node)->left;
		i++;
	}
	(*node)->left = NULL;
	(*node)->right = NULL;
	(*node)->left = tmp;
	free(wild_tab);
	return (tmp);
}
