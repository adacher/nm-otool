NAME1 = ft_nm
NAME2 = ft_otool

FLAGS = -Wall -Werror -Wextra

SRC_NM = srcs/nm/nm.c \
		srcs/nm/ar_and_fat/fat.c \
		srcs/nm/ar_and_fat/ar.c \
		srcs/nm/display/errors.c \
		srcs/nm/display/display.c \
		srcs/nm/display/symbols.c \
		srcs/nm/64/loadcmd_64.c\
		srcs/nm/64/mask_64.c\
		srcs/nm/64/sections_64.c\
		srcs/nm/64/sort_64.c\
		srcs/nm/64/symtable_64.c\
		srcs/nm/32/loadcmd_32.c\
		srcs/nm/32/mask_32.c\
		srcs/nm/32/sections_32.c\
		srcs/nm/32/symtable_32.c\
		srcs/universal/check_file.c \
		srcs/universal/check_32.c \
		srcs/universal/check_64.c \
		srcs/universal/tests.c

SRC_OTOOL = srcs/otool/otool.c \
			srcs/otool/otool_errors.c \
			srcs/otool/otool_macho.c \
			srcs/otool/otool_fat.c \
			srcs/otool/otool_display.c \
			srcs/otool/otool_ar.c \
			srcs/otool/otool_mask.c

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