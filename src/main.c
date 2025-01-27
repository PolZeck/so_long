/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:20:47 by pledieu           #+#    #+#             */
/*   Updated: 2025/01/27 13:09:43 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int handle_keypress(int keycode, t_game *game)
{
    if (keycode == 65307) // Touche "Echap" sur Linux
    {
        mlx_destroy_window(game->mlx, game->win); // Détruire la fenêtre
        exit(0); // Quitter le programme
    }
    return (0);
}


int main(void)
{
     t_game game;

    // Initialisation de MiniLibX et création de la fenêtre
    game.mlx = mlx_init();
    if (!game.mlx)
        return (fprintf(stderr, "Erreur : Impossible d'initialiser MiniLibX\n"), 1);
    
    game.win = mlx_new_window(game.mlx, 800, 600, "so_long");
    if (!game.win)
        return (fprintf(stderr, "Erreur : Impossible de créer la fenêtre\n"), 1);

    // Chargement d'une image au format XPM
    game.img = mlx_xpm_file_to_image(game.mlx, "assets/sacha.xpm", &game.img_width, &game.img_height);
    if (!game.img)
        return (fprintf(stderr, "Erreur : Impossible de charger l'image\n"), 1);

    // Affichage de l'image dans la fenêtre à une position donnée (x=100, y=100)
    mlx_put_image_to_window(game.mlx, game.win, game.img, 100, 100);

    // Gestion des événements clavier
    mlx_key_hook(game.win, handle_keypress, &game);

    // Boucle principale pour garder la fenêtre ouverte et gérer les événements
    mlx_loop(game.mlx);

    return (0);
}