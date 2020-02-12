# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/12 15:45:19 by jkauppi           #+#    #+#              #
#    Updated: 2020/02/12 13:40:01 by jkauppi          ###   ########.fr        #
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
SRC_FILES_NAME		=	ft_intswap.c ft_arraydel.c ft_intsort.c ft_intdup.c ft_strtoi.c \
						sort_common_1.c sort_common_2.c sort_common_3.c memory.c \
						sort_bubble_v1.c sort_bubble_v2.c sort_bubble_v3.c \
						sort_insertion_v1.c \
						sort_random_v1.c sort_random_v2.c sort_random_v3.c \
						action_rules_1.c action_rules_2.c action_rules_3.c \
						print_result.c \
						split_two_stacks.c \
						sort_bubble_v2_1.c sort_bubble_v2_2.c sort_bubble_v2_3.c sort_bubble_v2_4.c sort_bubble_v2_5.c \
						sort_bubble_v3_1.c \
						sort_less_moves_v1_1.c sort_less_moves_v1_2.c sort_less_moves_v1_3.c sort_less_moves_v1_4.c \
						sort_less_moves_v2_1.c \
						sort_less_moves_v3_1.c sort_less_moves_v3_2.c sort_less_moves_v3_3.c sort_less_moves_v3_4.c \
						sort_less_moves_v4_1.c sort_less_moves_v4_2.c sort_less_moves_v4_3.c sort_less_moves_v4_4.c \
						group_integers.c \
						move_cost.c move_next.c \
						move_pa_pb_functions.c sort_add_algorithms.c \
						common_1.c common_2.c checker_common.c

OBJ_FILES			=	$(addprefix $(OBJ_FOLDER)/, $(patsubst %.c, %.o, $(SRC_FILES_NAME)))

TEST_ARG			=	`ruby -e "puts (1..10000).to_a.shuffle.join(' ')"`


all: libft $(NAME1) $(NAME2)

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
	echo '$(TEST_ARG)'
	./push_swap $(TEST_ARG)
	./push_swap 1 2 8 4 -5

.PHONY: all test clean fclean re libft norm
