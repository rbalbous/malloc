ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc.so
HOST = libt_malloc_$(HOSTTYPE).so

CC = gcc
FLAGS = -Wall -Wextra -Werror -Ofast

INCLUDES = includes

OBJ_PATH = obj

SRCS =	ft_malloc.c \
		free.c \
		realloc.c \
		show_alloc_mem.c
SRCS_PATH = srcs/
SRCS_OBJ = $(addprefix $(OBJ_PATH)/, $(SRCS:.c=.o))

LIB_PATH = libft
LIB = $(LIB_PATH)/libft.a

all:
	@make $(LIB)
	@make $(NAME)

$(LIB)	:
			make -j -C $(LIB_PATH)

$(NAME) :	$(LIB) $(SRCS_OBJ)
			ln -fs $(HOST) $(NAME)
			$(CC) -shared $^ -o $(NAME)


$(OBJ_PATH)/%.o:  $(SRCS_PATH)/%.c $(INCLUDES)/ft_malloc.h
					@mkdir -p $(OBJ_PATH)
					$(CC) -o $@ -c $< -I $(INCLUDES) -I $(LIB_PATH)/includes $(FLAGS)

norme:
	@norminette srcs/**/*.c srcs/**/**/*.c includes | grep Error -B 1 > norm.out
	@echo "--" >> norm.out
	@norminette srcs/**/*.c srcs/**/**/*.c includes | grep Warning -B 1 >> norm.out

clean :
			make -C $(LIB_PATH) clean
			rm -f $(SRCS_OBJ)

fclean :	clean
			rm -f $(NAME)
			rm -f $(HOST)

re : 	
			make fclean 
			make all

.PHONY : all clean fclean re
