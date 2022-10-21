/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre-yves <pierre-yves@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 19:45:05 by ppajot            #+#    #+#             */
/*   Updated: 2022/09/16 19:59:36 by pierre-yves      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*create_content(char *str, int a)
{
	t_token	*content;

	content = (t_token *)malloc(sizeof(t_token));
	if (!content)
		return (0);
	content->string = ft_strdup(str);
	if (!content->string)
		return (free(content), (void *)0);
	content->token_type = a;
	return (content);
}

void	init_op_tab(char tab[9][3])
{
	tab[0][0] = '<';
	tab[0][1] = 0;
	tab[1][0] = '>';
	tab[1][1] = 0;
	tab[2][0] = '<';
	tab[2][1] = '<';
	tab[2][2] = 0;
	tab[3][0] = '>';
	tab[3][1] = '>';
	tab[3][2] = 0;
	tab[4][0] = '|';
	tab[4][1] = 0;
	tab[5][0] = '(';
	tab[5][1] = 0;
	tab[6][0] = ')';
	tab[6][1] = 0;
	tab[7][0] = '&';
	tab[7][1] = '&';
	tab[7][2] = 0;
	tab[8][0] = '|';
	tab[8][1] = '|';
	tab[8][2] = 0;
}

int	tokenization(char *str, t_list **token_list)
{
	t_list	*new_elem;
	t_token	*token;
	int		i;
	char	tab[9][3];

	i = -1;
	init_op_tab(tab);
	if (!*str)
		return (0);
	while (++i < 9)
	{
		if (ft_strcmp(str, tab[i]) == 0)
		{
			token = create_content(str, i + 1);
			break ;
		}
	}
	if (i == 9)
		token = create_content(str, WORDS);
	new_elem = ft_lstnew((void *)token);
	if (!token || !new_elem)
		return (free_token(token), free(new_elem), 0);
	ft_lstadd_back(token_list, new_elem);
	return (1);
}

void	is_in_quote(char c, int *quoting, int neg)
{
	if (neg == 0)
	{
		if (c == '\'' && *quoting % '\'' == 0)
			*quoting = '\'' - *quoting;
		if (c == '\"' && *quoting % '\"' == 0)
			*quoting = '\"' - *quoting;
	}
	else
	{
		if ((c == '\'' || c == - '\'') && *quoting % '\'' == 0)
			*quoting = '\'' - *quoting;
		if ((c == '\"' || c == - '\"') && *quoting % '\"' == 0)
			*quoting = '\"' - *quoting;
	}
}

int	tokener(char *input, t_list **token_list, char *temp)
{
	int	i;
	int	quoting;

	quoting = 0;
	i = 0;
	while (*input)
	{
		if (i > 0 && is_op(temp[i - 1]) && !quoting && (*input != temp[i - 1]
				|| temp[i - 1] == '(' || temp[i - 1] == ')'))
			token_and_reset(temp, token_list, &i);
		is_in_quote(*input, &quoting, 0);
		if (!quoting && is_op(*input) && i > 0 && !is_op(temp[i - 1]))
			token_and_reset(temp, token_list, &i);
		if (!quoting && (*input == ' ' || *input == '\t'))
		{
			token_and_reset(temp, token_list, &i);
			input++;
			continue ;
		}
		temp[i] = *input;
		i++;
		input++;
	}
	return (token_and_reset(temp, token_list, &i));
}
