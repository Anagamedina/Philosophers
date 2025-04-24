# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/02 17:19:39 by anamedin          #+#    #+#              #
#    Updated: 2025/04/25 00:42:52 by anamedin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
CC = cc
CFLAGS = -Wall -Wextra -Werror -Ipthread #-g -fsanitize=address
#CFLAGS = -Wall -Wextra -Werror -pthread -g -fsanitize=thread
RM = rm -rf

# Executable name and header
NAME = philo
HEADER = include/philo.h

# Directories
SRC_DIR = src
OBJ_DIR = obj

# Source and object files
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/parse_utils.c \
       $(SRC_DIR)/init_structs.c \
       $(SRC_DIR)/init_config.c \
       $(SRC_DIR)/free.c \
       $(SRC_DIR)/philosopher_threads.c \
       $(SRC_DIR)/fork_control.c \
       $(SRC_DIR)/time.c \
       $(SRC_DIR)/death_monitor.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Default rule
all: $(NAME)

# Linking rule
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	chmod +x $(NAME)
	@echo "\033[1;32mCompilation finished successfully! ✅\033[0m"

# Compilation rule
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) Makefile 
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	$(RM) $(OBJ_DIR)

# Clean all generated files
fclean: clean
	$(RM) $(NAME)

# Recompile everything
re: fclean all

.PHONY: all clean fclean re
