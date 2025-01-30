/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:57:56 by ailbezer          #+#    #+#             */
/*   Updated: 2025/01/30 09:11:24 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

void	put_pixel(t_fdf *fdf, int x, int y, uint32_t color)
{
	if (x <= 0 || x >= WIDTH_WINDOW || y <= 0 || y >= HEIGHT_WINDOW)
		return ;
	if (fdf->map->invert_color == 1)
		mlx_put_pixel(fdf->image, x, y, invert_color(color));
	else
		mlx_put_pixel(fdf->image, x, y, color);
}

void	axis_y_line(t_fdf *fdf, t_coordinates start, t_coordinates end)
{
	if (end.y > start.y)
	{
		while ((int)start.y != (int)end.y)
		{
			start.y++;
			put_pixel(fdf, (int)start.x, (int)start.y, start.color);
		}
	}
	else
	{
		while ((int)start.y != (int)end.y)
		{
			start.y--;
			put_pixel(fdf, (int)start.x, (int)start.y, start.color);
		}
	}
}

void	axis_x_line(t_fdf *fdf, t_coordinates start, t_coordinates end)
{
	if (end.x > start.x)
	{
		while ((int)start.x != (int)end.x)
		{
			start.x++;
			put_pixel(fdf, (int)start.x, (int)start.y, start.color);
		}
	}
	else
	{
		while ((int)start.x != (int)end.x)
		{
			start.x--;
			put_pixel(fdf, (int)start.x, (int)start.y, start.color);
		}
	}
}

void	diag_y_line(t_fdf *fdf, t_draw_line line, t_coordinates start,
					t_coordinates end)
{
	int		grad_len;

	grad_len = ft_abs(end.y - start.y);
	line.control = line.diff_y / 2;
	put_pixel(fdf, (int)start.x, (int)start.y, start.color);
	while ((int)start.y != (int)end.y)
	{
		start.y += line.inc_y;
		line.control -= line.diff_x;
		if (line.control < 0)
		{
			start.x += line.inc_x;
			line.control += line.diff_y;
		}
		put_pixel(fdf, (int)start.x, (int)start.y, start.color);
	}
}

void	diag_x_line(t_fdf *fdf, t_draw_line line, t_coordinates start,
					t_coordinates end)
{
	int		grad_len;

	grad_len = ft_abs(end.x - start.x);
	line.control = line.diff_x / 2;
	put_pixel(fdf, (int)start.x, (int)start.y, start.color);
	while ((int)start.x != (int)end.x)
	{
		start.x += line.inc_x;
		line.control -= line.diff_y;
		if (line.control < 0)
		{
			start.y += line.inc_y;
			line.control += line.diff_x;
		}
		put_pixel(fdf, (int)start.x, (int)start.y, start.color);
	}
}
