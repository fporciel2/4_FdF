/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 08:47:51 by fporciel          #+#    #+#             */
/*   Updated: 2023/05/29 14:26:14 by fporciel         ###   ########.fr       */
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

typedef struct	s_fdf_data
{
	void		*mlx;
	void		*window;
}				t_fdf_data;

typedef struct			s_map_data
{
	struct s_map_data	*map_start;
	struct s_map_data	*right_node;
	struct s_map_data	*left_node;
	struct s_map_data	*up_node;
	struct s_map_data	*bot_node;
	long long int		node_axis;
	long long int		node_ordinate;
	long long int		node_altitude;
	long long int		node_position_x;
	long long int		node_position_y;
	long long int		node_position_z;
}						t_map_data;

typedef struct		s_camera_data
{
	long long int	eye_x;
	long long int	eye_y;
	long long int	eye_z;
	t_map_data		*lookat_point;
	long long int	up_vector;
	long long int	right_vector;
}					t_camera_data;

int		fdf_start_process(int fd, int width, int height);
void	fdf_open_window(int width, int height, int fd);
int		fdf_close_window(void *param);
int		fdf_esc_window(int keycode, void *param);
int		fdf_error(void *param);
void	*fdf_free_null(void *param, void *other_param);
void	*fdf_error_free_null(void *param, void *other_param);

#endif
