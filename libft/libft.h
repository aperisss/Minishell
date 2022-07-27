/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:51:21 by ppajot            #+#    #+#             */
/*   Updated: 2022/07/24 18:43:23 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_list {
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_flags {
	int	precision;
	int	minsize;
	int	leftzero;
	int	rightfill;
	int	hexprefix;
	int	spacesign;
}	t_flags;

int			ft_max(int i, int j);
int			isflags(char c);
int			ft_fill(char c, int len, int *count);
void		putchar_flags(va_list arg, t_flags flags, int *count);
void		putstring_flags(va_list arg, t_flags flags, int *count);
int			hassign(long i, t_flags flags, char convert);
void		putsign(long *i, t_flags flags, int *count, char convert);
int			getsize_base(long l, t_flags flags, char convert);
void		ft_putnbr_long(unsigned long nbr, char *base, int *count);
void		putnbrleftzero(long i, t_flags flags, int *count, char convert);
void		putnbr_flags(va_list arg, t_flags flags, int *count, char convert);
void		ft_putnbr(long i, char convert, int *count);
void		ft_flags(char **str, t_flags *flags);
const char	*ft_put(va_list arg, const char *format,
				t_flags *flags, int *count);

int			ft_printf(const char *format, ...);

long		ft_convert(long l, char convert);
void		setflags(t_flags *flags);
int			atoi_move(char **str);
int			ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
char		*ft_itoa(int n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);
char		**ft_split(char const *s, char c);
char		*ft_strchr(const char *str, int c);
char		*ft_strdup(const char *s);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_strjoin(char const *s1, char const *s2, char *c);
size_t		ft_strlcat(char *dest, const char *src, size_t size);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strrchr(const char *str, int c);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_tolower(int c);
int			ft_toupper(int c);
void		*ft_memset(void *s, int c, size_t n);
void		ft_putchar_fd(char c, int fd);
size_t		ft_strlen(const char *str);

void		ft_lstadd_back(t_list **lst, t_list *new);
t_list		*ft_lstnew(void *content);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, int (*f)(void *), void (*del)(void *));
int			ft_lstsize(t_list *lst);

int			ft_abs(int a);
char		*end_file(char *result, char currentl[BUFFER_SIZE + 1]);
char		*cat_alloc(char newend[BUFFER_SIZE + 1], char *oldres, int size);
int			nextendl(char line[BUFFER_SIZE + 1]);
int			checkendl(char currentl[BUFFER_SIZE + 1],
				char line[BUFFER_SIZE + 1], char **result);

char		*get_next_line(int fd);

char		*initres(void);
void		pushback(char currentl[BUFFER_SIZE + 1],
				char line[BUFFER_SIZE + 1], int newbegin);
int			read_endbuff(int fd, char buff[BUFFER_SIZE + 1]);
char		*free_res(char *result);
void		free_array(char **array);

#endif