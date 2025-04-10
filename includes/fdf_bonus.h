/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:59:02 by ailbezer          #+#    #+#             */
/*   Updated: 2025/01/28 11:12:10 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "../libs/libft/get_next_line.h"
# include "../libs/libft/libft.h"
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>

# define WIDTH_WINDOW 1600
# define HEIGHT_WINDOW 900
# define ISOMETRIC 0
# define TOP_VIEW 1

typedef struct s_draw_line
{
	int			diff_x;
	int			diff_y;
	int			inc_x;
	int			inc_y;
	int			control;
}				t_draw_line;

typedef struct s_coordinates
{
	float		x;
	float		y;
	float		z;
	uint32_t	color;
}				t_coordinates;

typedef struct s_map
{
	int				width;
	int				height;
	float			z_top;
	t_coordinates	**matrix;
	int				invert_color;
}					t_map;

typedef struct s_camera
{
	float		x;
	float		x_rotation;
	float		y;
	float		y_rotation;
	float		z_default;
	float		z_rotation;
	float		z_scale_resize;
	float		scale;
	int			projection;
}				t_camera;

typedef struct s_fdf
{
	t_map		*map;
	t_camera	*camera;
	mlx_t		*mlx;
	mlx_image_t	*image;
}				t_fdf;

// ========== errors_and_free ==========
void		exit_msg(int msg);
void		free_fdf(t_fdf *fdf);
void		free_split(char **split);

// ========== map ==========
void		check_map(char *map);

// ========== init ==========
t_fdf		*init_fdf(char *map);
float		get_scale(t_fdf *fdf);

// ========== parse ==========
t_map		*parse(char *map);

// ========== render ==========
void		render(void *param);

// ========== colors ==========
int			ft_hex_to_int(char *hexa);
uint32_t	put_alpha(uint32_t color);
uint32_t	invert_color(uint32_t color);
void		invert_background(t_fdf *fdf);

// ========== parse_utils ==========
void		convert_map(t_map *map, char *map_id);
void		center_map(t_map *map);
void		centralize(t_fdf *fdf, t_coordinates *start, t_coordinates *end);

// ========== render_utils ==========
void		scale(t_fdf *fdf, t_coordinates *start, t_coordinates *end);
void		draw_line(t_fdf *fdf, t_coordinates start, t_coordinates end);
void		isometry(t_fdf *fdf, t_coordinates *start, t_coordinates *end);

// ========== draw_line_utils ==========
void		axis_y_line(t_fdf *fdf, t_coordinates start, t_coordinates end);
void		axis_x_line(t_fdf *fdf, t_coordinates start, t_coordinates end);
void		diag_y_line(t_fdf *fdf, t_draw_line line, t_coordinates start,
				t_coordinates end);
void		diag_x_line(t_fdf *fdf, t_draw_line line, t_coordinates start,
				t_coordinates end);
void		put_pixel(t_fdf *fdf, int x, int y, uint32_t color);

// ========== keyboard_command ==========
void		set_camera(t_fdf *fdf, int projection_type);
void		zoom(t_fdf *fdf);
void		rotation(t_fdf *fdf);
void		z_scale(t_fdf *fdf);
void		movement(t_fdf *fdf);

// ========== rotation ==========
void		rotate_x(t_fdf *fdf, t_coordinates *start, t_coordinates *end,
				float angle);
void		rotate_y(t_coordinates *start, t_coordinates *end, float angle);
void		rotate_z(t_coordinates *start, t_coordinates *end, float angle);

#endif