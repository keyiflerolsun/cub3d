/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 01:46:14 by osancak           #+#    #+#             */
/*   Updated: 2025/12/20 15:58:11 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 1920
# define HEIGHT 1080
# define BLOCK_SIZE 64

# define P 3.1415926535

# include "ft_printf.h"
# include "get_next_line.h"
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

#include <math.h>
#include <string.h> // sil aq


# define VALID_MAP_CHARS "01NSEW \n"

typedef struct s_img
{
	void			*img;
	void			*addr;
	int				bpp;
	int				row_length;
	int				endian;
	int				width;
	int				height;
}					t_img;

typedef struct s_draw
{
	t_img			*tex;
	int				tex_x;
	int				tex_y;
	int				start;
	int				end;
	float			wall_h;
	float			step;
	float			tex_pos;
	float			angle;
}					t_draw;

typedef struct s_ray
{
	float			delta_x;
	float			delta_y;
	float			side_x;
	float			side_y;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				side;
}					t_ray;

typedef struct s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct s_texture
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
}					t_texture;

typedef struct s_player
{
	unsigned int	row;
	unsigned int	column;
	char			direction;

	float			x;
	float			y;
	float			rotation;

	int				key_up;
	int				key_down;
	int				key_left;
	int				key_right;

	int				rotate_left;
	int				rotate_right;

	int				speed;
	float			angle_speed;

}					t_player;

typedef struct s_map
{
	char			**full;
	unsigned int	rows;
	unsigned int	columns;
	unsigned int	players;
}					t_map;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*data;
	int				bpp;
	int				size_line;
	int				endian;
	t_map			map;
	t_player		player;
	t_texture		texture;
	t_color			floor;
	t_color			ceiling;
	t_img			north_wall;
	t_img			south_wall;
	t_img			east_wall;
	t_img			west_wall;
}					t_game;

// utils
int					game_close(t_game *game);

#endif
