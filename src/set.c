/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:33:11 by pledieu           #+#    #+#             */
/*   Updated: 2025/02/10 11:54:33 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	check_textures(t_game *game)
{
	if (!game->img_wall || !game->img_player[0]
		|| !game->img_collectible || !game->img_exit
		|| !game->img_floor || !game->img_player[1]
		|| !game->img_player[2] || !game->img_player[3])
		error_exit("Error\nImpossible de charger une ou plusieurs textures.");
}

static void	load_player_textures(t_game *game, int *w, int *h)
{
	game->img_player[0] = mlx_xpm_file_to_image(game->mlx,
			"assets/player.xpm", w, h);
	game->img_player[1] = mlx_xpm_file_to_image(game->mlx,
			"assets/player_l.xpm", w, h);
	game->img_player[2] = mlx_xpm_file_to_image(game->mlx,
			"assets/player_r.xpm", w, h);
	game->img_player[3] = mlx_xpm_file_to_image(game->mlx,
			"assets/player_b.xpm", w, h);
}

void	load_textures(t_game *game)
{
	int	w;
	int	h;

	w = 0;
	h = 0;
	game->img_wall = mlx_xpm_file_to_image(game->mlx,
			"assets/wall.xpm", &w, &h);
	load_player_textures(game, &w, &h);
	game->img_exit = mlx_xpm_file_to_image(game->mlx,
			"assets/exit_closed.xpm", &w, &h);
	game->img_floor = mlx_xpm_file_to_image(game->mlx,
			"assets/floor.xpm", &w, &h);
	game->img_collectible = mlx_xpm_file_to_image(game->mlx,
			"assets/collectible.xpm", &w, &h);
	check_textures(game);
}

void	set_player_position(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
				ft_printf("Joueur trouvé à -> X: %d, Y: %d\n", x, y);
				return ;
			}
			x++;
		}
		y++;
	}
	error_exit("Error\n-> Joueur non trouvé dans la carte !");
}
