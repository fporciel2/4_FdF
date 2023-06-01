/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:56:39 by fporciel          #+#    #+#             */
/*   Updated: 2023/06/01 13:26:30 by fporciel         ###   ########.fr       */
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

#include "fdf.h"

static int	main_check_fdf_window_param(char *width, char *height)
{
	size_t	count;

	count = 0;
	while (width[count])
	{
		if ((width[count] < 48) || (width[count] > 57))
			return (0);
		count++;
	}
	count = 0;
	while (height[count])
	{
		if ((height[count] < 48) || (height[count] > 57))
			return (0);
		count++;
	}
	return (1);
}

static int	main_check_fdf_file_string(char *argvone)
{
	size_t	len;
	int		fd;

	len = ft_strlen(argvone);
	if ((argvone[len - 1] != 102) || (argvone[len - 2] != 100)
		|| (argvone[len - 3] != 102) || (argvone[len - 4] != 46))
	{
		perror("Invalid filename!");
		return (0);
	}
	fd = open(argvone, O_RDONLY);
	if (fd != -1)
		return (fd);
	else
	{
		perror("Invalid filename!");
		return (0);
	}
}

int	main(int argc, char *argv[])
{
	int	width;
	int	height;
	int	fd;

	width = DEFAULT_WIDTH;
	height = DEFAULT_HEIGHT;
	if ((argc >= 2) && (argc != 3) && (argc < 5))
	{
		fd = main_check_fdf_file_string(argv[1]);
		if (fd == 0)
			return (0);
		if (argc == 4)
		{
			if (main_check_fdf_window_param(argv[2], argv[3]))
			{
				width = ft_atoi(argv[2]);
				height = ft_atoi(argv[3]);
			}
		}
		return (fdf_start_process(fd, width, height));
	}
	perror("No filename or wrong arguments!");
	return (0);
}
