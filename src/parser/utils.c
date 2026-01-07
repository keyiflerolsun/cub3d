/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 09:15:44 by osancak           #+#    #+#             */
/*   Updated: 2026/01/06 18:14:19 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	err_exit(const char *message, t_game *game)
{
	write(2, "\033[0;31m\033[1m[!] ERROR\t\033[0m\033[0;35m", 33);
	while (*message)
		write(2, message++, 1);
	write(2, "\033[0m\n", 5);
	if (game && game->map.full)
		free_map(&game->map);
	if (game && game->texture.north)
		free(game->texture.north);
	if (game && game->texture.south)
		free(game->texture.south);
	if (game && game->texture.west)
		free(game->texture.west);
	if (game && game->texture.east)
		free(game->texture.east);
	if (game && game->mlx)
	{
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game)
		free(game);
	exit(EXIT_FAILURE);
}

char	*skip_spaces(char *str)
{
	while (*str && ft_strchr(" \t", *str))
		str++;
	return (str);
}
