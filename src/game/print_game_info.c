/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_game_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:52:31 by osancak           #+#    #+#             */
/*   Updated: 2025/12/13 15:08:56 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	print_game_info(t_game *game)
{
	ft_printf("\n╔═══════════════════════════════╗\n");
	ft_printf("║   CUB3D PARSER SUCCESS ✓     ║\n");
	ft_printf("╚═══════════════════════════════╝\n\n");
	ft_printf("Player: Row %d, Col %d, Dir '%c'\n",
		game->player.row, game->player.column, game->player.direction);
	ft_printf("Map: %dx%d\n", game->map.rows, game->map.columns);
	ft_printf("NO: %s\n", game->texture.north);
	ft_printf("SO: %s\n", game->texture.south);
	ft_printf("WE: %s\n", game->texture.west);
	ft_printf("EA: %s\n", game->texture.east);
	ft_printf("F: RGB(%d,%d,%d)\n",
		game->floor.r, game->floor.g, game->floor.b);
	ft_printf("C: RGB(%d,%d,%d)\n",
		game->ceiling.r, game->ceiling.g, game->ceiling.b);
	ft_printf("\n");
}
