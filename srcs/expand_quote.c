/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis <aperis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 19:21:43 by ppajot            #+#    #+#             */
/*   Updated: 2022/09/20 20:25:27 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*reduce_quote(char *str)
{
	int		quote;
	int		diff;
	char	*begin;

	begin = str;
	quote = 0;
	diff = 0;
	while (*(str + diff))
	{
		if ((*(str + diff) == '\'' && quote != '\"')
			|| (*(str + diff) == '\"' && quote != '\''))
		{
			is_in_quote(*(str + diff), &quote, 0);
			diff++;
			if (*(str + diff))
				continue ;
			else
				break ;
		}
		*str = *(str + diff);
		str++;
	}
	*str = 0;
	return (begin);
}

void	retoken_space(t_btree *root)
{
	int		quote;
	t_btree	*tmp;
	int		i;

	i = -1;
	quote = 0;
	tmp = root->left;
	while (root->content.string[++i])
	{
		is_in_quote(root->content.string[i], &quote, -1);
		if (!quote && (root->content.string[i] == ' '
				|| root->content.string[i] == '\t'))
		{
			root->content.string[i] = 0;
			while (root->content.string[i + 1] == ' '
				|| root->content.string[i + 1] == '\t')
				i++;
			add_node_left(&root);
			root->left->content.token_type = WORDS;
			root->left->content.string
				= ft_strdup(root->content.string + i + 1);
			reinit_root(&root, &i);
		}
	}
	root->left = tmp;
}

t_btree	*link_prev(t_btree *root, t_btree *prev)
{
	t_btree	*tmp;

	tmp = root->left;
	if (prev->left == root)
		prev->left = tmp;
	else
		prev->right = tmp;
	free(root->content.string);
	free(root);
	return (tmp);
}

t_btree	*retoken_wc(t_btree *root, t_data *data, t_btree *prev)
{
	int		i;
	t_btree	*tmp;

	i = -1;
	tmp = root;
	while (root->content.string[++i])
	{
		if (wc_is_unquote(root->content.string, i))
		{
			create_node_wildcards(&root, data);
			if (tmp != root)
			{
				link_prev(tmp, prev);
				return (prev->left);
			}
			else
				return (root);
		}
	}
	return (root);
}

void	expand_quote(t_btree *root, t_data *data, t_btree *prev)
{
	if (root == 0 || (root->content.token_type & 0xff) == DLESS)
		return ;
	if ((root->content.token_type & 0xff) == WORDS
		&& root->content.string != 0)
	{
		root->content.string = expand_env(root->content.string, data);
		if (!(root->content.token_type >> 8))
			retoken_space(root);
		while (root && ft_strcmp(root->content.string, "") == 0)
			root = link_prev(root, prev);
		if (root == 0)
			return ;
		if (!(root->content.token_type >> 9))
			root = retoken_wc(root, data, prev);
		if (root == 0)
			return ;
		reduce_quote(root->content.string);
		neg_quote_dollar(root->content.string, -1);
	}
	root->content.token_type &= 0xff;
	expand_quote(root->left, data, root);
	expand_quote(root->right, data, root);
}
