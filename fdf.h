/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:04:10 by fporciel          #+#    #+#             */
/*   Updated: 2023/11/26 14:13:31 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
 * FdF is a general-purpose Computer-Aided Design (CAD) program meant to analyze
 * and render a properly formatted map of a landscape.
 *
 * Copyright (C) 2023  Federico Porciello
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef FDF_H
# define FDF_H

# include "./1_libft/libft.h"
# include "./2_ft_printf/ft_printf.h"
# include "./minilibx-linux/mlx.h"
# include "./minilibx-linux/mlx_int.h"
# include <stdbool.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>

# define WINX	1920
# define WINY	1080

# define IMGX	1920
# define IMGY	1080

# define STARTX	480
# define STARTY	270

# define ENDX	1440
# define ENDY	810

# define WHITE	0xffffff
# define RED	0xe80c0c

/*fdf->dsty(fdf->dstx) == (ENDY(ENDX) - STARTY(STARTX)) / fdf->height(fdf->width)*/

typedef struct s_map
{
	int	x;
	int	y;
	int	z;
}		t_map;

typedef struct s_fdf
{
	void			*dsp;
	void			*win;
	void			*img;
	char			*data;
	char			*line;
	char			**spline;
	int				**map;
	int				bits;
	int				row;
	int				endian;
	int				fd;
	int				width;
	int				height;
	int				dsty;
	int				dstx;
	int				stop;
	ssize_t			imap;
	ssize_t			c;
	ssize_t			i;
	ssize_t			s;
	int				x;
	int				x0;
	int				x1;
	int				y;
	int				y0;
	int				y1;
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				e;
	int				e2;
	float			angle;
	struct s_map	*lst;
	struct s_map	*cur;
}					t_fdf;

int		fdf_invalid_argument_error(void);
int		fdf_nonexistent_file_error(void);
int		fdf_generic_error(t_fdf *fdf);
int		fdf_get_height_and_width(t_fdf *fdf, char *argvi);
int		**fdf_prepare_map(t_fdf *fdf, char *name);
int		fdf_put_pixel(void);
int		fdf_memory_cleaner(t_fdf *fdf);
int		fdf_draw_line(t_fdf *fdf);
int		fdf_draw_lines(t_fdf *fdf);
int		fdf_graphic_management(t_fdf *fdf);
int		fdf_deal_key(t_fdf *fdf);
int		fdf_normal_exit(t_fdf *fdf);
char	**fdf_free_split(char **split);
int		fdf_free_map(t_fdf *fdf);
int		fdf_mlx(t_fdf *fdf);
int		fdf_max(int a, int b);
int		fdf_absval(int a);
void	fdf_put_pixel(t_fdf *fdf, int x, int y, int color);
int		fdf_bresenham(t_fdf *fdf, int x1, int y1);
int		fdf_generate_model(t_fdf *fdf);
int		fdf_generate_list(t_fdf *fdf, int x, int y);
int		fdf_draw_model(t_fdf *fdf, int x, int y);
int		fdf_cancel_list(t_fdf *fdf);

#endif
