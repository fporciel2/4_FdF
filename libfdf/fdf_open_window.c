/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_open_window.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 09:35:14 by fporciel          #+#    #+#             */
/*   Updated: 2023/06/05 16:53:44 by fporciel         ###   ########.fr       */
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

static int	fdf_open_clean(t_point_data ***first_node, int param)
{
	t_point_data	*swap;

	while ((**first_node) != NULL)
	{
		swap = **first_node;
		**first_node = swap->next_point;
		free(swap);
		if (**first_node == NULL)
			*first_node = NULL;
	}
	if (param == 1)
		perror("Sorry :( an error occurred!");
	return (0);
}

int	fdf_open_connection(t_fdf_data *dt, t_point_data **first_node)
{
	(*dt).img_width = (*dt).width / 2;
	(*dt).img_height = (*dt).height / 2;
	(*dt).mlx = mlx_init();
	if ((*dt).mlx == NULL)
		return (fdf_open_clean(&first_node, 1));
	(*dt).win = mlx_new_window((*dt).mlx, (*dt).width, (*dt).height, "FdF");
	if ((*dt).win == NULL)
		return (fdf_open_clean(&first_node, 1));
	(*dt).img = mlx_new_image((*dt).mlx, (*dt).img_width, (*dt).img_height);
	if ((*dt).img == NULL)
		return (fdf_open_clean(&first_node, 1));
	(*dt).garbage = fdf_open_event_managing(dt, *first_node);
	if ((*dt).garbage == 0)
		return (fdf_open_clean(&first_node, 1));
	mlx_loop(data.mlx);
	return (fdf_open_clean(&first_node, 0));
}
