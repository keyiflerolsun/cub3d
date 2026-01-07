/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 14:16:05 by osancak           #+#    #+#             */
/*   Updated: 2026/01/06 18:14:19 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parse_number(char **ptr)
{
	int	num;

	*ptr = skip_spaces(*ptr);
	if (!ft_isdigit(**ptr))
		return (-1);
	num = 0;
	while (**ptr && ft_isdigit(**ptr))
	{
		num = num * 10 + (**ptr - '0');
		(*ptr)++;
	}
	return (num);
}
