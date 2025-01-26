/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:15:39 by ailbezer          #+#    #+#             */
/*   Updated: 2025/01/26 16:45:38 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

void	projection(t_fdf *fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_P))
		set_camera(fdf, ISOMETRIC);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_T))
		set_camera(fdf, TOP_VIEW);
}

static void	reset_view(t_fdf *fdf)
{
	if (!mlx_is_key_down(fdf->mlx, MLX_KEY_R))
		return ;
	set_camera(fdf, fdf->camera->projection);
}

static void	keyboard_command(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
	reset_view(fdf);
	projection(fdf);
	movement(fdf);
	z_scale(fdf);
	rotation(fdf);
	zoom(fdf);
}

int	main(int argc, char *argv[])
{
	t_fdf	*fdf;

	if (argc != 2)
		exit_msg(1);
	check_map(argv[1]);
	fdf = init_fdf(argv[1]);
	mlx_loop_hook(fdf->mlx, keyboard_command, fdf);
	mlx_loop_hook(fdf->mlx, render, fdf);
	mlx_loop(fdf->mlx);
	mlx_terminate(fdf->mlx);
	free_fdf(fdf);
	return (0);
}
