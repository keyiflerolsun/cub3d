/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_game_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:52:31 by osancak           #+#    #+#             */
/*   Updated: 2025/12/20 15:58:22 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	offset;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	offset = (y * game->size_line) + (x * (game->bpp / 8));
	*(unsigned int *)(offset + game->data) = color;
}

void	clear_image(t_game *game)
{
	memset(game->data, 0, game->size_line * HEIGHT);
}

static void	init_player(t_game *game)
{
	game->player.x = (game->player.column * BLOCK_SIZE) + (BLOCK_SIZE / 2);
	game->player.y = (game->player.row * BLOCK_SIZE) + (BLOCK_SIZE / 2);
	if (game->player.direction == 'S')
		game->player.rotation = P / 2;
	else if (game->player.direction == 'W')
		game->player.rotation = P;
	else if (game->player.direction == 'E')
		game->player.rotation = P*2;
	else if (game->player.direction == 'N')
		game->player.rotation = P + P/2;
	game->player.key_down = 0;
	game->player.key_right = 0;
	game->player.key_up = 0;
	game->player.key_left = 0;
	game->player.rotate_left = 0;
	game->player.rotate_right = 0;
	game->player.speed = 3;
	game->player.angle_speed = P / 56;
}

void	aq_oc_fonksiyonu(t_game *game, int *h, int *w)
{
	game->north_wall.img = mlx_xpm_file_to_image(game->mlx, game->texture.north, w, h);
	game->north_wall.addr = mlx_get_data_addr(game->north_wall.img, &game->north_wall.bpp, &game->north_wall.row_length, &game->north_wall.endian);
	game->north_wall.width = *w;
	game->north_wall.height = *h;
	game->west_wall.img = mlx_xpm_file_to_image(game->mlx, game->texture.west, w, h);
	game->west_wall.addr = mlx_get_data_addr(game->west_wall.img, &game->west_wall.bpp, &game->west_wall.row_length, &game->west_wall.endian);
	game->west_wall.width = *w;
	game->west_wall.height = *h;
	game->south_wall.img = mlx_xpm_file_to_image(game->mlx, game->texture.south, w, h);
	game->south_wall.addr = mlx_get_data_addr(game->south_wall.img, &game->south_wall.bpp, &game->south_wall.row_length, &game->south_wall.endian);
	game->south_wall.width = *w;
	game->south_wall.height = *h;
	game->east_wall.img = mlx_xpm_file_to_image(game->mlx, game->texture.east, w, h);
	game->east_wall.addr = mlx_get_data_addr(game->east_wall.img, &game->east_wall.bpp, &game->east_wall.row_length, &game->east_wall.endian);
	game->east_wall.width = *w;
	game->east_wall.height = *h;
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
	int w, h;
	init_player(game);
	aq_oc_fonksiyonu(game, &w, &h);
}
