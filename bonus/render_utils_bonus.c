/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:55:44 by ailbezer          #+#    #+#             */
/*   Updated: 2025/01/26 16:50:56 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

void	scale(t_fdf *fdf, t_coordinates *start, t_coordinates *end)
{
	start->x *= fdf->camera->scale;
	start->y *= fdf->camera->scale;
	end->x *= fdf->camera->scale;
	end->y *= fdf->camera->scale;
}

void	centralize(t_fdf *fdf, t_coordinates *start, t_coordinates *end)
{
	start->x += fdf->camera->x;
	start->y += fdf->camera->y;
	end->x += fdf->camera->x;
	end->y += fdf->camera->y;
}

void	isometry(t_fdf *fdf, t_coordinates *start, t_coordinates *end)
{
	t_coordinates	new_start;
	t_coordinates	new_end;

	new_start.x = (start->x - start->y) * cos(0.7071);
	new_start.y = (start->x + start->y) * sin(0.7071)
		- (start->z * fdf->camera->z_default);
	new_end.x = (end->x - end->y) * cos(0.7071);
	new_end.y = (end->x + end->y) * sin(0.7071)
		- (end->z * fdf->camera->z_default);
	start->x = new_start.x;
	start->y = new_start.y;
	end->x = new_end.x;
	end->y = new_end.y;
}

static void	new_line_data(t_draw_line *line, t_coordinates start,
	t_coordinates end)
{
	line->diff_x = ft_abs(end.x - start.x);
	line->diff_y = ft_abs(end.y - start.y);
	line->control = 0;
	if (end.x > start.x)
		line->inc_x = 1;
	else
		line->inc_x = -1;
	if (end.y > start.y)
		line->inc_y = 1;
	else
		line->inc_y = -1;
}

void	draw_line(t_fdf *fdf, t_coordinates start, t_coordinates end)
{
	t_draw_line	line;

	new_line_data(&line, start, end);
	if (line.diff_x == 0)
		axis_y_line(fdf, start, end);
	if (line.diff_y == 0)
		axis_x_line(fdf, start, end);
	else
	{
		if (line.diff_x >= line.diff_y)
			diag_x_line(fdf, line, start, end);
		else
			diag_y_line(fdf, line, start, end);
	}
}
