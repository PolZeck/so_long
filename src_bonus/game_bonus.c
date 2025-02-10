/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 08:51:47 by pledieu           #+#    #+#             */
/*   Updated: 2025/02/10 13:02:23 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

/**
 * @brief Initializes the game, loads the map,
 * sets up the window, and starts the game loop.
 * 
 * This function performs the initialization of the game structure, including
 * setting up the graphics library (MiniLibX), loading the map file, validating 
 * the map, setting the player position, creating the game window,
 * loading textures, and rendering the map. It also sets up event handling
 * for player movement and closing the game window.
 * 
 * @param game Pointer to the game structure to initialize.
 * @param map_file Path to the map file to load.
 */
void	init_game(t_game *game, char *map_file)
{
	init_struct_game(game);
	game->mlx = mlx_init();
	if (!game->mlx)
		error_exit("Erreur : Impossible d'initialiser MiniLibX");
	load_map(map_file, game);
	validate_map(game);
	set_player_position(game);
	check_size_map_on_window(game);
	if (!check_size_map_on_window(game))
		close_game(game);
	game->win = mlx_new_window(game->mlx, game->map_width * T_SIZE,
			game->map_height * T_SIZE, "so_long");
	if (!game->win)
		error_exit("Erreur : Impossible de créer la fenêtre");
	load_textures(game);
	render_map(game);
	mlx_key_hook(game->win, handle_movement, game);
	mlx_hook(game->win, 17, 0, close_game, game);
	mlx_loop_hook(game->mlx, animate_collectibles, game);
	mlx_loop(game->mlx);
}

int	close_game(t_game *game)
{
	ft_printf("👋 Fermeture du jeu !\n");
	destroy_textures(game);
	free_enemies(game);
	free_map(game);
	exit(0);
	return (0);
}

int	check_size_map_on_window(t_game *game)
{
	int	screen_width;
	int	screen_height;

	mlx_get_screen_size(game->mlx, &screen_width, &screen_height);
	if (game->map_width * T_SIZE > screen_width
		|| game->map_height * T_SIZE > screen_height - 64)
	{
		ft_printf("Erreur : La carte est trop grande pour l'écran.\n");
		ft_printf("Taille de l'écran : %d x %d\n", screen_width, screen_height);
		return (0);
	}
	return (1);
}

void	init_struct_game(t_game *game)
{
	int	i;

	i = 0;
	game->mlx = NULL;
	game->win = NULL;
	game->map = NULL;
	game->enemies = NULL;
	game->map_width = 0;
	game->map_height = 0;
	game->player_x = 0;
	game->player_y = 0;
	game->moves = 0;
	game->player_dir = 0;
	game->img_wall = NULL;
	game->img_exit = NULL;
	game->img_exit_closed = NULL;
	game->img_floor = NULL;
	while (i < 4)
	{
		if (i <= 1)
			game->img_collectible[i] = NULL;
		game->img_player[i] = NULL;
		i++;
	}
}
