/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_game_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:52:31 by osancak           #+#    #+#             */
/*   Updated: 2026/01/06 18:14:19 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	init_player(t_game *game)
{
	game->player.x = (game->player.column * BLOCK_SIZE) + (BLOCK_SIZE / 2);
	game->player.y = (game->player.row * BLOCK_SIZE) + (BLOCK_SIZE / 2);
	if (game->player.direction == 'S')
		game->player.rotation = P / 2;
	else if (game->player.direction == 'W')
		game->player.rotation = P;
	else if (game->player.direction == 'E')
		game->player.rotation = P * 2;
	else if (game->player.direction == 'N')
		game->player.rotation = P + P / 2;
	game->player.key_down = 0;
	game->player.key_right = 0;
	game->player.key_up = 0;
	game->player.key_left = 0;
	game->player.rotate_left = 0;
	game->player.rotate_right = 0;
	game->player.speed = 3;
	game->player.angle_speed = P / 56;
}

static void	init_wall(t_game *g, t_img *w_i, char *path)
{
	w_i->img = mlx_xpm_file_to_image(g->mlx, path, &w_i->width, &w_i->height);
	w_i->addr = mlx_get_data_addr(w_i->img, &w_i->bpp,
			&w_i->row_length, &w_i->endian);
}

void	init_textures(t_game *game)
{
	init_wall(game, &game->north_wall, game->texture.north);
	init_wall(game, &game->west_wall, game->texture.west);
	init_wall(game, &game->south_wall, game->texture.south);
	init_wall(game, &game->east_wall, game->texture.east);
}

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
	init_player(game);
	init_textures(game);
}
