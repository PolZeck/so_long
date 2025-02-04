/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:34:24 by pledieu           #+#    #+#             */
/*   Updated: 2025/02/04 17:37:38 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	destroy_player_images(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->img_player[i])
			mlx_destroy_image(game->mlx, game->img_player[i]);
		i++;
	}
}

static void	destroy_collectibles(t_game *game)
{
	if (game->img_collectible[0])
		mlx_destroy_image(game->mlx, game->img_collectible[0]);
	if (game->img_collectible[1])
		mlx_destroy_image(game->mlx, game->img_collectible[1]);
}

void	destroy_textures(t_game *game)
{
	if (!game)
		return ;
	if (game->img_wall)
		mlx_destroy_image(game->mlx, game->img_wall);
	destroy_player_images(game);
	destroy_collectibles(game);
	if (game->img_exit)
		mlx_destroy_image(game->mlx, game->img_exit);
	if (game->img_floor)
		mlx_destroy_image(game->mlx, game->img_floor);
	if (game->img_enemy)
		mlx_destroy_image(game->mlx, game->img_enemy);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}
