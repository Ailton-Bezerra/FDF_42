/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_and_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:05:47 by ailbezer          #+#    #+#             */
/*   Updated: 2025/01/18 19:32:36 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	exit_msg(int msg)
{
	if (msg == 1)
		ft_putendl_fd("\033[1;31mValid format: ./fdf *.fdf\033[0m", 1);
	else if (msg == 2)
		ft_putendl_fd("\033[1;31mValid map format: *.fdf\033[0m", 1);
	else if (msg == 3)
		ft_putendl_fd("\033[1;31mError opening file...\033[0m", 1);
	else if (msg == 4)
		ft_putendl_fd("\033[1;31mError reading file...\033[0m", 1);
	else if (msg == 5)
		ft_putendl_fd("\033[1;31mError alocating memory\033[0m", 1);
	else if (msg == 6)
		ft_putendl_fd("\033[1;31mFailed to create image\033[0m", 1);
	exit(msg);
}

static void	free_matrix(t_map *map)
{
	while (map->height--)
		free(map->matrix[map->height]);
	free(map->matrix);
}

void	free_fdf(t_fdf *fdf)
{
	if (fdf->map)
	{
		free_matrix(fdf->map);
		free(fdf->map);
	}
	if (fdf->camera)
		free(fdf->camera);
	free(fdf);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
