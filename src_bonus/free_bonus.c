/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:26:44 by pledieu           #+#    #+#             */
/*   Updated: 2025/02/05 15:13:23 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	free_map_copy(char **map, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_invalid_map(t_game *game)
{
	game->win = NULL;
	load_textures(game);
	destroy_textures(game);
	free_map(game);
	free_enemies(game);
	error_exit("Error\n	-> Incorrect Map !");
}

void	free_map(t_game *game)
{
	int	i;

	i = 0;
	if (!game->map)
		return ;
	while (i < game->map_height)
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	game->map = NULL;
}

void	free_enemies(t_game *game)
{
	t_enemy	*temp;

	while (game->enemies)
	{
		temp = game->enemies;
		game->enemies = game->enemies->next;
		free(temp);
	}
}
