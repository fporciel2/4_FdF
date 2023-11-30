/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bresenham.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:48:59 by fporciel          #+#    #+#             */
/*   Updated: 2023/11/30 19:30:54 by fporciel         ###   ########.fr       */
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

static int	fdf_draw_line_loop(t_fdf *fdf, int x1, int y1)
{
	while (1)
	{
		if ((fdf->x0 > 0) && (fdf->x0 < WINX) && (fdf->y0 > 0) && (fdf->y0 < WINY))
			fdf_put_pixel(fdf, fdf->x0, fdf->y0, fdf->color);
		if ((fdf->x0 == x1) && (fdf->y0 == y1))
			break ;
		fdf->e2 = 2 * fdf->e;
		if (fdf->e2 >= fdf->dy)
		{
			if (fdf->x0 == x1)
				break ;
			fdf->e = fdf->e + fdf->dy;
			fdf->x0 = fdf->x0 + fdf->sx;
		}
		if (fdf->e2 <= fdf->dx)
		{
			if (fdf->y0 == y1)
				break ;
			fdf->e = fdf->e + fdf->dx;
			fdf->y0 = fdf->y0 + fdf->sy;
		}
	}
	return (0);
}

int	fdf_bresenham(t_fdf *fdf, int x1, int y1)
{
	fdf->dx = fdf_absval(x1 - fdf->x0);
	if (fdf->x0 < x1)
		fdf->sx = 1;
	else
		fdf->sx = -1;
	fdf->dy = -(fdf_absval(y1 - fdf->y0));
	if (fdf->y0 < y1)
		fdf->sy = 1;
	else
		fdf->sy = -1;
	fdf->e = fdf->dx + fdf->dy;
	return (fdf_draw_line_loop(fdf, x1, y1));
}
