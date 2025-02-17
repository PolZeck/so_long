# **************************************************************************** #
#                                  🎮 SO_LONG 🎮                               #
# **************************************************************************** #
NAME = so_long
NAME_BONUS = so_long_bonus

# ⚙️ Compilateur et options
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -MMD -MP

# 📁 Dossiers
SRC_DIR = src
SRC_BONUS_DIR = src_bonus
OBJ_DIR = obj
OBJ_BONUS_DIR = obj_bonus
DEP_DIR = dep
DEP_BONUS_DIR = dep_bonus
INCLUDE_DIR = includes
MLX_DIR = minilibx-linux
FT_PRINTF = ft_printf
LIBFT_DIR = $(FT_PRINTF)/libft
 
# 📄 Fichiers source
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
			$(SRC_BONUS_DIR)/ennemies_utils_bonus.c $(SRC_BONUS_DIR)/free_bonus.c

# 🗃️ Fichiers objets et dépendances
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_BONUS = $(SRC_BONUS:$(SRC_BONUS_DIR)/%.c=$(OBJ_BONUS_DIR)/%.o)
DEP = $(SRC:$(SRC_DIR)/%.c=$(DEP_DIR)/%.d)
DEP_BONUS = $(SRC_BONUS:$(SRC_BONUS_DIR)/%.c=$(DEP_BONUS_DIR)/%.d)

# 📚 Fichiers headers
HEADERS = $(INCLUDE_DIR)/so_long.h
HEADERS_BONUS = $(INCLUDE_DIR)/so_long_bonus.h

# 🔗 Librairies
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
FT_PRINTF_LIB = $(FT_PRINTF)/ft_printf.a
LIBFT_LIB = $(LIBFT_DIR)/libft.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -I$(MLX_DIR) -lXext -lX11 -lm
FT_PRINTF_FLAGS = $(FT_PRINTF)/ft_printf.a

# 🎯 Règles principales
all: $(MLX_LIB) $(FT_PRINTF_LIB) $(LIBFT_LIB) $(NAME)
	@echo "\033[32m✅ Build complet : $(NAME)\033[0m"

$(NAME): $(OBJ) $(FT_PRINTF_LIB) $(LIBFT_LIB) $(HEADERS)
	@echo "\033[34m🔨 Compilation de $(NAME)...\033[0m"
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(FT_PRINTF_FLAGS) $(MLX_FLAGS)

bonus: $(MLX_LIB) $(FT_PRINTF_LIB) $(LIBFT_LIB) $(NAME_BONUS)
	@echo "\033[35m🎉 Compilation du bonus : $(NAME_BONUS)\033[0m"

$(NAME_BONUS): $(OBJ_BONUS) $(FT_PRINTF_LIB) $(LIBFT_LIB) $(HEADERS_BONUS)
	@echo "\033[34m🔨 Compilation de $(NAME_BONUS)...\033[0m"
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME_BONUS) $(FT_PRINTF_FLAGS) $(MLX_FLAGS)

# 🛠️ Compilation des fichiers source
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR) $(DEP_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(FT_PRINTF) -I$(MLX_DIR) -c $< -o $@ -MF $(DEP_DIR)/$*.d

$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c $(HEADERS_BONUS)
	@mkdir -p $(OBJ_BONUS_DIR) $(DEP_BONUS_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(FT_PRINTF) -I$(MLX_DIR) -c $< -o $@ -MF $(DEP_BONUS_DIR)/$*.d

# 🔄 Recompiler si des fichiers sont modifiés
$(FT_PRINTF_LIB): $(wildcard $(FT_PRINTF)/*.c)
	@$(MAKE) --no-print-directory -C $(FT_PRINTF)

$(LIBFT_LIB): $(wildcard $(LIBFT_DIR)/*.c)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

$(MLX_LIB):
	@$(MAKE) --no-print-directory -C $(MLX_DIR)

# 🧹 Nettoyage
clean:
	@echo "\033[33m🗑️ Nettoyage des fichiers objets...\033[0m"
	@$(MAKE) --no-print-directory -C $(FT_PRINTF) clean
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@$(MAKE) --no-print-directory -C $(MLX_DIR) clean
	rm -rf $(OBJ_DIR) $(OBJ_BONUS_DIR) $(DEP_DIR) $(DEP_BONUS_DIR)

fclean: clean
	@echo "\033[31m🗑️ Suppression des exécutables...\033[0m"
	rm -f $(NAME) $(NAME_BONUS)
	@$(MAKE) --no-print-directory -C $(FT_PRINTF) fclean
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

re: fclean all

# 📎 Inclusion des dépendances
-include $(DEP)
-include $(DEP_BONUS)

.PHONY: all bonus clean fclean re