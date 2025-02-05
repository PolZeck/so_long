NAME = so_long
NAME_BONUS = so_long_bonus

# Compilateur et options
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -MMD -MP

# Dossiers
SRC_DIR = src
SRC_BONUS_DIR = src_bonus
OBJ_DIR = obj
OBJ_BONUS_DIR = obj_bonus
DEP_DIR = dep
DEP_BONUS_DIR = dep_bonus
INCLUDE_DIR = includes
MLX_DIR = minilibx-linux
SUPER_LIBFT = super_libft
LIBFT_DIR = $(SUPER_LIBFT)/libft

# Fichiers source
SRC = $(SRC_DIR)/main.c $(SRC_DIR)/game.c $(SRC_DIR)/map.c $(SRC_DIR)/utils.c \
	  $(SRC_DIR)/check_map.c $(SRC_DIR)/render.c $(SRC_DIR)/set.c \
	  $(SRC_DIR)/render_mouv.c $(SRC_DIR)/texture.c $(SRC_DIR)/flood_fill.c \
	  $(SRC_DIR)/check_map_walls.c

SRC_BONUS = $(SRC_BONUS_DIR)/main_bonus.c $(SRC_BONUS_DIR)/game_bonus.c \
			$(SRC_BONUS_DIR)/map_bonus.c $(SRC_BONUS_DIR)/utils_bonus.c \
			$(SRC_BONUS_DIR)/check_map_bonus.c $(SRC_BONUS_DIR)/render_bonus.c \
			$(SRC_BONUS_DIR)/set_bonus.c $(SRC_BONUS_DIR)/render_mouv_bonus.c \
			$(SRC_BONUS_DIR)/texture_bonus.c $(SRC_BONUS_DIR)/flood_fill_bonus.c \
			$(SRC_BONUS_DIR)/check_map_walls_bonus.c $(SRC_BONUS_DIR)/ennemies_bonus.c \
			$(SRC_BONUS_DIR)/ennemies_utils_bonus.c \

# Fichiers objets et dépendances
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_BONUS = $(SRC_BONUS:$(SRC_BONUS_DIR)/%.c=$(OBJ_BONUS_DIR)/%.o)
DEP = $(SRC:$(SRC_DIR)/%.c=$(DEP_DIR)/%.d)
DEP_BONUS = $(SRC_BONUS:$(SRC_BONUS_DIR)/%.c=$(DEP_BONUS_DIR)/%.d)

# Fichiers headers
HEADERS = $(INCLUDE_DIR)/so_long.h
HEADERS_BONUS = $(INCLUDE_DIR)/so_long_bonus.h

# Librairies
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
SUPER_LIBFT_LIB = $(SUPER_LIBFT)/super_libft.a
LIBFT_LIB = $(LIBFT_DIR)/libft.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -I$(MLX_DIR) -lXext -lX11 -lm
SUPER_LIBFT_FLAGS = $(SUPER_LIBFT)/super_libft.a

# Règles principales
all: $(MLX_LIB) $(SUPER_LIBFT_LIB) $(LIBFT_LIB) $(NAME)

$(NAME): $(OBJ) $(SUPER_LIBFT_LIB) $(LIBFT_LIB) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(SUPER_LIBFT_FLAGS) $(MLX_FLAGS)

bonus: $(MLX_LIB) $(SUPER_LIBFT_LIB) $(LIBFT_LIB) $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS) $(SUPER_LIBFT_LIB) $(LIBFT_LIB) $(HEADERS_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME_BONUS) $(SUPER_LIBFT_FLAGS) $(MLX_FLAGS)

# Compilation des fichiers source
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR) $(DEP_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(SUPER_LIBFT) -I$(MLX_DIR) -c $< -o $@

$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c $(HEADERS_BONUS)
	@mkdir -p $(OBJ_BONUS_DIR) $(DEP_BONUS_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(SUPER_LIBFT) -I$(MLX_DIR) -c $< -o $@

# Recompiler si des fichiers de super_libft ou libft sont modifiés
$(SUPER_LIBFT_LIB): $(wildcard $(SUPER_LIBFT)/*.c)
	@$(MAKE) -C $(SUPER_LIBFT)

$(LIBFT_LIB): $(wildcard $(LIBFT_DIR)/*.c)
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

# Nettoyage
clean:
	@$(MAKE) -C $(SUPER_LIBFT) clean
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(OBJ_DIR) $(OBJ_BONUS_DIR) $(DEP_DIR) $(DEP_BONUS_DIR)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	@$(MAKE) -C $(SUPER_LIBFT) fclean
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# Inclusion des dépendances
-include $(DEP)
-include $(DEP_BONUS)

.PHONY: all bonus clean fclean re
