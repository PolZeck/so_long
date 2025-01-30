/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:16:03 by pledieu           #+#    #+#             */
/*   Updated: 2025/01/30 18:56:03 by pledieu          ###   ########lyon.fr   */
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

# define T_SIZE 32


typedef struct s_enemy
{
    int x;
    int y;
	char under_enemy;
    struct s_enemy *next;
} t_enemy;

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
    void    *img_enemy;
	void	*img_exit_closed;
	t_enemy *enemies;
} t_game;

typedef struct s_counts
{
    int player;
    int exit;
    int collectible;
} t_counts;

typedef struct s_position
{
    int x;
    int y;
} t_position;


// Prototypes des fonctions
void	load_map(const char *filename, t_game *game);
void	validate_map(t_game *game);
void	free_map(t_game *game);
void	error_exit(const char *message);
void	init_game(t_game *game, char *map_file);
void	render_map(t_game *game);
int		handle_movement(int keycode, void *param);
void	load_textures(t_game *game);
void	destroy_textures(t_game *game);
void	set_player_position(t_game *game);
int		count_collectibles(t_game *game);
void	check_map_walls(t_game *game);
int		close_game(t_game *game);
void	check_valid_path(t_game *game);
void	check_map_walls(t_game *game);
void	free_map_copy(char **map, int height);
void	move_on_window(t_game *game);
void	set_enemies(t_game *game);
void	add_enemy(t_game *game, int x, int y);
void	free_enemies(t_game *game);

void free_map_copy(char **map, int height);
void move_enemies(t_game *game);

#endif
