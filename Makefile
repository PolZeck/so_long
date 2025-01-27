NAME = so_long

# Compilateur et options
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Dossiers
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = includes
MLX_DIR = minilibx-linux
SUPER_LIBFT = super_libft

# Fichiers source et objets
SRC = $(SRC_DIR)/main.c
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Librairies
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
SUPER_LIBFT_LIB = $(SUPER_LIBFT)/super_libft.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -I$(MLX_DIR) -lXext -lX11 -lm
SUPER_LIBFT_FLAGS = $(SUPER_LIBFT)/super_libft.a

# Règles
all: $(MLX_LIB) $(SUPER_LIBFT_LIB) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(SUPER_LIBFT_FLAGS) $(MLX_FLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(SUPER_LIBFT) -I$(MLX_DIR) -c $< -o $@

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

$(SUPER_LIBFT_LIB):
	@$(MAKE) -C $(SUPER_LIBFT)

clean:
	@$(MAKE) -C $(SUPER_LIBFT) clean
	@$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(MLX_DIR) clean
	@$(MAKE) -C $(SUPER_LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re
