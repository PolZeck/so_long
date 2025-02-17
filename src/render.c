/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:32:28 by pledieu           #+#    #+#             */
/*   Updated: 2025/02/05 08:19:00 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	render_special_tiles(t_game *game, char tile, int x, int y)
{
	if (tile == 'P')
	{
		mlx_put_image_to_window(game->mlx, game->win,
			game->img_player[game->player_dir], x * T_SIZE, y * T_SIZE);
	}
	else if (tile == 'C')
	{
		mlx_put_image_to_window(game->mlx, game->win,
			game->img_collectible, x * T_SIZE, y * T_SIZE);
	}
}

static void	render_tile(t_game *game, char tile, int x, int y)
{
	void	*img;

	img = NULL;
	if (tile == '1')
		img = game->img_wall;
	else if (tile == '0')
		img = game->img_floor;
	else if (tile == 'E')
		img = game->img_exit;
	if (img)
		mlx_put_image_to_window(game->mlx, game->win, img,
			x * T_SIZE, y * T_SIZE);
	else
		render_special_tiles(game, tile, x, y);
}

void	render_map(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			render_tile(game, game->map[y][x], x, y);
			x++;
		}
		y++;
	}
}
