/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 22:23:24 by ppajot            #+#    #+#             */
/*   Updated: 2022/07/24 23:34:31 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	create_content(int type, char *str)
{
	t_token	token;
	
	token.string = ft_strdup(str);
	token.token_type = type;
	return (token);
}

void    tokenization(char *str, t_list **token_list)
{
	t_token newcontent;
	
	if (ft_strcmp(str, "|") == 0)
		newcontent = create_content(PIPE, str);	
	else if (ft_strcmp(str, ">") == 0)
		newcontent = create_content(ONE_REDIR_RIGHT, str);
	else if (ft_strcmp(str, "<") == 0)
		newcontent = create_content(ONE_REDIR_LEFT, str);
	else if (ft_strcmp(str, ">>") == 0)
		newcontent = create_content(DOUBLE_REDIR_RIGHT, str);
	else if (ft_strcmp(str, "<<") == 0)
		newcontent = create_content(DOUBLE_REDIR_LEFT, str);
	else if (ft_strcmp(str, "(") == 0)
		newcontent = create_content(OPEN_PAR, str);
	else if (ft_strcmp(str, ")") == 0)
		newcontent = create_content(CLOSE_PAR, str);
	else if (ft_strcmp(str, "&&") == 0)
		newcontent = create_content(AND, str);
	else if (ft_strcmp(str, "||") == 0)
		newcontent = create_content(OR, str);
	else
		newcontent = create_content(WORDS, str);
	ft_lstadd_back(token_list, ft_lstnew(newcontent));
}

int	is_op(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '&' || c == '(' || c == ')')
		return (1);
	return (0);
}

void	tokener(char *input, t_list **token_list)
{
	char *temp;
	int	i;
	int	quoting;

	quoting = 0;
	i = 0;
	temp = ft_calloc(ft_strlen(input) + 1, sizeof(char));
	while (*input)
	{
		if (i > 0 && is_op(temp[i - 1]) && !quoting)
		{
			if (*input != temp[i - 1] || temp[i - 1] == '(' || temp[i - 1] == ')')
			{
				temp[i] = 0;
				tokenization(temp, token_list);
				i = 0;
			}
		}
		else if (*input == '\'' || *input == '\"')
		{
			if (!quoting)
				quoting = *input;
			else if (quoting == *input)
				quoting = 0;
		}
		else if (!quoting && is_op(*input) && i > 0 && !is_op(temp[i - 1]))
		{
			temp[i] = 0;
			tokenization(temp, token_list);
			i = 0;
		}
		if (!quoting && *input == ' ')
		{
			temp[i] = 0;
			tokenization(temp, token_list);
			i = 0;
			input++;
			continue;
		}
		temp[i] = *input;
		i++;
		input++;
	}
	temp[i] = 0;
	tokenization(temp, token_list);
	free(temp);
}

void	expand_env(t_list *token_list)
{
	int		quoting;
	int		i;
	char	*name;
	char	*var;
	
	name = (char *)malloc(sizeof(char) * (size + 1));
	quoting = 0;
	while (*token_list->content.string)
	{
		if (!quoting && *token_list->content.string == '\'')
			quoting = 1;
		if (quoting && *token_list->content.string == '\'')	
			quoting = 0;
		if (!quoting && *token_list->content.string == '$')
		{
			i = 1;
			while (ft_isalnum(token_list->content.string[i]))
				i++;
			ft_strlcpy(name, token_list->content.string + 1, i);
			var = ft_getenv(name);
		
		}
		else
			new_str[i] = ;
	}
}

int	check_token(t_list **token_list)
{
	t_list	*current;

	current = *token_list;
	while (current)
	{
		if (is_op(current->content.string[0]) && ft_strlen(current->content.string) > 2)
			return (0);
		current = current->next;
	}
	return (1);
}

int	check_syntax(t_list **token_list)
{
	t_list	*current;
	int	i;
	int	prev_token;

	i = 0;
	prev_token = -1;
	current = *token_list;
	while (current)
	{
		if (current->content.token_type > 0 && current->content.token_type < 5)
			if (!current->next || current->next->content.token_type != WORDS)
				return (0);
		if (current->content.token_type == OPEN_PAR)
			if ((i != 0 && prev_token != AND && prev_token != OR) || current->next->content.token_type == PIPE)
				return (0);
		if (current->content.token_type == CLOSE_PAR)
			if ((current->next && (current->next->content.token_type != AND && current->next->content.token_type != OR)) || prev_token == PIPE)
				return (0);
		i++;
		prev_token = current->content.token_type;
		current = current->next;
	}
	return (0);
}

t_list *lexer(char *input)
{
    int i;
    t_list *token_list;

    token_list = NULL;
    tokener(input, &token_list);
	check_token(token_list);
	check_syntax(token_list);
	expand_env(token_list);
	reduce_quote(token_list);
    return (token_list);
}