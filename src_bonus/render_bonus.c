/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:32:28 by pledieu           #+#    #+#             */
/*   Updated: 2025/02/10 11:21:09 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

/**
 * @brief Animates collectibles by blinking them on and off at each frame.
 * 
 * This function handles the animation of collectibles
 * on the game map by alternating the visibility of the
 * collectibles at a regular frame interval. It toggles the `blink` 
 * state every 8000 frames, which is used to alternate between
 * two collectible images to create the blinking effect.
 * The function iterates over the entire map, checking for 
 * collectibles ('C') and displaying the appropriate image
 * based on the current `blink` state.
 * 
 * @param game Pointer to the game structure containing map and images.
 * 
 * @return 0 Always returns 0 (function signature for mlx loop).
 */
int	animate_collectibles(t_game *game)
{
	static int	blink = 0;
	static int	frame_count = 0;
	int			x;
	int			y;

	frame_count++;
	if (frame_count >= 8000)
	{
		blink = !blink;
		frame_count = 0;
	}
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'C')
				mlx_put_image_to_window(game->mlx, game->win,
					game->img_collectible[blink], x * T_SIZE, y * T_SIZE);
			x++;
		}
		y++;
	}
	return (0);
}

/**
 * @brief Renders special tiles (player or collectible) on the game map.
 * 
 * This function checks the tile type at the given
 * position and renders the appropriate image for special
 * tiles such as the player ('P') and collectibles ('C').
 * For the player, it uses the player's current direction
 * to select the correct sprite. For collectibles, 
 * it renders a standard collectible image.
 * 
 * @param game Pointer to the game structure containing map and images.
 * @param tile The type of tile ('P' for player, 'C' for collectible).
 * @param x The x-coordinate of the tile on the map.
 * @param y The y-coordinate of the tile on the map.
 */
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
			game->img_collectible[0], x * T_SIZE, y * T_SIZE);
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
	else if (tile == 'M')
		img = game->img_enemy;
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
	move_on_window(game);
}

/**
 * @brief Displays the move count on the game window.
 * 
 * This function draws a rectangular background on the game window and displays
 * the current move count of the player on it. The move count is rendered in 
 * gold text with a white number beside it. It also prints the move count to the 
 * terminal for debugging purposes.
 * 
 * @param game Pointer to the game structure containing the number of moves.
 */
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
