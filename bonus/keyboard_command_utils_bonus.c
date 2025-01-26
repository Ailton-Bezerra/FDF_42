/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_command_utils_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:37:09 by ailbezer          #+#    #+#             */
/*   Updated: 2025/01/26 16:50:08 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

void	zoom(t_fdf *fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_EQUAL))
		fdf->camera->scale += 0.3;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_MINUS))
		fdf->camera->scale -= 0.3;
}

void	rotation(t_fdf *fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_A))
		fdf->camera->y_rotation += 0.0175;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_D))
		fdf->camera->y_rotation -= 0.0175;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_W))
		fdf->camera->x_rotation += 0.0175;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_S))
		fdf->camera->x_rotation -= 0.0175;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Q))
		fdf->camera->z_rotation += 0.0175;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_E))
		fdf->camera->z_rotation -= 0.0175;
}

void	z_scale(t_fdf *fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_U))
		fdf->camera->z_default += fdf->camera->z_scale_resize;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_F))
		fdf->camera->z_default -= fdf->camera->z_scale_resize;
}

void	movement(t_fdf *fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_UP))
		fdf->camera->y -= 25;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_DOWN))
		fdf->camera->y += 25;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT))
		fdf->camera->x -= 25;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_RIGHT))
		fdf->camera->x += 25;
}

void	set_camera(t_fdf *fdf, int projection_type)
{
	fdf->camera->projection = projection_type;
	fdf->camera->scale = get_scale(fdf);
	fdf->camera->x = WIDTH_WINDOW / 2;
	fdf->camera->y = HEIGHT_WINDOW / 2;
	fdf->camera->x_rotation = 0;
	fdf->camera->y_rotation = 0;
	fdf->camera->z_rotation = 0;
	if (fdf->map->width <= 500)
		fdf->camera->z_scale_resize = 0.5;
	else
		fdf->camera->z_scale_resize = 0.005;
	if (fdf->map->z_top <= 20)
		fdf->camera->z_default = 10;
	else if (fdf->map->z_top > 720)
		fdf->camera->z_default = 0.03;
	else
		fdf->camera->z_default = 1;
}
