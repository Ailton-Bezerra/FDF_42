/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:15:39 by ailbezer          #+#    #+#             */
/*   Updated: 2025/01/18 19:29:34 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	keyboard_command(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
}

int	main(int argc, char *argv[])
{
	t_fdf	*fdf;

	if (argc != 2)
		exit_msg(1);
	check_map(argv[1]);
	fdf = init_fdf(argv[1]);
	mlx_loop_hook(fdf->mlx, keyboard_command, fdf);
	render(fdf);
	mlx_loop(fdf->mlx);
	mlx_terminate(fdf->mlx);
	free_fdf(fdf);
	return (0);
}
