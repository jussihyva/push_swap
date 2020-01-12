# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/12 15:45:19 by jkauppi           #+#    #+#              #
#    Updated: 2020/01/12 18:01:12 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1			=	checker
NAME2			=	push_swap

HEADER_FILE1	=	checker.h
HEADER_FILE2	=	push_swap.h

CC				=	clang

SRC_FOLDER		=	src
HEADER_FOLDER	=	./
OBJ_FOLDER		=	obj
TEST_FOLDER		=	basic_test
SRC_FILES_NAME	=	
OBJ_FILES		=	$(addprefix $(OBJ_FOLDER)/, $(patsubst ".c", ".o", $(SRC_FILES_NAME)))


all: $(NAME1) $(NAME2)

$(NAME1): $(OBJ_FILES)
	$(CC) -I $(HEADER_FOLDER) -o $@	$@.c $(OBJ_FILES)

$(NAME2): $(OBJ_FILES)
	$(CC) -I $(HEADER_FOLDER) -o $@	$@.c $(OBJ_FILES)

$(OBJ_FILES): $(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c $(HEADER_FILE1) $(HEADER_FILE2) | $(OBJ_FOLDER) $(SRC_FOLDER)
	$(CC) -c -o $@ $<

$(SRC_FOLDER):
	@mkdir $(SRC_FOLDER)

$(TEST_FOLDER):
	@mkdir $(TEST_FOLDER)

$(OBJ_FOLDER):
	@mkdir $(OBJ_FOLDER)

clean:
	@\rm -f $(OBJ_FOLDER)/*.o

fclean: clean
	@\rm -f $(NAME1)
	@\rm -f $(NAME2)

re: fclean all

test: | $(TEST_FOLDER)
	ls -1

.PHONY: all test clean fclean re
