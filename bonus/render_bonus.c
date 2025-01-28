/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:57:36 by ailbezer          #+#    #+#             */
/*   Updated: 2025/01/28 11:06:24 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

static void	settings(t_fdf *fdf, t_coordinates start, t_coordinates end)
{
	scale(fdf, &start, &end);
	if (fdf->camera->projection == ISOMETRIC)
		isometry(fdf, &start, &end);
	rotate_x(fdf, &start, &end, fdf->camera->x_rotation);
	rotate_y(&start, &end, fdf->camera->y_rotation);
	rotate_z(&start, &end, fdf->camera->z_rotation);
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

void	render(void *param)
{
	int		x;
	int		y;
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (fdf->map->invert_color == 1)
		invert_background(fdf);
	else
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
