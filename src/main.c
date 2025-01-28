/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:20:47 by pledieu           #+#    #+#             */
/*   Updated: 2025/01/28 13:08:44 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int main(int argc, char **argv)
{
    t_game game;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <fichier_map.ber>\n", argv[0]);
        return (1);
    }

    game.moves = 0;
    init_game(&game, argv[1]);

    return (0);
}
