/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:56:39 by fporciel          #+#    #+#             */
/*   Updated: 2023/05/27 08:36:01 by fporciel         ###   ########.fr       */
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

static int	check_fdf_file_string(char *argvone)
{
	size_t	len;
	int		fd;

	len = ft_strlen(argvone);
	if ((argvone[len - 1] != 102) || (argvone[len - 2] != 100)
		|| (argvone[len - 3] != 102) || (argvone[len - 4] != 46))
		return (0);
	fd = open(argvone, O_RDONLY);
	if (fd != -1)
		return (fd);
	else
	{
		perror("The file name you passed to the program is not valid!");
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
		fd = check_fdf_file_string(argv[1]);
		if (fd == 0)
			return (0);
		if (argc == 4)
		{
			width = ft_atoi(argv[2]);
			height = ft_atoi(argv[3]);
		}
		fdf_start_process(fd, width, height);
	}
	return (0);
}
