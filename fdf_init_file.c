/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:30:30 by fporciel          #+#    #+#             */
/*   Updated: 2023/06/02 15:56:33 by fporciel         ###   ########.fr       */
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

#include "./fdf.h"

static int	init_fdf_close_all(int fd)
{
	int	control;

	control = close(fd);
	return (0);
}

static int	init_effectively_count(int fd, char swap, int num, ssize_t count)
{
	char	buffer;
	int		time;

	time = 0;
	while (count > 0)
	{
		count = read(fd, &buffer, 1);
		if (count < 0)
			return (init_fdf_close_all(fd));
		if ((time == 0) || ((buffer != 10) && (swap == 10)))
			num++;
		time++;
		swap = buffer;
	}
	time = close(fd);
	if (time < 0)
		return (0);
	return (num);
}

static int	init_count_fdf_lines(int fd)
{
	int		num_of_lines;
	char	swap;
	ssize_t	count;

	num_of_lines = ft_printf("Counting number of lines...");
	num_of_lines = 0;
	swap = 0;
	count = 1;
	num_of_lines = init_effectively_count(fd, swap, num_of_lines, count);
	if (num_of_lines == 0)
		return (0);
	return (num_of_lines);
}

int	fdf_init_file(int fd, int width, int height, char *argvone)
{
	static t_fdf_data	data;

	data.garbage = ft_printf("Initializing file and data...");
	data.num_of_lines = init_count_fdf_lines(fd);
	if (data.num_of_lines == 0)
		return (0);
	fd = open(argvone, O_RDONLY);
	if (fd >= 0)
	{
		data.fd = fd;
		data.width = width;
		data.height = height;
		return (fdf_start_process(data));
	}
	else
	{
		perror("An error occurred!");
		return (0);
	}
}
