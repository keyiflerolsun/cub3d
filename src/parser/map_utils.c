/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 09:23:14 by osancak           #+#    #+#             */
/*   Updated: 2026/01/06 18:14:19 by osancak          ###   ########.fr       */
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

char	*join_lines(char *map_lines, char *line, t_game *game)
{
	char	*temp;
	char	*newline;
	size_t	src_i;
	size_t	dst_i;

	if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	temp = map_lines;
	newline = malloc(ft_strlen(map_lines) + ft_strlen(line) + 2);
	if (!newline)
		err_exit("Memory allocation failed", game);
	src_i = 0;
	dst_i = 0;
	while (map_lines[src_i])
		newline[dst_i++] = map_lines[src_i++];
	src_i = 0;
	while (line[src_i])
		newline[dst_i++] = line[src_i++];
	newline[dst_i++] = '\n';
	newline[dst_i] = '\0';
	free(temp);
	return (newline);
}
