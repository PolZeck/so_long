/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:32:28 by pledieu           #+#    #+#             */
/*   Updated: 2025/02/03 15:02:45 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int animate_collectibles(t_game *game)
{
    static int blink = 0;
    static int frame_count = 0; // ✅ Compteur pour ralentir l'animation
    int x, y;

    frame_count++;
    if (frame_count >= 1000)  // ✅ Change d'image toutes les 20 frames
    {
        blink = !blink;      // Alterne entre 0 et 1
        frame_count = 0;     // Réinitialise le compteur
    }

    for (y = 0; y < game->map_height; y++)
    {
        for (x = 0; x < game->map_width; x++)
        {
            if (game->map[y][x] == 'C')
                mlx_put_image_to_window(game->mlx, game->win, game->img_collectible[blink], x * T_SIZE, y * T_SIZE);
        }
    }
    return (0);
}



static void	render_tile(t_game *game, char tile, int x, int y)
{
	void	*img;

	img = NULL;
	if (tile == '1')
		img = game->img_wall;
	else if (tile == '0')
		img = game->img_floor;
	else if (tile == 'P')
		img = game->img_player;
	else if (tile == 'C')
	{
		mlx_put_image_to_window(game->mlx, game->win, game->img_collectible[0], x * T_SIZE, y * T_SIZE);
		return;
	}

	else if (tile == 'E')
		img = game->img_exit;
	else if (tile == 'M')
		img = game->img_enemy;
	if (img)
		mlx_put_image_to_window(game->mlx, game->win, img,
			x * T_SIZE, y * T_SIZE);
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
	move_on_window(game);
}

void	move_on_window(t_game *game)
{
	int		rect_width;
	int		rect_height;
	int		i;
	char	*move_count;
	int		j;

	rect_width = 140;
	rect_height = 20;
	i = 5;
	while (i++ < 5 + rect_height)
	{
		j = 5;
		while (j++ < 5 + rect_width)
			mlx_pixel_put(game->mlx, game->win, j, i, 0x000000);
	}
	move_count = ft_itoa(game->moves);
	mlx_string_put(game->mlx, game->win, 15, 20, 0xFFD700, "Mouvements : ");
	mlx_string_put(game->mlx, game->win, 120, 20, 0xFFFFFF, move_count);
	free(move_count);
	ft_printf("Nombre de mouvements affiché sur la fenêtre : %d\n",
		game->moves);
}
