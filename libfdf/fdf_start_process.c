/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_start_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 08:58:28 by fporciel          #+#    #+#             */
/*   Updated: 2023/06/02 16:01:19 by fporciel         ###   ########.fr       */
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

static void	*cleaner(char *line, t_point_data *start, char **splitted_line)
{
	size_t			count;
	t_point_data	*swap;

	count = 0;
	if (line != NULL)
		free(line);
	if (splitted_line != NULL)
	{
		while (splitted_line[count] != NULL)
			free(splitted_line[count++]);
		free(splitted_line);
	}
	if (start != NULL)
	{
		while (start != NULL)
		{
			swap = start;
			start = swap->next_point;
			free(swap);
		}
		start = NULL;
	}
	return (NULL);
}

static t_point_data	*fdf_node(t_point_data *start, char *ptr, t_fdf_data data)
{
	t_point_data	*next;

	next = start;
	if (start == NULL)
	{
		start = (t_point_data *)malloc(sizeof(t_point_data));
		if (start == NULL)
			return (NULL);
		start->map_x = data.max_x;
		start->map_y = data.max_y;
		start->map_z = ft_atoi(ptr);
		start->next_point = NULL;
		return (start);
	}
	while (next != NULL)
		next = next->next_point;
	next = (t_point_data *)malloc(sizeof(t_point_data));
	if (next == NULL)
		return (NULL);
	next->map_x = data.max_x;
	next->map_y = data.max_y;
	next->map_z = ft_atoi(ptr);
	next->next_point = NULL;
	return (next);
}

static t_point_data	*fdf_map(t_fdf_data data, t_point_data *start, char *line)
{
	t_point_data	*next;
	char			**splitted_line;
	size_t			count;

	count = 0;
	while (line[count] != 10)
	{
		if ((line[count] != 32) && ((line[count] < 48) || (line[count] > 57)))
			return (NULL);
		count++;
	}
	splitted_line = ft_split(line, 32);
	if (splitted_line == NULL)
		return (NULL);
	count = 0;
	while (splitted_line[count] != NULL)
	{
		next = fdf_node(start, splitted_line[count], data);
		if (next == NULL)
			return (cleaner(NULL, start, splitted_line));
		count++;
		data.max_x = count;
	}
	splitted_line = cleaner(NULL, NULL, splitted_line);
	return (start);
}

static t_point_data	*fdf_start_parse(t_fdf_data data, t_point_data *first_node)
{
	char	*line;
	int		count;

	line = (char *)malloc(sizeof(char));
	if (line == NULL)
		return (NULL);
	line[0] = 0;
	count = 0;
	while (line != NULL)
	{
		free(line);
		line = get_next_line(data.fd);
		if ((line == NULL) && (count != data.num_of_lines))
			return (cleaner(NULL, first_node, NULL));
		if (line != NULL)
		{
			count++;
			data.max_y = count;
			first_node = fdf_map(data, first_node, line);
			if (first_node == NULL)
				return (cleaner(line, NULL, NULL));
		}
	}
	return (first_node);
}

int	fdf_start_process(t_fdf_data data)
{
	static t_fdf_data	data;
	static t_point_data	*first_node;
	int					result;

	result = ft_printf("Starting the process...");
	first_node = fdf_start_parse(data, first_node);
	if (first_node == NULL)
	{
		perror("Failed to read the map.");
		return (0);
	}
	result = fdf_open_window(data, first_node);
	return (result);
}
