# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: DonKey <DonKey@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/02/17 06:10:07 by adacher           #+#    #+#              #
#    Updated: 2018/06/18 23:34:51 by DonKey           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEBUG=yes
NAME=libft.a
ifeq ($(DEBUG),yes)
	FLAGS=-Wall -Wextra -Werror
else
	FLAGS=
endif
FILES_C=ft_putstr.c ft_strrev.c ft_putendl.c ft_putchar.c ft_putnbr.c ft_putchar_fd.c \
ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_bzero.c ft_memccpy.c ft_memcpy.c \
ft_memset.c ft_memmove.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
ft_isprint.c ft_tolower.c ft_toupper.c ft_strlen.c ft_strnstr.c ft_putcolorendl.c \
ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c ft_strncat.c ft_strstr.c \
ft_strchr.c ft_strrchr.c ft_strmap.c ft_strmapi.c ft_strcmp.c ft_strncmp.c \
ft_atoi.c ft_itoa.c ft_memalloc.c ft_memdel.c ft_memchr.c ft_memcmp.c ft_strnew.c \
ft_strdel.c ft_strsplit.c ft_strtrim.c ft_strclr.c ft_striter.c ft_striteri.c ft_strequ.c \
ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strlcat.c ft_putcolor.c \
ft_isupper.c ft_islower.c ft_strclen.c ft_lstadd.c ft_lstnew.c ft_lstiter.c ft_lstdel.c \
ft_lstdelone.c ft_lstmap.c ft_isspace.c ft_tablen.c get_next_line.c del_array.c ft_nbrlen.c
FILES_O=$(FILES_C:.c=.o)

all: $(NAME)

$(NAME): make_obj do_lib
	@echo "\\033[1;32mLibrary created."

do_lib: make_obj
	@ar rc $(NAME) $(FILES_O)
	@ranlib $(NAME)

make_obj:
ifeq ($(DEBUG),yes)
	@echo "\\033[1;31mHi,\\033[0;39m"
else
	@echo "\\033[1;31mNo flags.\\033[0;39m"
endif
	@echo "\\033[1;34mObjects incoming, please wait."
	@gcc $(FLAGS) -c $(FILES_C)
clean:
	@rm -f $(FILES_O)
fclean: clean
	@echo "\\033[1;31mDeleting libft.a..."
	@rm -f $(NAME)
re: fclean all
.PHONY: clean fclean re