/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 09:15:44 by osancak           #+#    #+#             */
/*   Updated: 2025/12/18 13:26:08 by osancak          ###   ########.fr       */
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
