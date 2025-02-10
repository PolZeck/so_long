/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:16:03 by pledieu           #+#    #+#             */
/*   Updated: 2025/02/10 13:23:02 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../ft_printf/ft_printf.h"
# include "../ft_printf/libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>

# define T_SIZE 32

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	int		moves;
	int		player_dir;
	void	*img_wall;
	void	*img_player[4];
	void	*img_collectible;
	void	*img_exit;
	void	*img_floor;
	void	*img_exit_closed;
}				t_game;

typedef struct s_counts
{
	int	player;
	int	exit;
	int	collectible;
}				t_counts;

typedef struct s_position
{
	int	x;
	int	y;
}				t_position;

int		close_game(t_game *game);
int		handle_movement(int keycode, void *param);
int		count_collectibles(t_game *game);
void	load_map(const char *filename, t_game *game);
void	validate_map(t_game *game);
void	free_map(t_game *game);
void	error_exit(const char *message);
void	init_game(t_game *game, char *map_file);
void	render_map(t_game *game);
void	load_textures(t_game *game);
void	destroy_textures(t_game *game);
void	set_player_position(t_game *game);
void	check_map_walls(t_game *game);
void	check_valid_path(t_game *game);
void	check_map_walls(t_game *game);
void	free_map_copy(char **map, int height);
void	free_invalid_map(t_game *game);
int		check_size_map_on_window(t_game *game);
void	init_struct_game(t_game *game);

#endif
