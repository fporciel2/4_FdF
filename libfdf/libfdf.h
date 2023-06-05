/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 08:47:51 by fporciel          #+#    #+#             */
/*   Updated: 2023/06/05 16:50:51 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* 
* This software is made available to anyone who wants to retrace the 
* author's learning path through the projects of school 42.
* Copyright (C) 2023  fporciel
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
*
* You can contact the author at: 
*- fporciel@student.42roma.it
*/

#ifndef LIBFDF_H
# define LIBFDF_H
# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <errno.h>

typedef struct	s_fdf_data
{
	void		*mlx;
	void		*window;
	void		*img;
	int			width;
	int			height;
	int			img_width;
	int			img_height;
	int			fd;
	int			max_x;
	int			max_y;
	int			num_of_lines;
	int			garbage;
}				t_fdf_data;

typedef struct			s_point_data
{
	int					map_x;
	int					map_y;
	int					map_z;
	double				display_x;
	double				display_y;
	double				display_z;
	struct s_point_data	*next_point;
}						t_point_data;

typedef struct	s_camera_data
{
	int			eye_x;
	int			eye_y;
	double		eye_z;
}				t_camera_data;

int	fdf_start_process(t_fdf_data data);
int	fdf_open_window(t_fdf_data *data, t_point_data **first_point);

#endif
