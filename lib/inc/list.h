/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:46:02 by ppajot            #+#    #+#             */
/*   Updated: 2022/08/24 17:03:28 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include <stdlib.h> 

typedef struct s_list {
	struct s_list	*next;
	void			*content;
}	t_list;

void		ft_lstadd_back(t_list **lst, t_list *new);
t_list		*ft_lstnew(void *content);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int			ft_lstsize(t_list *lst);
void		ft_lstdel_first(t_list **list, void (*del)(void *));

#endif