/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_start_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 08:58:28 by fporciel          #+#    #+#             */
/*   Updated: 2023/05/31 14:56:50 by fporciel         ###   ########.fr       */
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

#include "./libfdf.h"

static void	start_fdf_clean(t_fdf_data data, t_point_data *starting_point)

static t_point_data	start_fdf_map(t_fdf_data data, t_point_data *first_point)

static t_point_data	start_process_fdf_first_point(int fd, t_fdf_data data)
{
	t_point_data	*first_point;
	char			*first_line;
	char			**first_sequence;

	first_line = get_next_line(fd);
	if (first_line == NULL)
		return (NULL);
	first_sequence = ft_split(first_line, 32);
	free(first_line);
	if (first_sequence == NULL)
		return (NULL);
	first_point = (t_point_data *)malloc(sizeof(t_point_data));
	if (first_point == NULL)
		return (NULL);
	return (start_fdf_map(data, first_point));
}

static t_point_data	start_process_fdf_map(int fd, t_fdf_data data)
{
	t_point_data	*starting_point;
	t_point_data	*next_point;

	starting_point = start_process_fdf_first_point(fd, data);
	if (starting_point == NULL)
		return (NULL);
	next_point = NULL;
	next_point = fdf_map(data, starting_point, next_point);
	if (next_point == NULL)
		return (NULL);
	return (starting_point);
}

int	fdf_start_process(int fd, int width, int height)
{
	static t_fdf_data	data;
	static t_point_data	*starting_point;
	int					result;

	data.width = width;
	data.height = height;
	data.fd = fd;
	starting_point = start_process_fdf_map(fd, data);
	if (starting_point == NULL)
	{
		perror("The map is not valid!");
		return (0);
	}
	result = fdf_open_window(data, starting_point);
	start_process_fdf_clean(starting_point, data);
	return (result);
}
