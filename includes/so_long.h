/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:16:03 by pledieu           #+#    #+#             */
/*   Updated: 2025/01/28 11:04:59 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../super_libft/super_libft.h"
# include "../super_libft/libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>

# define TILE_SIZE 32

typedef struct s_game {
    void    *mlx;
    void    *win;
    char    **map;
    int     map_width;
    int     map_height;
    int     player_x;
    int     player_y;
    int     moves;

    // Textures
    void    *img_wall;
    void    *img_player;
    void    *img_collectible;
    void    *img_exit;
    void    *img_floor;
} t_game;

// Prototypes des fonctions
void    load_map(const char *filename, t_game *game);
void    validate_map(t_game *game);
void    free_map(t_game *game);
void    error_exit(const char *message);
void    init_game(t_game *game, char *map_file);
void    render_map(t_game *game);
int handle_movement(int keycode, void *param);
void    load_textures(t_game *game);
void    destroy_textures(t_game *game);
void start_game(t_game *game);
int key_press_wrapper(int keycode, void *param);
void set_player_position(t_game *game);



#endif
