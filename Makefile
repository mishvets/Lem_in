# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mshvets <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/04 14:14:54 by mshvets           #+#    #+#              #
#    Updated: 2019/09/04 14:15:19 by mshvets          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# name of the executable file

NAME		:= lem-in

# project directories

SRC_DIR     = ./src/
OBJ_DIR     = ./obj/
INC_DIR     = ./inc/
LIB_DIR     = ./

# project source files

SRC             := $(SRC_DIR)main.c
SRC             += $(SRC_DIR)parsing.c
SRC             += $(SRC_DIR)parsing_room.c
SRC             += $(SRC_DIR)parsing_link.c
SRC             += $(SRC_DIR)find_way.c

# project object files

OBJ		        = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# libraries

LIB             := $(LIBFT_DIR)libft.a
LIBFT_DIR       := $(LIB_DIR)libft/
LIBFT_INC       := $(LIBFT_DIR)
LIBFT_FLAGS     := -lft -L $(LIBFT_DIR)

# compilation flags

CC_FLAGS        := -Wall -Wextra -Werror

# linking flags

LINK_FLAGS      := $(LIBFT_FLAGS)

# header flags

HEAD            := $(INC_DIR)lem-in.h
HEADER_FLAGS    := -I $(INC_DIR) -I $(LIBFT_INC)

# compiler

CC              := gcc

# rules

all: $(LIB) $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(LINK_FLAGS) -o $(NAME) -fsanitize=undefined

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CC_FLAGS) -c $< -o $@ $(HEADER_FLAGS)

$(LIB):
	@make -C $(LIBFT_DIR)

clean:
	@rm -f $(OBJ)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

reclean: fclean all
	@rm -f $(OBJ)
