# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/12 15:45:19 by jkauppi           #+#    #+#              #
#    Updated: 2020/02/14 07:48:02 by jkauppi          ###   ########.fr        #
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

I_FLAGS				=	-I $(HEADER_FOLDER) -I $(LIBFT_FOLDER) -I $(LIBFTPRINTF_FOLDER)/src
CC_FLAGS			=	-g -Wall -Werror -Wextra

SRC_FOLDER			=	src
HEADER_FOLDER		=	./
OBJ_FOLDER			=	obj
TEST_FOLDER			=	basic_test
SRC_FILES_NAME		=	ft_intswap.c ft_arraydel.c ft_intsort.c ft_intdup.c ft_strtoi.c ft_lstswap.c ft_lstsort.c \
						ft_int_array_dup.c \
						sort_common_1.c sort_common_2.c sort_common_3.c sort_common_4.c sort_common_5.c \
						memory_1.c memory_2.c \
						sort_bubble_v1.c sort_bubble_v2.c sort_bubble_v3.c \
						sort_insertion_v1.c \
						sort_random_v1.c \
						print_result.c \
						split_two_stacks.c \
						sort_less_moves_v4_1.c sort_less_moves_v4_2.c sort_less_moves_v4_3.c sort_less_moves_v4_4.c \
						group_integers.c \
						move_cost_1.c move_cost_2.c \
						move_next_1.c move_next_2.c move_next_3.c \
						move_pa_pb_functions.c sort_add_algorithms.c \
						common_1.c common_2.c checker_common.c

OBJ_FILES			=	$(addprefix $(OBJ_FOLDER)/, $(patsubst %.c, %.o, $(SRC_FILES_NAME)))

TEST_ARG			=	`ruby -e "puts (1..10000).to_a.shuffle.join(' ')"`


all: $(LIBFT_FOLDER) $(LIBFTPRINTF_FOLDER) $(NAME1) $(NAME2)

$(NAME1): $(OBJ_FILES) $(NAME1).c
	$(CC) $(CC_FLAGS) $(I_FLAGS) -o $@ $@.c $(OBJ_FILES) -L $(LIBFT_FOLDER) -l $(LIBFT) -L $(LIBFTPRINTF_FOLDER) -l $(LIBFTPRINTF)

$(NAME2): $(OBJ_FILES) $(NAME2).c
	$(CC) $(CC_FLAGS) $(I_FLAGS) -o $@ $@.c $(OBJ_FILES) -L $(LIBFT_FOLDER) -l $(LIBFT) -L $(LIBFTPRINTF_FOLDER) -l $(LIBFTPRINTF)

$(OBJ_FILES): $(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c $(HEADER_FILE1) $(HEADER_FILE2) | $(OBJ_FOLDER) $(SRC_FOLDER)
	$(CC) $(CC_FLAGS) $(I_FLAGS) -c -o $@ $<

$(SRC_FOLDER):
	@mkdir $(SRC_FOLDER)

$(TEST_FOLDER):
	@mkdir $(TEST_FOLDER)

$(OBJ_FOLDER):
	@mkdir $(OBJ_FOLDER)

$(LIBFT_FOLDER):
	@make -C $(LIBFT_FOLDER)

$(LIBFTPRINTF_FOLDER):
	@make -C $(LIBFTPRINTF_FOLDER)

clean:
	@\rm -f $(OBJ_FOLDER)/*.o
	@make -C $(LIBFT_FOLDER) clean

fclean: clean
	@\rm -f $(NAME1)
	@\rm -f $(NAME2)
	@make -C $(LIBFT_FOLDER) fclean

re: fclean all

norm:
	norminette ./*.[ch] $(SRC_FOLDER)/*.[ch]

test: | $(TEST_FOLDER)
	echo '$(TEST_ARG)'
	./push_swap $(TEST_ARG)
	./push_swap 1 2 8 4 -5

.PHONY: all test clean fclean re norm $(LIBFT_FOLDER) $(LIBFTPRINTF_FOLDER)
