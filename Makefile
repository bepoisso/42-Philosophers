# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/23 18:53:14 by bepoisso          #+#    #+#              #
#    Updated: 2025/01/23 19:01:19 by bepoisso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#_________________COLORS_________________

PURPLE = \033[0;35m
YELLOW = \033[0;93m
RESET = \033[0m

#_________________VARIABLE_________________

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I$(INC_DIR)
ARGS = 
VALARGS = --track-fds=yes --leak-check=full --track-origins=yes --show-leak-kinds=all --trace-children=yes
MAKEFLAGS += --no-print-directory

#_________________FILES_________________

SRC_DIR = ./srcs
OBJ_DIR = ./objs
INC_DIR = ./includes

SRC_FILES = \
			philo.c\
			parser.c\


SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

#_________________RULES_________________

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -Llibft -lft -o $(NAME)
		@echo "Create Program		✅"


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
		$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
		@mkdir -p $(OBJ_DIR)

clean:
		@rm -rf $(OBJ_DIR)
		@echo "Clean Program Objs	✅"

fclean: clean
		@rm -f $(NAME)
		@echo "Clean Program		✅"

re: fclean all

val:
		valgrind $(VALARGS) ./$(NAME) $(ARGS)

exec:
		./$(NAME) $(ARGS)

debug:
		gdb -tui -q ./$(NAME)

.PHONY: all clean fclean re
