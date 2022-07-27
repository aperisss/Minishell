#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	if (s1)
	{
		while (*s1 == *s2 && *s1 && *s2)
		{
			s1++;
			s2++;
		}
		return (*s1 - *s2);
	}
	return (0);
}

void print_token_list(t_list *prev)
{
	while (prev)
	{
		printf("token_list = %d\n", prev->content.token_type);
		prev = prev->next;
	}
}