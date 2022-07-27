SRC := ft_abs.c   ft_atoi.c     ft_isascii.c  ft_memcmp.c      ft_putendl_fd.c  ft_strdup.c    ft_strlen.c   ft_strtrim.c \
ft_bzero.c    ft_isdigit.c  ft_memcpy.c      ft_putnbr_fd.c   ft_striteri.c  ft_strmapi.c  ft_substr.c \
ft_calloc.c   ft_isprint.c  ft_memmove.c     ft_putstr_fd.c   ft_strjoin.c   ft_strncmp.c  ft_tolower.c \
ft_isalnum.c  ft_itoa.c     ft_memset.c      ft_split.c       ft_strlcat.c   ft_strnstr.c  ft_toupper.c \
ft_isalpha.c  ft_memchr.c   ft_putchar_fd.c  ft_strchr.c      ft_strlcpy.c   ft_strrchr.c	ft_printf.c \
ft_printf_utils.c   ft_printf_utils2.c   ft_printf_utils3.c   ft_strcmp.c \
ft_lstadd_back.c ft_lstadd_front.c  ft_lstclear.c \
ft_lstdelone.c  ft_lstiter.c  ft_lstlast.c \
ft_lstmap.c     ft_lstnew.c   ft_lstsize.c \
get_next_line.c get_next_line_utils.c free_array.c

OBJ := $(patsubst %.c,%.o,$(SRC))

NAME := libft.a

all: libft.a


%.o: %.c libft.h
	gcc -Wall -Wextra -Werror -c -o $@ $< -I./


$(NAME) : $(OBJ)
	ar -rcs $@ $^


clean:
	rm -f $(OBJ)


fclean:
	rm -f $(OBJ) libft.a


re: fclean all


