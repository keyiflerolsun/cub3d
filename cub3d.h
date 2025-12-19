/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 01:46:14 by osancak           #+#    #+#             */
/*   Updated: 2025/10/28 01:46:14 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <X11/X.h>
# include <X11/keysym.h>

# define VALID_MAP_CHARS "01NSEW \n"

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}		t_color;

typedef struct s_texture
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}		t_texture;

typedef struct s_player
{
	unsigned int	row;
	unsigned int	column;
	char			direction;
}		t_player;

typedef struct s_map
{
	char			**full;
	unsigned int	rows;
	unsigned int	columns;
	unsigned int	players;
}		t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_player	player;
	t_texture	texture;
	t_color		floor;
	t_color		ceiling;
}		t_game;

// utils
int		game_close(t_game *game);

#endif
