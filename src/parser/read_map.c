/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 08:42:18 by osancak           #+#    #+#             */
/*   Updated: 2025/12/16 17:53:29 by osancak          ###   ########.fr       */
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
	trimmed = line;
	while (*trimmed && ft_strchr(" \t", *trimmed))
		trimmed++;
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

static char	*join_lines(char *map_lines, char *line, t_game *game)
{
	char	*temp;
	char	*newline;
	size_t	i;
	size_t	j;
	int		len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	temp = map_lines;
	newline = malloc(ft_strlen(map_lines) + ft_strlen(line) + 2);
	if (!newline)
		err_exit("Memory allocation failed", game);
	i = 0;
	j = 0;
	while (map_lines[i])
		newline[j++] = map_lines[i++];
	i = 0;
	while (line[i])
		newline[j++] = line[i++];
	newline[j++] = '\n';
	newline[j] = '\0';
	free(temp);
	return (newline);
}

static char	*read_config(t_game *game, int fd)
{
	char	*line;
	char	*map_lines;
	int		config_count;

	map_lines = ft_strdup("");
	config_count = 0;
	while (config_count < 6)
	{
		line = get_next_line(fd);
		if (!line)
			err_exit("Missing configuration in .cub file", game);
		parse_config_line(game, line, &config_count);
		free(line);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] != '\0' && line[0] != '\n')
			map_lines = join_lines(map_lines, line, game);
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
	map_lines = read_config(game, fd);
	close(fd);
	if (!map_lines || map_lines[0] == '\0')
		err_exit("map is empty or invalid", game);
	game->map.full = ft_split(map_lines, '\n');
	free(map_lines);
	if (!is_map_valid(game->map.full))
		err_exit("map structure is invalid", game);
	validate_map(game);
}
