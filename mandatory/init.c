/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:59:56 by ailbezer          #+#    #+#             */
/*   Updated: 2025/01/18 19:28:49 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static float	get_scale(t_fdf *fdf)
{
	float	scale;
	float	scale_x;
	float	scale_y;

	scale_x = WIDTH_WINDOW / (float)fdf->map->width;
	scale_y = HEIGHT_WINDOW / (float)fdf->map->height;
	if (scale_x < scale_y)
		scale = scale_x;
	else
		scale = scale_y;
	return (scale / 1.80);
}

static t_camera	*cam_config(t_fdf *fdf)
{
	t_camera	*camera;

	camera = malloc(sizeof(t_camera));
	if (!camera)
		exit_msg(5);
	camera->scale = get_scale(fdf);
	camera->x = (WIDTH_WINDOW / 2);
	camera->y = (HEIGHT_WINDOW / 2);
	camera->z = 1;
	if (fdf->map->z_top <= 20)
		camera->z = 10;
	else if (fdf->map->z_top > 720)
		camera->z = 0.05;
	return (camera);
}

t_fdf	*init_fdf(char *map)
{
	t_fdf	*fdf;

	fdf = malloc(sizeof(t_fdf));
	if (!fdf)
		exit_msg(5);
	fdf->map = parse(map);
	if (!fdf->map)
		return (free(fdf), NULL);
	fdf->mlx = mlx_init(WIDTH_WINDOW, HEIGHT_WINDOW, "FDF", 1);
	if (!fdf->mlx)
		exit_msg(6);
	fdf->image = mlx_new_image(fdf->mlx, WIDTH_WINDOW, HEIGHT_WINDOW);
	if (fdf->image == NULL)
		exit_msg(5);
	fdf->camera = cam_config(fdf);
	mlx_image_to_window(fdf->mlx, fdf->image, 0, 0);
	return (fdf);
}
