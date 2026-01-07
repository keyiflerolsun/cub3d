/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 08:42:18 by osancak           #+#    #+#             */
/*   Updated: 2026/01/06 18:14:19 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	parse_config_line(t_game *game, char *line, int *config_count)
{
	int		len;
	char	*trimmed;

	if (!line)
		return ;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	if (line[0] == '\0')
		return ;
	trimmed = skip_spaces(line);
	if (ft_strchr("NSWE", trimmed[0]))
	{
		if (parse_textures(game, trimmed))
			(*config_count)++;
	}
	else if (ft_strchr("FC", trimmed[0]))
	{
		if (parse_color(game, trimmed))
			(*config_count)++;
	}
}

static void	read_headers(t_game *game, int fd)
{
	char	*line;
	int		config_count;

	config_count = 0;
	while (config_count < 6)
	{
		line = get_next_line(fd);
		if (!line)
			err_exit("Missing configuration in .cub file", game);
		parse_config_line(game, line, &config_count);
		free(line);
	}
}

static char	*read_map_data(t_game *game, int fd)
{
	char	*line;
	char	*map_lines;
	int		map_started;

	map_lines = ft_strdup("");
	map_started = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if ((line[0] == '\n' || line[0] == '\0') && map_started == 1)
			map_started = 2;
		else if (map_started == 2 && line[0] != '\n' && line[0] != '\0')
			err_exit("Empty line inside the map structure", game);
		else if (line[0] != '\n' && line[0] != '\0')
		{
			map_started = 1;
			map_lines = join_lines(map_lines, line, game);
		}
		free(line);
	}
	return (map_lines);
}

void	read_map(t_game *game, char *map_path)
{
	char	*cub;
	char	*map_lines;
	int		fd;

	cub = ft_strnstr(map_path, ".cub");
	if (!cub || cub[4] != '\0')
		err_exit("file extension must be .cub", game);
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		err_exit("file not found", game);
	read_headers(game, fd);
	map_lines = read_map_data(game, fd);
	close(fd);
	if (!map_lines || map_lines[0] == '\0')
		err_exit("map is empty or invalid", game);
	game->map.full = ft_split(map_lines, '\n');
	free(map_lines);
	if (!is_map_valid(game->map.full))
		err_exit("map structure is invalid", game);
	validate_map(game);
}
