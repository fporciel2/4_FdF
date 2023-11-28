/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_generate_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 10:52:16 by fporciel          #+#    #+#             */
/*   Updated: 2023/11/28 11:26:55 by fporciel         ###   ########.fr       */
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

#include "fdf.h"

/*
 	if (fdf->cur->z < 0)
		fdf->cur->y -= fdf->cur->z;
	else
		fdf->cur->y += fdf->cur->z;
 */
static int	fdf_set_point(t_fdf *fdf, int x, int y)
{
	if (y == 0)
		fdf->cur->y = STARTY;
	else
		fdf->cur->y = y * fdf->dsty;
	if (x == 0)
		fdf->cur->x = STARTX;
	else
		fdf->cur->x = x * fdf->dstx;
	fdf->cur->z = (fdf->map)[y][x];
	return (0);
}

int	fdf_generate_list(t_fdf *fdf, int x, int y)
{
	if ((x == 0) && (y == 0))
	{
		fdf->lst = (t_map *)malloc(sizeof(t_map));
		if (fdf->lst == NULL)
			return (fdf_generic_error(fdf));
		fdf->cur = fdf->lst;
		fdf->cur->next = NULL;
	}
	else
	{
		fdf->cur->next = (t_map *)malloc(sizeof(t_map));
		if (fdf->cur->next == NULL)
			return (fdf_generic_error(fdf));
		fdf->cur = fdf->cur->next;
		fdf->cur->next = NULL;
	}
	return (fdf_set_point(fdf, x, y));
}
