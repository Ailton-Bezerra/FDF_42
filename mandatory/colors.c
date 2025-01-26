/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:09:19 by ailbezer          #+#    #+#             */
/*   Updated: 2025/01/26 10:11:10 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	ft_hex_to_int(char *hexa)
{
	int	res;
	int	byte;

	res = 0;
	while (*hexa != ' ' && *hexa)
	{
		byte = *hexa++;
		if (byte >= '0' && byte <= '9')
			byte = byte - '0';
		else if (byte >= 'a' && byte <= 'f')
			byte = byte - 'a' + 10;
		else if (byte >= 'A' && byte <= 'F')
			byte = byte - 'A' + 10;
		res = (res * 16) + byte;
	}
	return (res);
}

uint32_t	put_alpha(uint32_t color_rgb)
{
	uint32_t		color_rgba;
	unsigned char	*ptr;

	color_rgba = color_rgb << 8;
	ptr = (unsigned char *)&color_rgba;
	*ptr = 0xFF;
	return (color_rgba);
}
