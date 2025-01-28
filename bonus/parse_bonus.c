/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:55:09 by ailbezer          #+#    #+#             */
/*   Updated: 2025/01/28 11:37:37 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

static t_map	*new_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (exit_msg(5), NULL);
	map->height = 0;
	map->width = 0;
	map->z_top = 0;
	map->invert_color = 0;
	map->matrix = NULL;
	return (map);
}

static int	get_width(char *map_id)
{
	int		fd;
	int		width;
	char	*line;
	char	**col;

	width = 0;
	fd = open(map_id, O_RDONLY);
	if (fd < 0)
		exit_msg(1);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), -1);
	col = ft_split(line, ' ');
	free(line);
	if (!col)
		return (close(fd), exit_msg(5), -1);
	while (col[width] && col[width][0] != '\n')
		width++;
	free_split(col);
	close(fd);
	return (width);
}

static int	get_height(char *map_id)
{
	int		height;
	int		fd;
	char	*line;

	height = 0;
	fd = open(map_id, O_RDONLY);
	if (fd < 0)
		return (exit_msg(1), -1);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), -1);
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

static t_coordinates	**alloc_matrix(int width, int height)
{
	t_coordinates	**matrix;
	int				i;

	matrix = malloc(sizeof(t_coordinates *) * height);
	if (!matrix)
		exit_msg(5);
	i = -1;
	while (++i < height)
	{
		matrix[i] = ft_calloc(width, sizeof(t_coordinates));
		if (!matrix[i])
		{
			while (i)
				free(matrix[--i]);
			free(matrix);
			exit_msg(5);
		}
	}
	return (matrix);
}

t_map	*parse(char *map_id)
{
	t_map	*map;

	map = new_map();
	if (!map)
		return (NULL);
	map->width = get_width(map_id);
	map->height = get_height(map_id);
	map->matrix = alloc_matrix(map->width, map->height);
	convert_map(map, map_id);
	center_map(map);
	return (map);
}
