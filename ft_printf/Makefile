# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/18 14:33:15 by pledieu           #+#    #+#              #
#    Updated: 2025/02/10 13:21:11 by pledieu          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

BLUE   = \033[1;32m

NAME = ft_printf.a

# Compilateur et options
CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIC

SRC =   ft_printf.c\
        ft_utils.c\
        ft_handlers.c\
        ft_handlers2.c\
        ft_parser.c\
        ft_utils2.c\
		get_next_line.c\
		get_next_line_utils.c\

OBJ = $(SRC:.c=.o)

# Liste des headers
HEADERS = ft_printf.h

# Chemin vers la libft
LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

# Règle principale
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_A)
	@ar x $(LIBFT_A)
	@ar rcs $(NAME) $(OBJ) *.o
	@rm -f *.o
	@echo  "$(BLUE)ft_printf.a créé avec succès ! ✅"

# Compile la libft
$(LIBFT_A):
	@make -C $(LIBFT_DIR)

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

# Recompilation complète
re: fclean all

# Commandes pas liées à des fichiers
.PHONY: all clean fclean re
