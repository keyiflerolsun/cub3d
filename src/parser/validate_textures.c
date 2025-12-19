/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:24:16 by osancak           #+#    #+#             */
/*   Updated: 2025/12/15 08:57:03 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	validate_textures(t_game *game)
{
	int	fd;

	fd = open(game->texture.north, O_RDONLY);
	if (fd < 0)
		err_exit("North texture file not found or cannot be opened", game);
	close(fd);
	fd = open(game->texture.south, O_RDONLY);
	if (fd < 0)
		err_exit("South texture file not found or cannot be opened", game);
	close(fd);
	fd = open(game->texture.west, O_RDONLY);
	if (fd < 0)
		err_exit("West texture file not found or cannot be opened", game);
	close(fd);
	fd = open(game->texture.east, O_RDONLY);
	if (fd < 0)
		err_exit("East texture file not found or cannot be opened", game);
	close(fd);
}
