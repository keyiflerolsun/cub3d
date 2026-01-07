/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:27:48 by osancak           #+#    #+#             */
/*   Updated: 2026/01/06 18:14:19 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

static int	count_commas(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == ',')
			count++;
		str++;
	}
	return (count);
}

static int	parse_rgb(char *ptr, int *r, int *g, int *b)
{
	if (count_commas(ptr) != 2)
		return (0);
	*r = parse_number(&ptr);
	ptr = skip_spaces(ptr);
	if (*ptr != ',')
		return (0);
	ptr++;
	*g = parse_number(&ptr);
	ptr = skip_spaces(ptr);
	if (*ptr != ',')
		return (0);
	ptr++;
	*b = parse_number(&ptr);
	ptr = skip_spaces(ptr);
	if (*ptr != '\0')
		return (0);
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
		err_exit("Invalid RGB color format", game);
	if (trimmed[0] == 'F')
		set_floor_color(game, r, g, b);
	else if (trimmed[0] == 'C')
		set_ceiling_color(game, r, g, b);
	else
		return (0);
	return (1);
}
