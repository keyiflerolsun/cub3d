/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_borders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:02:37 by osancak           #+#    #+#             */
/*   Updated: 2025/12/17 16:22:14 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	check_side_borders(char **map, int rows)
{
	int	i;
	int	len;

	i = -1;
	while (++i < rows)
	{
		len = ft_strlen(map[i]);
		if (len == 0)
			return (0);
		if (!ft_strchr("1 ", map[i][0]))
			return (0);
		if (len > 0 && !ft_strchr("1 ", map[i][len - 1]))
			return (0);
	}
	return (1);
}

static int	check_top_bottom(char **map, int rows)
{
	int	i;
	int	len;

	i = -1;
	while (map[0][++i])
	{
		if (!ft_strchr("1 ", map[0][i]))
			return (0);
	}
	i = -1;
	len = ft_strlen(map[rows - 1]);
	while (++i < len)
	{
		if (!ft_strchr("1 ", map[rows - 1][i]))
			return (0);
	}
	return (1);
}

int	check_map_borders(char **map, int rows)
{
	if (!check_side_borders(map, rows))
		return (0);
	if (!check_top_bottom(map, rows))
		return (0);
	return (1);
}
