/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:45:22 by osancak           #+#    #+#             */
/*   Updated: 2026/01/06 18:14:19 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	**duplicate_map(t_game *game)
{
	char	**res;
	int		r;
	size_t	c;

	res = ft_calloc(game->map.rows + 1, sizeof(char *));
	if (!res)
		return (NULL);
	r = -1;
	while (game->map.full[++r])
	{
		res[r] = malloc(game->map.columns + 1);
		if (!res[r])
			return (NULL);
		c = 0;
		while (c < game->map.columns)
		{
			if (c < ft_strlen(game->map.full[r]))
				res[r][c] = game->map.full[r][c];
			else
				res[r][c] = ' ';
			c++;
		}
		res[r][c] = '\0';
	}
	return (res);
}

static int	fill_map(t_game *g, char **map, int r, int c)
{
	if (r < 0 || r >= (int)g->map.rows || c < 0 || c >= (int)g->map.columns)
		return (0);
	if (map[r][c] == '1' || map[r][c] == '*')
		return (1);
	if (map[r][c] == ' ')
		return (0);
	map[r][c] = '*';
	if (!fill_map(g, map, r + 1, c))
		return (0);
	if (!fill_map(g, map, r - 1, c))
		return (0);
	if (!fill_map(g, map, r, c + 1))
		return (0);
	if (!fill_map(g, map, r, c - 1))
		return (0);
	return (1);
}

int	fill_check(t_game *game, t_player *player)
{
	char	**dup;
	int		res;
	int		i;

	dup = duplicate_map(game);
	if (!dup)
		return (0);
	res = fill_map(game, dup, player->row, player->column);
	i = -1;
	while (dup[++i])
		free(dup[i]);
	free(dup);
	return (res);
}
