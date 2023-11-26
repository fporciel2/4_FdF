/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_generate_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 10:52:16 by fporciel          #+#    #+#             */
/*   Updated: 2023/11/26 11:26:17 by fporciel         ###   ########.fr       */
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

static int	fdf_set_point(t_fdf *fdf, int x, int y)
{
}

int	fdf_generate_list(t_fdf *fdf, int x, int y)
{
	if ((x == 0) && (y == 0))
	{
		fdf->lst = (t_map *)malloc(sizeof(t_map));
		fdf->cur = fdf->lst;
	}
	else
	{
		fdf->cur->next = (t_map *)malloc(sizeof(t_map));
		fdf->cur = fdf->cur->next;
	}
	if (fdf->cur == NULL)
		return (fdf_generic_error(fdf));
	return (fdf_set_point(fdf, x, y));
}
