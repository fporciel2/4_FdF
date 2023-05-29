/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_start_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 08:58:28 by fporciel          #+#    #+#             */
/*   Updated: 2023/05/29 15:46:34 by fporciel         ###   ########.fr       */
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

static t_map_data	store_map_data(size_t count, char *line, t_map_data *node)
{
	char	**splitted_line;

	splitted_line = ft_split(line, 32);
	if (splitted_line == NULL)
		fdf_error_free_null(line, node, splitted_line);
}

int	fdf_start_process(int fd, int width, int height)
{
	char				*line;
	size_t				count;
	static t_map_data	*node;

	count = 0;
	line = (char *)malloc(sizeof(char));
	if (line == NULL)
		return (fdf_error(NULL));
	line[0] = 0;
	while (line != NULL)
	{
		line = fdf_free_null(line, NULL);
		line = get_next_line(fd);
		if (line != NULL)
		{
			count++;
			node = store_map_data(count, line, node);
		}
		else
			return (fdf_error(NULL));
	}
	fdf_open_window(width, height, node);
	return (0);
}
