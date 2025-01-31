/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemies.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:51:41 by pledieu           #+#    #+#             */
/*   Updated: 2025/01/31 07:39:46 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	handle_enemy_movement(t_game *game, t_enemy *enemy,
	int new_x, int new_y)
{
	if (new_x == game->player_x && new_y == game->player_y)
	{
		ft_printf("💀 GAME OVER ! Un ennemi vous a attrapé !\n");
		destroy_textures(game);
		free_map(game);
		free_enemies(game);
		exit(1);
	}
	if (game->map[new_y][new_x] == '0' || game->map[new_y][new_x] == 'C')
	{
		if (enemy->under_enemy == 'C')
			game->map[enemy->y][enemy->x] = 'C';
		else
			game->map[enemy->y][enemy->x] = '0';
		if (game->map[new_y][new_x] == 'C')
			enemy->under_enemy = 'C';
		else
			enemy->under_enemy = '0';
		enemy->x = new_x;
		enemy->y = new_y;
		game->map[new_y][new_x] = 'M';
	}
}

static void	move_enemy(t_game *game, t_enemy *enemy)
{
	int	new_x;
	int	new_y;

	new_x = enemy->x;
	new_y = enemy->y;
	determine_new_position(game, enemy, &new_x, &new_y);
	handle_enemy_movement(game, enemy, new_x, new_y);
}

void	move_enemies(t_game *game)
{
	t_enemy	*enemy;

	enemy = game->enemies;
	while (enemy)
	{
		move_enemy(game, enemy);
		enemy = enemy->next;
	}
}

void	add_enemy(t_game *game, int x, int y)
{
	t_enemy	*new_enemy;

	new_enemy = malloc(sizeof(t_enemy));
	if (!new_enemy)
		error_exit("Erreur : Allocation mémoire pour un ennemi");
	new_enemy->x = x;
	new_enemy->y = y;
	if (game->map[y][x] == 'C')
		new_enemy->under_enemy = 'C';
	else
		new_enemy->under_enemy = '0';
	new_enemy->next = game->enemies;
	game->enemies = new_enemy;
}

void	set_enemies(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'M')
			{
				ft_printf("M détecté dans la map à (x=%d, y=%d)\n", x, y);
				add_enemy(game, x, y);
			}
			x++;
		}
		y++;
	}
}
