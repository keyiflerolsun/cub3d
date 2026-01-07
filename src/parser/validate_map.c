/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 10:38:52 by osancak           #+#    #+#             */
/*   Updated: 2026/01/06 18:14:19 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	init_player(t_player *player, t_map *map, int row, int column)
{
	map->players += 1;
	player->row = row;
	player->column = column;
	player->direction = map->full[row][column];
}

static int	is_player_char(char c)
{
	return (ft_strchr("NSWE", c) != NULL);
}

int	is_valid_map_char(char c)
{
	return (ft_strchr("01NSWE \t", c) != NULL);
}

void	validate_map(t_game *game)
{
	int	row;
	int	col;

	game->map.rows = 0;
	game->map.columns = ft_strlen((game->map.full)[0]);
	game->map.players = 0;
	row = -1;
	while ((game->map.full)[++row])
	{
		game->map.rows += 1;
		col = -1;
		while ((game->map.full)[row][++col])
		{
			if (!is_valid_map_char(game->map.full[row][col]))
				err_exit("Map contains invalid character", game);
			if (is_player_char(game->map.full[row][col]))
				init_player(&game->player, &game->map, row, col);
		}
	}
	if (game->map.players != 1)
		err_exit("Map must have exactly 1 player (N, S, E, or W)", game);
	validate_textures(game);
	if (!fill_check(game, &game->player))
		err_exit("Map is not closed or player cannot reach all areas", game);
}
