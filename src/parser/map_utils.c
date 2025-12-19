/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:23:14 by osancak           #+#    #+#             */
/*   Updated: 2025/12/15 14:37:42 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_valid_char(const char *line, const char *charset)
{
	while (*line)
	{
		if (!ft_strchr(charset, *line))
			return (0);
		line++;
	}
	return (1);
}

int	is_map_valid(char **map)
{
	int	rows;
	int	cols;
	int	line_len;

	if (!map || !map[0])
		return (0);
	cols = 0;
	rows = 0;
	while (map[rows])
	{
		line_len = ft_strlen(map[rows]);
		if (line_len > cols)
			cols = line_len;
		rows++;
	}
	if (rows < 3 || cols < 3)
		return (0);
	if (!check_map_borders(map, rows))
		return (0);
	return (1);
}

void	free_map(t_map *map)
{
	char	**_map;

	_map = map->full;
	if (map && map->full)
	{
		while (*(map->full))
			free(*(map->full)++);
		free(_map);
		map->full = NULL;
	}
}
