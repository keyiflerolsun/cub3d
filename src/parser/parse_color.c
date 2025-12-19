/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:27:48 by osancak           #+#    #+#             */
/*   Updated: 2025/12/14 11:45:33 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*skip_spaces(char *str)
{
	while (*str && ft_strchr(" \t", *str))
		str++;
	return (str);
}

static void	set_floor_color(t_game *game, int r, int g, int b)
{
	game->floor.r = r;
	game->floor.g = g;
	game->floor.b = b;
}

static void	set_ceiling_color(t_game *game, int r, int g, int b)
{
	game->ceiling.r = r;
	game->ceiling.g = g;
	game->ceiling.b = b;
}

static int	parse_rgb(char *ptr, int *r, int *g, int *b)
{
	*r = parse_number(&ptr);
	while (*ptr && *ptr != ',')
		ptr++;
	if (*ptr == ',')
		ptr++;
	*g = parse_number(&ptr);
	while (*ptr && *ptr != ',')
		ptr++;
	if (*ptr == ',')
		ptr++;
	*b = parse_number(&ptr);
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		return (0);
	return (1);
}

int	parse_color(t_game *game, char *line)
{
	char	*ptr;
	char	*trimmed;
	int		r;
	int		g;
	int		b;

	trimmed = skip_spaces(line);
	if (!ft_strchr("FC", trimmed[0]))
		return (0);
	ptr = skip_spaces(trimmed + 1);
	if (!parse_rgb(ptr, &r, &g, &b))
		return (0);
	if (trimmed[0] == 'F')
		set_floor_color(game, r, g, b);
	else if (trimmed[0] == 'C')
		set_ceiling_color(game, r, g, b);
	else
		return (0);
	return (1);
}
