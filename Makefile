# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/12 15:45:19 by jkauppi           #+#    #+#              #
#    Updated: 2020/01/25 12:54:45 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1				=	checker
NAME2				=	push_swap

HEADER_FILE1		=	checker.h
HEADER_FILE2		=	push_swap.h

CC					=	clang

LIBFT				=	ft
LIBFT_FOLDER		=	libft
LIBFTPRINTF			=	ftprintf
LIBFTPRINTF_FOLDER	=	libftprintf

I_FLAGS				=	-I $(HEADER_FOLDER) -I $(LIBFT_FOLDER) -I $(LIBFTPRINTF_FOLDER)
CC_FLAGS			=	-g -Wall -Werror -Wextra

SRC_FOLDER			=	src
HEADER_FOLDER		=	./
OBJ_FOLDER			=	obj
TEST_FOLDER			=	basic_test
SRC_FILES_NAME		=	ft_intswap.c ft_arraydel.c ft_intsort.c \
						sort_common_1.c sort_common_2.c sort_common_3.c \
						sort_bubble_v1.c sort_bubble_v2.c sort_bubble_v3.c \
						sort_insertion_v1.c \
						sort_random_v1.c sort_random_v2.c \
						action_rules_1.c action_rules_2.c \
						print_result.c

OBJ_FILES			=	$(addprefix $(OBJ_FOLDER)/, $(patsubst %.c, %.o, $(SRC_FILES_NAME)))

TEST_ARG			=	`ruby -e "puts (1..10000).to_a.shuffle.join(' ')"`


all: libft $(NAME1) $(NAME2)

$(NAME1): $(OBJ_FILES) $(NAME1).c
	$(CC) $(CC_FLAGS) $(I_FLAGS) -o $@_1 $@.c $(OBJ_FILES) -L $(LIBFT_FOLDER) -l $(LIBFT) -L $(LIBFTPRINTF_FOLDER) -l $(LIBFTPRINTF)

$(NAME2): $(OBJ_FILES) $(NAME2).c
	$(CC) $(CC_FLAGS) $(I_FLAGS) -o $@ $@.c $(OBJ_FILES) -L $(LIBFT_FOLDER) -l $(LIBFT) -L $(LIBFTPRINTF_FOLDER) -l $(LIBFTPRINTF)

$(OBJ_FILES): $(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c $(HEADER_FILE1) $(HEADER_FILE2) $(LIBFT_FOLDER) | $(OBJ_FOLDER) $(SRC_FOLDER)
	$(CC) $(CC_FLAGS) $(I_FLAGS) -c -o $@ $<

$(SRC_FOLDER):
	@mkdir $(SRC_FOLDER)

$(TEST_FOLDER):
	@mkdir $(TEST_FOLDER)

$(OBJ_FOLDER):
	@mkdir $(OBJ_FOLDER)

libft:
	@make -C $(LIBFT_FOLDER)

clean:
	@\rm -f $(OBJ_FOLDER)/*.o

fclean: clean
	@\rm -f $(NAME1)
	@\rm -f $(NAME2)

re: fclean all

norm:
	norminette ./*.[ch] $(SRC_FOLDER)/*.[ch]

test: | $(TEST_FOLDER)
#	./push_swap $(TEST_ARG)
	./push_swap 1 2 8 4 -5

.PHONY: all test clean fclean re libft norm
