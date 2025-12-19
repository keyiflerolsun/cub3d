/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:45:22 by osancak           #+#    #+#             */
/*   Updated: 2025/12/16 09:18:56 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	**duplicate_map(char **map)
{
	char	**res;
	int		i;

	i = 0;
	while (map[i])
		i++;
	res = ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (map[++i])
		res[i] = ft_strdup(map[i]);
	return (res);
}

static void	fill_map(char **map, int row, int column)
{
	if (ft_strchr("1*", map[row][column]))
		return ;
	map[row][column] = '*';
	fill_map(map, row + 1, column);
	fill_map(map, row - 1, column);
	fill_map(map, row, column + 1);
	fill_map(map, row, column - 1);
}

int	fill_check(t_map *map, t_player *player)
{
	char	**dup;
	int		res;
	int		i;

	res = 1;
	dup = duplicate_map(map->full);
	fill_map(dup, player->row, player->column);
	i = -1;
	while (dup[++i])
	{
		if (!is_valid_char(dup[i], "01* "))
		{
			res = 0;
			break ;
		}
	}
	i = -1;
	while (dup[++i])
		free(dup[i]);
	free(dup);
	return (res);
}
