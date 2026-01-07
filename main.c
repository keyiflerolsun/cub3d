/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 01:35:03 by osancak           #+#    #+#             */
/*   Updated: 2025/12/20 15:58:07 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "game.h"
#include "parser.h"

int	game_close(t_game *game)
{
	if (game->north_wall.img)
		mlx_destroy_image(game->mlx, game->north_wall.img);
	if (game->south_wall.img)
		mlx_destroy_image(game->mlx, game->south_wall.img);
	if (game->west_wall.img)
		mlx_destroy_image(game->mlx, game->west_wall.img);
	if (game->east_wall.img)
		mlx_destroy_image(game->mlx, game->east_wall.img);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
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

int	key_press(int keycode, t_game *game)
{
	printf("x : %f \n", game->player.x);
	printf("y : %f \n", game->player.y);
	if (keycode == XK_s)
		game->player.key_up = 1;
	if (keycode == XK_w)
		game->player.key_down = 1;
	if (keycode == XK_a)
		game->player.key_right = 1;
	if (keycode == XK_d)
		game->player.key_left = 1;
	if (keycode == XK_Left)
		game->player.rotate_left = 1;
	if (keycode == XK_Right)
		game->player.rotate_right = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == XK_q || keycode == XK_Escape)
		game_close(game);
	if (keycode == XK_s)
		game->player.key_up = 0;
	if (keycode == XK_w)
		game->player.key_down = 0;
	if (keycode == XK_a)
		game->player.key_right = 0;
	if (keycode == XK_d)
		game->player.key_left = 0;
	if (keycode == XK_Left)
		game->player.rotate_left = 0;
	if (keycode == XK_Right)
		game->player.rotate_right = 0;
	return (0);
}

void	key_hooks(t_game *game)
{
	mlx_hook(game->win, KeyPress, (1L << 0), key_press, game);
	mlx_hook(game->win, KeyRelease, (1L << 1), key_release, game);
	mlx_hook(game->win, DestroyNotify, StructureNotifyMask, game_close, game);
	mlx_loop_hook(game->mlx, draw_loop, game);
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
	game->mlx = mlx_init();
	if (!game->mlx)
		err_exit("MLX initialization failed", game);
	print_game_info(game);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	if (!game->win)
		err_exit("Window creation failed", game);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		err_exit("Image creation failed", game);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	if (!game->data)
		err_exit("Data creation failed", game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	key_hooks(game);
	mlx_loop(game->mlx);
	return (0);
}
