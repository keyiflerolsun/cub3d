/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 11:55:58 by hyakici           #+#    #+#             */
/*   Updated: 2025/12/20 15:58:20 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	rotate_player(t_game *game)
{
	if (game->player.rotate_left)
		game->player.rotation -= game->player.angle_speed;
	if (game->player.rotate_right)
		game->player.rotation += game->player.angle_speed;
	if (game->player.rotation > 2 * P)
		game->player.rotation -= 2 * P;
	if (game->player.rotation < 0)
		game->player.rotation += 2 * P;
}

static void	position_player(t_game *game, float *new_y, float *new_x)
{
	if (game->player.key_right)
	{
		*new_y -= cos(game->player.rotation) * game->player.speed;
		*new_x += sin(game->player.rotation) * game->player.speed;
	}
	if (game->player.key_left)
	{
		*new_y += cos(game->player.rotation) * game->player.speed;
		*new_x -= sin(game->player.rotation) * game->player.speed;
	}
	if (game->player.key_up)
	{
		*new_x -= cos(game->player.rotation) * game->player.speed;
		*new_y -= sin(game->player.rotation) * game->player.speed;
	}
	if (game->player.key_down)
	{
		*new_x += cos(game->player.rotation) * game->player.speed;
		*new_y += sin(game->player.rotation) * game->player.speed;
	}
}

void	move_player(t_game *game)
{
	float	new_x;
	float	new_y;
	int		map_x;
	int		map_y;

	rotate_player(game);
	new_y = game->player.y;
	new_x = game->player.x;
	position_player(game, &new_y, &new_x);
	map_x = (int)(game->player.x / BLOCK_SIZE);
	map_y = (int)(new_y / BLOCK_SIZE);
	if (map_y >= 0 && map_y < 10 && map_x >= 0 && map_x < 15)
	{
		if (game->map.full[map_y][map_x] != '1')
			game->player.y = new_y;
	}
	map_x = (int)(new_x / BLOCK_SIZE);
	map_y = (int)(game->player.y / BLOCK_SIZE);
	if (map_y >= 0 && map_y < 10 && map_x >= 0 && map_x < 15)
	{
		if (game->map.full[map_y][map_x] != '1')
			game->player.x = new_x;
	}
}
