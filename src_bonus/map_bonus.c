/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 08:51:34 by pledieu           #+#    #+#             */
/*   Updated: 2025/02/05 07:56:42 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

static void	free_map_partial(char **map, int last_index)
{
	while (last_index >= 0)
		free(map[last_index--]);
	free(map);
	map = NULL;
}

static char	*read_map_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (line && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	return (line);
}

static void	check_map_validity(t_game *game, char *line, int i)
{
	if (i == 0)
		game->map_width = ft_strlen(line);
	if ((int)ft_strlen(line) != game->map_width)
	{
		game->map_height = 0;
		free(line);
		free_map_partial(game->map, i - 1);
		game->map = NULL;
		free_invalid_map(game);
	}
}

static void	process_map(int fd, t_game *game)
{
	char	*line;
	int		i;

	i = 0;
	line = read_map_line(fd);
	while (line)
	{
		check_map_validity(game, line, i);
		game->map[i++] = line;
		line = read_map_line(fd);
	}
	game->map[i] = NULL;
	game->map_height = i;
	if (game->map_height == 0)
	{
		free_map_partial(game->map, i - 1);
		game->map = NULL;
		free_invalid_map(game);
	}
	set_enemies(game);
	ft_printf("Carte chargée avec succès, hauteur: %d, largeur: %d\n",
		game->map_height, game->map_width);
}

void	load_map(const char *filename, t_game *game)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		free_invalid_map(game);
	game->map = malloc(sizeof(char *) * 100);
	if (!game->map)
	{
		close(fd);
		error_exit("Erreur : Allocation mémoire échouée");
	}
	process_map(fd, game);
	close(fd);
}
