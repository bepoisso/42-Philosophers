# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/23 18:53:14 by bepoisso          #+#    #+#              #
#    Updated: 2025/02/12 13:59:34 by bepoisso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#_________________COLORS_________________

PURPLE = \033[0;35m
YELLOW = \033[0;93m
RESET = \033[0m

#_________________VARIABLE_________________

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR)
ARGS = 10 8000 200 200 3
VALARGS = --leak-check=full --track-origins=yes --show-leak-kinds=all #--trace-children=yes --track-fds=yes
MAKEFLAGS += --no-print-directory

#_________________FILES_________________

SRC_DIR = ./srcs
OBJ_DIR = ./objs
INC_DIR = ./includes

SRC_FILES = \
			main.c\
			utils.c\
			parser.c\
			philo.c\
			init.c\
			manip.c\
			simulation.c\
			clean.c\
			mutex_handle.c\
			thread_handle.c\


SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

#_________________RULES_________________

all: $(NAME)

$(NAME): $(OBJS)
		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
		@echo "Create Program		✅"
		@echo "$(YELLOW)__________.__    .__.__                            .__                         $(RESET)"
		@echo "$(YELLOW)\______   \  |__ |__|  |   ____  __________ ______ |  |__   ___________  ______$(RESET)"
		@echo "$(YELLOW) |     ___/  |  \|  |  |  /  _ \/  ___/  _ \\____ \|  |  \_/ __ \_  __ \/  ___/$(RESET)"
		@echo "$(YELLOW) |    |   |   Y  \  |  |_(  <_> )___ (  <_> )  |_> >   Y  \  ___/|  | \/\___ \ $(RESET)"
		@echo "$(YELLOW) |____|   |___|  /__|____/\____/____  >____/|   __/|___|  /\___  >__|  /____  >$(RESET)"
		@echo "$(YELLOW)               \/                   \/      |__|        \/     \/           \/ $(RESET)"
		@echo "$(PURPLE)                                                               By bepoisso 🐟  $(RESET)"
		@echo "$(PURPLE)🤖 To execute : ./philo nbr_philo time_to_die time_to_eat time_to_sleep (nbr_of_meals) 🤖$(RESET)"


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
		@$(CC) $(CFLAGS) -c $< -o $@

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

hel: re
		valgrind --tool=helgrind --history-level=none  ./$(NAME) $(ARGS)

exec:
		./$(NAME) $(ARGS)

debug:
		gdb -tui -q ./$(NAME)

.PHONY: all clean fclean re