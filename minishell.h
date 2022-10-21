/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis <aperis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 21:36:19 by ppajot            #+#    #+#             */
/*   Updated: 2022/09/21 19:51:21 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include "lib/inc/list.h"
# include "lib/inc/libft.h"
# include <dirent.h>

# define BASE_PATH "/mnt/nfs/homes/ppajot/bin:/mnt/nfs/homes/ppajot/bin:/usr/\
local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/\
local/games:/snap/bin"

# define PROMPT_OK "minishell ➜ "
# define PROMPT_KO "minishell ➜ "

extern unsigned char	g_exit_status;

enum e_token_type
{
	WORDS,
	RET_FROM,
	RET_TO,
	DLESS,
	DGREAT,
	PIPE,
	OPEN_PAR,
	CLOSE_PAR,
	AND,
	OR,
	SIMPLE_COMMAND,
	OPERATEUR_SEQUENCE,
	PIPE_SEQUENCE,
};

typedef struct s_builtin
{
	char	*name;
	int		(*fct)(char **, void *);
}	t_builtin;

typedef struct s_token
{
	int		token_type;
	char	*string;
}	t_token;

typedef struct s_dict
{
	char	*name;
	char	*value;
	int		print;
}	t_dict;

typedef struct s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	t_token			content;
}	t_btree;

typedef struct s_wild
{
	int		i;
	int		j;
	int		k;
	char	*str_wild;
	char	*wild;
}	t_wild;

typedef struct s_data
{
	t_btree		*ast;
	t_list		*token_list;
	char		**cmd_av;
	int			**hd_pfd;
	int			hd_nbr;
	t_list		*envp;
	int			exit_status;
	int			cmd_nbr;
	int			pfd[2][2];
	int			tempfd[2];
	int			par;
	int			op;
	t_builtin	builtin_tab[7];
	char		**ret;
	int			i;
	char		*cwd;
	t_wild		w;
}	t_data;

// btree_cmd_construct.c

void	last_free(t_data *data);
void	double_sig(void);
void	sig_double(void);
void	reinit_root(t_btree **root, int *i);
void	put_value_backslash(char *value, t_data *data);
void	free_exit(t_data *data, char **av);

t_btree	*btree_cmd_left(t_btree **cmd, t_list **stack);
t_btree	*btree_cmd_right(t_btree **cmd, t_list **stack);
void	cmd_right(t_btree **cmd, t_btree *tmp, t_token *token2);
void	cmd_left(t_btree **cmd, t_list **stack, t_list **sless);
void	stack_up(t_list **stack, t_list **stackless);

//btree_pipe.c

t_btree	*tree_pipe(t_list **token_list, t_data *data, int par);
void	shift_pipe(t_list **token_list, t_list **stack, t_data *data);
int		next_op(t_list *token_list);
void	after_par(t_list **token_list);
void	init_string(t_btree **cmd, t_list **token_list);

//btree_utils.c

void	shift(t_list **list, t_list **token_list);
void	add_node_left_and_right(t_btree **cmd);
void	add_node_right(t_btree **cmd);
void	add_node_left(t_btree **cmd);
void	btree_last(t_btree **cmd);

//btree_utils2.c

int		check_op(t_list **token_list);
int		check_redir(t_list **token_list);
t_list	*ft_listlast(t_list *list);
void	init_r(t_list **tl, t_list **st, t_list **s);
void	init_token(t_token **t, t_token **t2, t_list *stack, t_list *sless);

//btree.c

t_btree	*btree_create(t_list **token_list, t_data *data, int par);
t_btree	*node_op(t_btree **cmd, t_list **token_list, t_data *data, int par);
t_btree	*create_node_op(t_btree **cmd, t_list **token_list, t_data *data);
t_btree	*init_node_op(t_btree *cmd, t_list *token_list, t_data *data);
t_btree	*btree_cmd(t_list **token_list, t_data *data, int par);

//btree_wildcards.c

t_btree	*create_node_wildcards(t_btree **cmd, t_data *data);
void	init_cmd(t_btree **cmd);

//builtins

int		ft_export(char **av, void *arg);
int		ft_unset(char **av, void *arg);
int		ft_echo(char **av, void *arg);
int		ft_cd(char **av, void *arg);
int		ft_pwd(char **av, void *arg);
int		ft_env(char **av, void *arg);
int		ft_exit(char **av, void *arg);

//builtin utils

int		init_builtin(t_data *data);
int		check_name(char *str, int unset);
void	write_protect(char *str, t_data *data, int len);

//cd_utils.c

int		check_symlink(char *curpath, int i);
int		get_prev_slash(char *curpath, int i);
char	*reduce_points(char *curpath);

//export_utils.c

void	put_declare(t_data *data);

//check_quote.c

int		check_quote(char *str);

//env_utils.c

void	remove_entry(char *name, t_list **envp);
void	create_entry(char *str, t_data *data);
int		env_var_exists(char *name, t_data *data);

//env.c

void	put_env(char *name, char *value, int print, t_data *data);
char	*ft_getenv(char *name, t_list *env_list);
char	**list_to_tab(t_list *env_list);
t_list	*tab_to_list(char **env, t_data *data);

//exec_builtin.c

int		exec_builtin(int builtin_nbr, t_data *data);
int		exec_single_builtin(t_btree *root, t_data *data);

//exec_cmd.c

char	**fill_av(t_btree *root);
int		redir(t_btree *root, t_data *data);
int		exec_cmd(t_btree *root, t_data *data);

//exec_pipe_seq.c

void	exec_pipe_seq(t_btree *root, int n, t_data *data);

//exec_tree.c

int		exec_tree(t_btree *root, t_data *data);

//exec_utils.c

void	ft_dup(int fd_in, int fd_out, t_data *data);
int		is_builtin(char *cmd, t_data *data);
int		size_left(t_btree *root);
void	close_fd(t_data *data);
int		count_cmd(t_btree *root);

//expand_env.c

char	*expand_env(char *str, t_data *data);
int		expand_here_doc(int here_doc_fd, t_data *data);
void	neg_quote_dollar(char *str, int pos_neg);
char	*replace_env(char **str, int i, t_data *data);

//expand_quote.c

void	expand_quote(t_btree *root, t_data *data, t_btree *prev);
char	*reduce_quote(char *str);

//fill_hd.c

int		fill_hd(t_data *data, char *lim, int count);

//free functions

void	free_token(void *content);
void	free_entry(void *content);
void	free_tree(t_btree *root);
void	free_builtin(t_data *data);
void	free_list(t_list *list);
void	free_and_next(t_list **list);
void	free_file(char **file);
void	free_data(t_data *data);
void	free_hd_pfd(t_data *data, int mode);
void	free_content(char *str);

//get_input.c

char	*get_input(void);

//here_doc.c

int		here_doc_fd(t_data *data);
void	open_hd(t_btree *root, t_data *data);

//lexer.c

t_list	*lexer(char *input, t_data *data);

//tokener_utils.c

int		is_op(char c);
int		token_and_reset(char *temp, t_list **token_list, int *i);

//tokener.c

int		tokenization(char *str, t_list **token_list);
t_token	*create_content(char *str, int a);
void	is_in_quote(char c, int *quoting, int neg);
int		tokener(char *input, t_list **token_list, char *temp);

//utils.c

int		check_free(void **tab, int i);
void	exit_error(int av, t_data *data, int exit_status, char *exit_str);
void	sig_handler_int(int signum);
void	display(t_btree *ast, int lvl);
void	print_token_list(t_list *list);

//wildcards_readdir.c

char	**read_dir(t_data *data, int mode);
void	mode_conditions(char **file, struct dirent *dir, int mode, int *i);
void	init_wild(t_wild *w);

//wirldcards_utils.c

int		only_wildcards(char *str, int k);
char	**return_wildcards(char **file, char *str);
void	reinit_wildcards(t_wild *w);
char	*ft_strjoin2(char *s1, char *s2);
int		wc_is_unquote(char *str, int n);

//wildcards.c

char	**wildcards(char *str, t_data *data);
char	**get_wildcards(char **file, char *str, t_data *data);
int		after_wildcards(t_wild *w, char **file, char *str);
char	*get_str_wild(char *str, t_wild *w);
int		str_wild_chr(char *str_wild, char *file, int *k);

#endif
