/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:57:36 by ailbezer          #+#    #+#             */
/*   Updated: 2025/01/18 19:23:11 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	settings(t_fdf *fdf, t_coordinates start, t_coordinates end)
{
	scale(fdf, &start, &end);
	isometry(fdf, &start, &end);
	centralize(fdf, &start, &end);
	draw_line(fdf, start, end);
}

static void	background(t_fdf *fdf)
{
	uint32_t	*pixel;
	uint32_t	index;

	pixel = (uint32_t *)fdf->image->pixels;
	index = fdf->image->height * fdf->image->width;
	while (index--)
		pixel[index] = 0xff000000;
}

void	render(t_fdf *fdf)
{
	int	x;
	int	y;

	background(fdf);
	y = 0;
	while (y + 1 <= fdf->map->height)
	{
		x = 0;
		while (x + 1 <= fdf->map->width)
		{
			if (x + 1 < fdf->map->width)
				settings(fdf, fdf->map->matrix[y][x],
					fdf->map->matrix[y][x + 1]);
			if (y + 1 < fdf->map->height)
				settings(fdf, fdf->map->matrix[y][x],
					fdf->map->matrix[y + 1][x]);
			x++;
		}
		y++;
	}
}
