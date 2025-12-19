/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 01:35:03 by osancak           #+#    #+#             */
/*   Updated: 2025/10/28 01:35:03 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"
#include "game.h"

int	game_close(t_game *game)
{
	if (game->mlx)
	{
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
	}
	free(game->mlx);
	if (game->map.full)
		free_map(&game->map);
	if (game->texture.north)
		free(game->texture.north);
	if (game->texture.south)
		free(game->texture.south);
	if (game->texture.west)
		free(game->texture.west);
	if (game->texture.east)
		free(game->texture.east);
	free(game);
	exit(EXIT_SUCCESS);
	return (1);
}

static int	key_hook(int keycode, t_game *game)
{
	if (keycode == XK_q || keycode == XK_Escape)
		game_close(game);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		err_exit("Usage » ./cub3d 'path/to/map/file.cub'", NULL);
	game = calloc(1, sizeof(t_game));
	if (!game)
		err_exit("Memory allocation failed", NULL);
	read_map(game, argv[1]);
	print_game_info(game);
	game->mlx = mlx_init();
	if (!game->mlx)
		err_exit("MLX initialization failed", game);
	game->win = mlx_new_window(game->mlx, 1920, 1080, "cub3D");
	if (!game->win)
		err_exit("Window creation failed", game);
	mlx_hook(game->win, DestroyNotify, KeyPressMask, game_close, game);
	mlx_key_hook(game->win, key_hook, game);
	mlx_loop(game->mlx);
	return (0);
}
