/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:32:28 by pledieu           #+#    #+#             */
/*   Updated: 2025/01/29 14:04:36 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

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
			if (game->map[y][x] == '1')
				mlx_put_image_to_window(game->mlx, game->win, game->img_wall, x * T_SIZE, y * T_SIZE);
			else if (game->map[y][x] == '0')
				mlx_put_image_to_window(game->mlx, game->win, game->img_floor, x * T_SIZE, y * T_SIZE);
			else if (game->map[y][x] == 'P')
				mlx_put_image_to_window(game->mlx, game->win, game->img_player, x * T_SIZE, y * T_SIZE);
			else if (game->map[y][x] == 'C')
				mlx_put_image_to_window(game->mlx, game->win, game->img_collectible, x * T_SIZE, y * T_SIZE);
			else if (game->map[y][x] == 'E')
				mlx_put_image_to_window(game->mlx, game->win, game->img_exit, x * T_SIZE, y * T_SIZE);
			x++;
		}
		y++;
	}
	move_on_window(game);
}

void	move_on_window(t_game *game)
{
	int rect_width; 
	int rect_height;
	int color;
	int	i;
	char *move_count;
	int	j;

	rect_width = 140;
	rect_height = 20;
	color = 0x000000;
	i = 5;
	while (i++ < 5 + rect_height)
	{
		j = 5;
		while (j++ < 5 + rect_width)
			mlx_pixel_put(game->mlx, game->win, j, i, color);
	}
	move_count = ft_itoa(game->moves);
	mlx_string_put(game->mlx, game->win, 15, 20, 0xFFD700, "Mouvements : ");
	mlx_string_put(game->mlx, game->win, 120, 20, 0xFFFFFF, move_count);
	free(move_count);
	ft_printf("DEBUG: Nombre de mouvements affiché sur la fenêtre : %d\n", game->moves);
}
