#ifndef MINISHELL_H
#define MINISHELL_H


#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1000

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

enum e_token_type
{
    WORDS, // 0
    RET_TO, // 1
    RET_FROM, // 2
    DLESS, // 3
    DGREAT, // 4
    CMD_NAME, // 5
    CMD_WORD, // 6
    CMD_SUFFIX, // 7
    CMD_PREFIX, // 8
    IO_REDIRECT, // 9
    IO_FILE, // 10
    IO_HERE, // 11
    SIMPLE_COMMAND, // 12
    OPERATEUR_SEQUENCE, // 13
    PIPE_SEQUENCE, // 14
    PIPE, // 15
    CLOSE_PAR, // 16
    OPEN_PAR, // 17
    AND, // 18
    OR, // 19
    FILENAME, // 20
    END, // 21
};


typedef struct s_token
{
	int		token_type;
	char	*string;
}	t_token;                                              

typedef struct s_btree
{
	struct s_btree *left;
	struct s_btree *right;
	t_token	content;
}	t_btree;

typedef struct s_list
{
    struct s_list *next;
    t_token        content;
} t_list;

typedef	struct s_data
{
	t_btree **ast;
	t_list	**token_list;
	char	**envp;
	int		exit_status;
	int		pipefd[2][2];
    int     par;
	//int		quoting;
	//int		parenthese;
} t_data;

int     ft_strchr2( char d, char c);
int     ft_lenword(char const *str, char c);
char	*ft_strdup2(char const *src, char c);
int     ft_countword(char const *str, char c);
char	**ft_split(char const *s, char c);
t_list *lexer(char *input);
int     ft_strcmp(char *s1, char *s2);

size_t	ft_strlen(const char *str);

int		ft_isalnum(int c);

char	*ft_strdup(const char *s);

char	*ft_strjoin(char const *s1, char const *s2, char *sep);

void	*ft_calloc(size_t nmemb, size_t size);

//void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);


int		check_quote(char *str);

void	tokener(char *input, t_list **token_list);

int	check_op(t_list **token_list);
int	check_redir(t_list **token_list);

void *add_node_left_and_right(t_btree **cmd);
void *add_node_right(t_btree **cmd);
void *add_node_left(t_btree **cmd);
void	btree_last(t_btree **cmd);

t_btree *btree_create(t_list **token_list, t_data *data, int par);
t_btree *node_or(t_btree **cmd, t_list **token_list, t_data *data, int par);
t_btree *node_and(t_btree **cmd, t_list **token_list, t_data *data, int par);
t_btree *node_pipe( t_btree **cmd, t_list **token_list, t_data *data, int par);
t_btree	*btree_cmd(t_list **token_list, t_data *data, int par);
t_btree *btree_cmd_left(t_btree **cmd, t_list **stack);
t_btree *btree_cmd_right(t_btree **cmd, t_list **stack);

void	print_token_list(t_list *token_list);

t_list  *ft_listlast(t_list *list);
void    ft_lstadd_back(t_list **list, int token);
void    reduce(t_list **stack, t_list **token_list, int token, int nb_reduce);
void    shift(t_list **list, t_list **token_list);
int     parsing(t_list *token_list);



#endif
#endif 