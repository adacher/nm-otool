NAME1 = ft_nm
NAME2 = ft_otool

FLAGS = -Wall -Werror -Wextra

SRC_NM = srcs/nm/nm.c \
		srcs/nm/fat/fat_32.c \
		srcs/nm/fat/fat_64.c \
		srcs/nm/archive/ar.c \
		srcs/nm/display/display.c \
		srcs/nm/display/symbols.c \
		srcs/nm/64/loadcmd_64.c\
		srcs/nm/64/sections_64.c\
		srcs/nm/64/symtable_64.c\
		srcs/nm/32/loadcmd_32.c\
		srcs/nm/32/sections_32.c\
		srcs/nm/32/symtable_32.c\
		srcs/universal/check_file.c \
		srcs/universal/check_32.c \
		srcs/universal/check_64.c \
		srcs/universal/check_fat32.c \
		srcs/universal/check_fat64.c \
		srcs/universal/mask.c \
		srcs/universal/ppc.c \
		srcs/universal/swap.c \
		srcs/nm/list/insertion_sort.c \
		srcs/universal/errors.c

SRC_OTOOL = srcs/otool/otool.c \
			srcs/otool/loadcmd_32.c\
			srcs/otool/loadcmd_64.c \
			srcs/otool/fat_32.c \
			srcs/otool/fat_64.c \
			srcs/otool/display.c \
			srcs/otool/ar.c \
			srcs/universal/mask.c \
			srcs/universal/check_file.c \
			srcs/universal/check_32.c \
			srcs/universal/check_64.c \
			srcs/universal/check_fat32.c \
			srcs/universal/check_fat64.c \
			srcs/universal/ppc.c \
			srcs/universal/swap.c \
			srcs/universal/errors.c

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