/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:16:03 by pledieu           #+#    #+#             */
/*   Updated: 2025/01/23 14:38:26 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../super_libft/super_libft.h"
# include "../super_libft/libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <fcntl.h>


typedef struct s_game {
    void    *mlx;       // Pointeur pour la connexion MiniLibX
    void    *win;       // Pointeur pour la fenêtre
    void    *img;       // Pointeur pour l'image (sprite)
    int     img_width;  // Largeur de l'image
    int     img_height; // Hauteur de l'image
}   t_game;

#endif