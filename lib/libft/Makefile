NAME := libft.a

CC := gcc

CFLAGS := -Wall -Wextra -Werror

SRCDIR := srcs

OBJDIR := objs

INCDIR := ../inc

INC := $(patsubst %.a,$(INCDIR)/%.h,$(NAME))

SRCS := ft_abs.c   ft_atoi.c     ft_isascii.c  ft_memcmp.c      ft_putendl_fd.c  ft_strdup.c    ft_strlen.c   ft_strtrim.c \
ft_bzero.c    ft_isdigit.c  ft_memcpy.c      ft_putnbr_fd.c   ft_striteri.c  ft_strmapi.c  ft_substr.c \
ft_calloc.c   ft_isprint.c  ft_memmove.c     ft_putstr_fd.c   ft_strjoin.c   ft_strncmp.c  ft_tolower.c \
ft_isalnum.c  ft_itoa.c     ft_memset.c      ft_split.c       ft_strlcat.c   ft_strnstr.c  ft_toupper.c \
ft_isalpha.c  ft_memchr.c   ft_putchar_fd.c  ft_strchr.c      ft_strlcpy.c   ft_strrchr.c  ft_array_size.c\
free_array.c  ft_strcmp.c   ft_max.c \
get_next_line.c  get_next_line_utils.c \
ft_printf.c   ft_printf_utils2.c     ft_printf_utils3.c     ft_printf_utils.c

OBJS := $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

green = /bin/echo -e "\x1b[32m$1\x1b[0m"
red = /bin/echo -e "\x1b[31m$1\x1b[0m"


all : $(NAME)



$(OBJDIR)/%.o : $(SRCDIR)/%.c $(INC)
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $< -I$(INCDIR)


$(NAME) : $(OBJS)
	$(call green,"Compiling libft...")
	ar -rcs $@ $^
	$(call green,"Done")


clean :
	$(call red,"Removing libft object files...")
	rm -fd $(OBJS) $(OBJDIR)


fclean :
	$(call red,"Removing libft object files and library...")
	rm -fd $(OBJS) $(OBJDIR) $(NAME)


re : fclean all


.PHONY : all clean fclean re

.SILENT: