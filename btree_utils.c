#include "minishell.h"

void *add_node_right(t_btree **cmd)
{
	t_btree *node_right;
	node_right = malloc(sizeof(t_btree));
	(*cmd)->right = node_right;
}

void *add_node_left(t_btree **cmd)
{
	t_btree *node;
	node = malloc(sizeof(t_btree));
	(*cmd)->left = node;
}

void *add_node_left_and_right(t_btree **cmd)
{
	t_btree *node_left;
	t_btree *node_right;
	node_left = malloc(sizeof(t_btree));
	node_right = malloc(sizeof(t_btree));
	(*cmd)->left = node_left;
	(*cmd)->right = node_right;
}

void	btree_last(t_btree **cmd)
{
	t_btree *tmp;
	
	tmp = *cmd;
	*cmd = (*cmd)->right;
	(*cmd)->right = NULL;
	(*cmd)->left = NULL;
	*cmd = tmp;
}