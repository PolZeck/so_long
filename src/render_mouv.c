/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mouv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:33:48 by pledieu           #+#    #+#             */
/*   Updated: 2025/02/04 13:03:18 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int update_position(int keycode, t_game *game, int *new_x, int *new_y)
{
    if (keycode == 'w' || keycode == 65362) {
        (*new_y)--;
        game->player_dir = 3;  // Haut
    }
    else if (keycode == 's' || keycode == 65364) {
        (*new_y)++;
        game->player_dir = 0;  // Bas
    }
    else if (keycode == 'a' || keycode == 65361) {
        (*new_x)--;
        game->player_dir = 1;  // Gauche
    }
    else if (keycode == 'd' || keycode == 65363) {
        (*new_x)++;
        game->player_dir = 2;  // Droite
    }
    else if (keycode == 65307) {
        destroy_textures(game);
        free_map(game);
        free_enemies(game);
        exit(0);
    }
    else
        return (0);
    return (1);
}


static int	check_collisions(t_game *game, int new_x, int new_y)
{
	if (new_x < 0 || new_x >= game->map_width
		|| new_y < 0 || new_y >= game->map_height)
	{
		ft_printf("⛔ Mouvement hors limites !\n");
		return (0);
	}
	if (game->map[new_y][new_x] == '1')
	{
		ft_printf("⛔ Collision avec un mur !\n");
		return (0);
	}
	if (game->map[new_y][new_x] == 'M')
	{
		ft_printf("💀 GAME OVER ! Vous avez été attrapé par un ennemi !\n");
		free_enemies(game);
		destroy_textures(game);
		free_map(game);
		exit(1);
	}
	return (1);
}

static void	update_exit_status(t_game *game)
{
	int	h;
	int	w;

	if (count_collectibles(game) == 0)
	{
		if (game->img_exit)
			mlx_destroy_image(game->mlx, game->img_exit);
		game->img_exit = mlx_xpm_file_to_image(game->mlx,
				"assets/exit.xpm", &w, &h);
	}
}

static void	handle_exit_collectibles(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == 'C')
	{
		ft_printf("🍎 Collectible ramassé !\n");
		game->map[new_y][new_x] = '0';
	}
	update_exit_status(game);
	if (game->map[new_y][new_x] == 'E')
	{
		if (count_collectibles(game) > 0)
		{
			ft_printf("⛔ Il reste encore des collectibles ! (%d restants)\n",
				count_collectibles(game));
			return ;
		}
		ft_printf("🎉 Victoire ! Vous avez collecté tous les objets ! ");
		ft_printf("Sortie atteinte en %d déplacements!\n", game->moves + 1);
		free_enemies(game);
		destroy_textures(game);
		free_map(game);
		exit(0);
	}
}

int	handle_movement(int keycode, void *param)
{
	t_game	*game;
	int		new_x;
	int		new_y;
	int		moved;

	game = (t_game *)param;
	new_x = game->player_x;
	new_y = game->player_y;
	moved = update_position(keycode, game, &new_x, &new_y);
	if (!moved || !check_collisions(game, new_x, new_y))
		return (0);
	handle_exit_collectibles(game, new_x, new_y);
	game->map[game->player_y][game->player_x] = '0';
	game->player_x = new_x;
	game->player_y = new_y;
	game->map[game->player_y][game->player_x] = 'P';
	if (moved)
	{
		game->moves++;
		ft_printf("\033[H\033[JJoueur déplacé à (%d, %d), Mouvements: %d\n",
			game->player_x, game->player_y, game->moves);
		move_enemies(game);
	}
	render_map(game);
	return (0);
}
