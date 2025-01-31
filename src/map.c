/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 08:51:34 by pledieu           #+#    #+#             */
/*   Updated: 2025/01/31 07:08:35 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static char	*read_map_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	if (line && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	return (line);
}

static void	check_map_validity(t_game *game, char *line, int i)
{
	if (i == 0)
		game->map_width = ft_strlen(line);
	if ((int)ft_strlen(line) != game->map_width)
		error_exit("Erreur : La carte n'est pas rectangulaire !");
}

void	load_map(const char *filename, t_game *game)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Erreur : Impossible d'ouvrir la carte");
	game->map = malloc(sizeof(char *) * 100);
	if (!game->map)
		error_exit("Erreur : Allocation mémoire échouée");
	while (1)
	{
		line = read_map_line(fd);
		if (!line)
			break ;
		check_map_validity(game, line, i);
		game->map[i++] = line;
	}
	game->map[i] = NULL;
	game->map_height = i;
	close(fd);
	set_enemies(game);
	ft_printf("✅ DEBUG: Carte chargée avec succès, hauteur: %d, largeur: %d\n",
		game->map_height, game->map_width);
}
