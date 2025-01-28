/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:09:19 by ailbezer          #+#    #+#             */
/*   Updated: 2025/01/28 11:38:52 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

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

uint32_t	invert_color(uint32_t color)
{	
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
	uint32_t		invert_color;

	r = 255 - ((color >> 24) & 255);
	g = 255 - ((color >> 16) & 255);
	b = 255 - ((color >> 8) & 255);
	a = color & 255;
	invert_color = (r << 24) | (g << 16) | (b << 8) | a;
	return (invert_color);
}

void	invert_background(t_fdf *fdf)
{
	uint32_t	*pixel;
	uint32_t	index;

	pixel = (uint32_t *)fdf->image->pixels;
	index = fdf->image->height * fdf->image->width;
	while (index--)
		pixel[index] = 0xffd3d3d3;
}
