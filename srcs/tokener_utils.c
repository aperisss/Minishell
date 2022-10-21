/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre-yves <pierre-yves@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 19:46:28 by ppajot            #+#    #+#             */
/*   Updated: 2022/09/16 20:00:30 by pierre-yves      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_op(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '&' || c == '(' || c == ')')
		return (1);
	return (0);
}

int	token_and_reset(char *temp, t_list **token_list, int *i)
{
	temp[*i] = 0;
	if (*i == 0)
		return (-1);
	*i = 0;
	return (tokenization(temp, token_list));
}
