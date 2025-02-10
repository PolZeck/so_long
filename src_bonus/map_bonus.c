/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 08:51:34 by pledieu           #+#    #+#             */
/*   Updated: 2025/02/10 11:17:23 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

/**
 * @brief Frees a partially loaded map and all
 * its elements up to the specified index.
 * 
 * This function iterates through the map array from the given index and frees
 * each allocated string, then frees the map array itself. It also sets the map
 * pointer to NULL after freeing.
 * 
 * @param map The map array to free.
 * @param last_index The index up to which to free the map elements.
 */
static void	free_map_partial(char **map, int last_index)
{
	while (last_index >= 0)
		free(map[last_index--]);
	free(map);
	map = NULL;
}

/**
 * @brief Reads a single line from the map file.
 * 
 * This function reads a line from the file descriptor
 * using `get_next_line` and removes the newline character
 * at the end, if present, before returning the line.
 * 
 * @param fd The file descriptor from which to read the line.
 * @return The line read from the file, or NULL if end of file is reached.
 */
static char	*read_map_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (line && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	return (line);
}

/**
 * @brief Checks the validity of the map's current
 * line and updates map properties.
 * 
 * This function checks if the current line of the map is valid by comparing its
 * length with the map's width. If the line's length doesn't match the expected
 * width, the map is considered invalid, and the function frees the map memory
 * and exits the program.
 * 
 * @param game Pointer to the game structure.
 * @param line The line from the map to check.
 * @param i The index of the current line being processed.
 */
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

/**
 * @brief Processes and loads the map from the file into the game structure.
 * 
 * This function reads each line of the map file,
 * checks the validity of each line,
 * and stores the lines in the `map` array.
 * It also sets up the enemies and prints
 * the map's dimensions upon successful loading.
 * 
 * @param fd The file descriptor of the map file.
 * @param game Pointer to the game structure where the map will be stored.
 */
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

/**
 * @brief Loads the map from the specified file into the game structure.
 * 
 * This function opens the given map file, allocates memory for the map array,
 * and calls `process_map` to load the map lines. If memory allocation fails or
 * the file cannot be opened, it calls `free_invalid_map`
 * to clean up and terminate the program.
 * 
 * @param filename The path to the map file.
 * @param game Pointer to the game structure where the map will be stored.
 */
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
