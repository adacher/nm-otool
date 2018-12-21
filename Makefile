NAME1 = ft_nm
NAME2 = ft_otool

FLAGS = -Wall -Werror -Wextra

SRC_NM = srcs/nm.c \
		srcs/nm_errors.c \
		srcs/nm_macho.c \
		srcs/nm_fat.c \
		srcs/nm_sections.c \
		srcs/nm_display.c \
		srcs/nm_list.c \
		srcs/nm_mask.c \
		srcs/nm_ar.c \
		srcs/nm_symbols.c \
		srcs/nm_list_two.c

SRC_OTOOL = srcs/otool.c \
			srcs/otool_errors.c \
			srcs/otool_macho.c \
			srcs/otool_fat.c \
			srcs/otool_display.c \
			srcs/otool_ar.c \
			srcs/nm_mask.c

OBJ_NM = $(SRC_NM:.c=.o)
OBJ_OTOOL = $(SRC_OTOOL:.c=.o)

INC = -I libft \
		-I inc

LIB = -L libft/ -lft

all: $(NAME1) $(NAME2)

$(NAME1) $(NAME2): $(OBJ_NM) $(OBJ_OTOOL)
	@make -C libft/
	@gcc -o $(NAME1) $(OBJ_NM) 	  $(LIB) $(FLAGS)
	@gcc -o $(NAME2) $(OBJ_OTOOL) $(LIB) $(FLAGS)

%.o:%.c
	@gcc -g $(FLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJ_NM)
	rm -f $(OBJ_OTOOL)
	@make -C libft/ clean

fclean: clean
	rm -f $(NAME1)
	rm -f $(NAME2)
	@make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re