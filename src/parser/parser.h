/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:08:35 by osancak           #+#    #+#             */
/*   Updated: 2025/12/19 10:42:17 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "cub3d.h"

// read_map.c
void	read_map(t_game *game, char *map_path);

// map_utils.c
int		is_valid_char(const char *line, const char *charset);
int		is_map_valid(char **map);
void	free_map(t_map *map);

// map_borders.c
int		check_map_borders(char **map, int rows);

// validate_map.c
void	validate_map(t_game *game);

// validate_textures.c
void	validate_textures(t_game *game);

// flood_fill.c
int		fill_check(t_map *map, t_player *player);

// parse_texture.c
int		parse_textures(t_game *game, char *line);

// parse_color.c
int		parse_color(t_game *game, char *line);

// parse_number.c
int		parse_number(char **ptr);

// utils.c
void	err_exit(const char *message, t_game *game);

#endif
