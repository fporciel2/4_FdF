/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:04:10 by fporciel          #+#    #+#             */
/*   Updated: 2023/11/19 14:26:32 by fporciel         ###   ########.fr       */
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

typedef struct s_fdf
{
	void	*dsp;
	void	*win;
	void	*img;
	char	*data;
	char	*line;
	char	**spline;
	int		**map;
	int		bits;
	int		llen;
	int		endian;
	int		fd;
	int		width;
	int		height;
	int		stop;
	ssize_t	imap;
}			t_fdf;

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
int		fdf_free_map(t_fdf *fdf, int param);

#endif
