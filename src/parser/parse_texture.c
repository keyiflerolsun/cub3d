/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:34:19 by osancak           #+#    #+#             */
/*   Updated: 2026/01/06 18:14:19 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*get_path(char *line)
{
	char	*start;
	char	*end;
	char	*path;
	int		len;
	int		i;

	start = skip_spaces(line);
	end = start;
	while (*end && !ft_strchr(" \t\n", *end))
		end++;
	len = end - start;
	path = malloc(sizeof(char) * (len + 1));
	if (!path)
		return (NULL);
	i = 0;
	while (i < len)
	{
		path[i] = start[i];
		i++;
	}
	path[i] = '\0';
	return (path);
}

int	parse_textures(t_game *game, char *line)
{
	char	*trimmed;

	trimmed = skip_spaces(line);
	if (!ft_strncmp(trimmed, "NO ", 3))
		game->texture.north = get_path(trimmed + 2);
	else if (!ft_strncmp(trimmed, "SO ", 3))
		game->texture.south = get_path(trimmed + 2);
	else if (!ft_strncmp(trimmed, "WE ", 3))
		game->texture.west = get_path(trimmed + 2);
	else if (!ft_strncmp(trimmed, "EA ", 3))
		game->texture.east = get_path(trimmed + 2);
	else
		return (0);
	return (1);
}
