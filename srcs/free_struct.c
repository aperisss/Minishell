/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis <aperis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 19:37:04 by ppajot            #+#    #+#             */
/*   Updated: 2022/09/20 20:13:41 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tree(t_btree *root)
{
	if (root == 0)
		return ;
	free_tree(root->left);
	free_tree(root->right);
	free(root->content.string);
	free(root);
}

void	free_entry(void *content)
{
	t_dict	*entry;

	entry = (t_dict *)content;
	free(entry->name);
	free(entry->value);
	free(entry);
}

void	free_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	free(token->string);
	free(token);
}

void	free_builtin(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 7)
		free(data->builtin_tab[i].name);
}

void	last_free(t_data *data)
{
	free(data->cwd);
	free_builtin(data);
	ft_lstclear(&data->envp, free_entry);
}
