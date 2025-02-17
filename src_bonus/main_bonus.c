/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:20:47 by pledieu           #+#    #+#             */
/*   Updated: 2025/02/10 09:31:08 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	is_valid_extension(const char *filename)
{
	size_t	len;

	len = 0;
	while (filename[len])
		len++;
	if (len < 4)
		return (0);
	if (filename[len - 4] == '.'
		&& filename[len - 3] == 'b'
		&& filename[len - 2] == 'e'
		&& filename[len - 1] == 'r')
		return (1);
	return (0);
}

/**
 * @brief Entry point of the program, initializes and runs the game.
 * 
 * This function checks command-line arguments, validates the map file 
 * extension, initializes the game, and properly cleans up resources 
 * before exiting.
 * 
 * @param ac Number of command-line arguments.
 * @param av Array of command-line argument strings.
 * @return int Returns 0 on success, 1 on error.
 */
int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
	{
		ft_printf("Error \n	->Usage: %s <fichier_map.ber>\n", av[0]);
		return (1);
	}
	if (!is_valid_extension(av[1]))
	{
		ft_printf("Error\n	->Le fichier doit avoir l'extension '.ber'\n");
		return (1);
	}
	game.moves = 0;
	init_game(&game, av[1]);
	close_game(&game);
	return (0);
}
