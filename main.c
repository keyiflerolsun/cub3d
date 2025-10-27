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

int	game_close(t_game *game)
{
	if (game->mlx)
	{
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
	}
	free(game->mlx);
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

int	main(void)
{
	t_game	*game;

	game = calloc(sizeof(t_game), 1);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 1920, 1080, "Merhaba Mahmut");
	mlx_hook(game->win, DestroyNotify, KeyPressMask, game_close, game);
	mlx_key_hook(game->win, key_hook, game);
	mlx_loop(game->mlx);
	return (0);
}
