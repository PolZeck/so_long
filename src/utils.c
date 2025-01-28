/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 08:52:03 by pledieu           #+#    #+#             */
/*   Updated: 2025/01/28 09:34:58 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void error_exit(const char *message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void free_map(t_game *game) {
    int i = 0;
    while (game->map[i]) free(game->map[i++]);
    free(game->map);
}
