# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/02 17:19:39 by anamedin          #+#    #+#              #
#    Updated: 2025/04/10 15:06:44 by anamedin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Variables de compilación
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude #-g -fsanitize=address
RM = rm -rf

# Nombre del ejecutable y archivo de cabecera
NAME = philo
HEADER = include/philo.h

# Directorios
SRC_DIR = src
OBJ_DIR = obj

# Archivos fuente y objetos
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/parse_utils.c \
       $(SRC_DIR)/init_structs.c \
       $(SRC_DIR)/init_config.c \
       $(SRC_DIR)/philosopher_threads.c \
       $(SRC_DIR)/fork_control.c \
       $(SRC_DIR)/death_monitor.c
#include "philo.h"

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Regla por defecto
all: $(NAME)

# Crear el ejecutable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	chmod +x $(NAME)

# Regla para compilar archivos .c a .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) Makefile
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Eliminar archivos objeto
clean:
	$(RM) $(OBJ_DIR)

# Eliminar archivos objeto y el archivo ejecutable
fclean: clean
	$(RM) $(NAME)

# Reconstruir todo
re: fclean all

# Archivos que no son objetivos de archivos
.PHONY: all clean fclean re


