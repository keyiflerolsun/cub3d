/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:43:00 by keyiflerols       #+#    #+#             */
/*   Updated: 2026/01/06 16:43:39 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	rgb_to_hex(t_color color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}

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
