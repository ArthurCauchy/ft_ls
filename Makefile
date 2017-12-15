# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acauchy <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/29 10:04:49 by acauchy           #+#    #+#              #
#    Updated: 2017/12/15 16:39:01 by acauchy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOR_GREEN = "\033[1;32;40m"
COLOR_RED = "\033[1;31;40m"
COLOR_YELLOW = "\033[1;33;40m"
COLOR_CYAN = "\033[1;36;40m"
COLOR_RESET = "\033[0m"

.PHONY: all clean fclean re compile

NAME = ft_ls

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC_NAME =	main.c \
		options.c \
		output.c \
		utils.c

OBJ_PATH = objs
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

LIBFT_PATH = libft
LIBFT_INCLUDE = -I$(LIBFT_PATH)
LIBFT = -L$(LIBFT_PATH) -lft

all: compile

$(OBJ_PATH)/%.o: %.c
	$(CC) -c $(CFLAGS) $< $(LIBFT_INCLUDE) -o $@

$(NAME): $(OBJ)
	@echo $(COLOR_YELLOW)"Linking "$@"..."$(COLOR_RESET)
	$(CC) $^ $(LIBFT) -o $@
	@echo $(COLOR_GREEN)$(NAME)" successfully created."$(COLOR_RESET)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

compile: $(OBJ_PATH)
	@echo $(COLOR_CYAN)"==Entering "$(LIBFT_PATH)"=="$(COLOR_RESET)
	@make -C $(LIBFT_PATH)
	@echo $(COLOR_CYAN)"==Exiting "$(LIBFT_PATH)"=="$(COLOR_RESET)
	@echo $(COLOR_YELLOW)"Compiling "$(NAME)"..."$(COLOR_RESET)
	@make $(NAME)

clean:
	@echo $(COLOR_RED)"Removing "$(OBJ_PATH)"..."$(COLOR_RESET)
	@rm -Rf $(OBJ_PATH)
	@echo $(COLOR_CYAN)"==Entering "$(LIBFT_PATH)"=="$(COLOR_RESET)
	@make -C $(LIBFT_PATH) clean
	@echo $(COLOR_CYAN)"==Exiting "$(LIBFT_PATH)"=="$(COLOR_RESET)

fclean: clean
	@echo $(COLOR_RED)"Removing "$(NAME)"..."$(COLOR_RESET)
	@rm -f $(NAME)
	@echo $(COLOR_CYAN)"==Entering "$(LIBFT_PATH)"=="$(COLOR_RESET)
	@make -C $(LIBFT_PATH) fclean
	@echo $(COLOR_CYAN)"==Exiting "$(LIBFT_PATH)"=="$(COLOR_RESET)

re: fclean all
