/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:33:05 by ppajot            #+#    #+#             */
/*   Updated: 2022/09/20 19:52:34 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_token_list(t_list *list)
{
	t_token	*token;

	while (list)
	{
		token = list->content;
		printf("string = %s\ntype = %i\n", token->string, token->token_type);
		list = list->next;
	}
}

void	free_and_next(t_list **list)
{
	t_list	*tmp;
	t_token	*token;

	if (*list == 0)
		return ;
	token = (*list)->content;
	if ((*list)->next)
	{
		tmp = *list;
		*list = (*list)->next;
		if (token->token_type == OPEN_PAR || token->token_type == CLOSE_PAR)
			free(token->string);
		free(token);
		free(tmp);
	}
	else
	{
		if (token->token_type == OPEN_PAR || token->token_type == CLOSE_PAR)
			free(token->string);
		free(token);
		free(*list);
		*list = 0;
	}
}

void	free_list(t_list *list)
{
	t_list	*tmp;
	t_token	*token;

	while (list && list->next)
	{
		token = list->content;
		tmp = list;
		list = list->next;
		free(token);
		free(tmp);
	}
	token = list->content;
	free(token);
	free(list);
}

void	free_hd_pfd(t_data *data, int mode)
{
	int	i;

	i = -1;
	while (++i < data->hd_nbr)
	{
		close(data->hd_pfd[i][0]);
		close(data->hd_pfd[i][1]);
		if (mode)
			free(data->hd_pfd[i]);
	}
	if (mode)
		free(data->hd_pfd);
}

void	free_data(t_data *data)
{
	free_tree(data->ast);
	free(data->cwd);
	free_builtin(data);
	free_hd_pfd(data, 1);
	ft_lstclear(&data->envp, free_entry);
	rl_clear_history();
}
