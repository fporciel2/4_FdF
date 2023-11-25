/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_generate_model.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:06:56 by fporciel          #+#    #+#             */
/*   Updated: 2023/11/25 17:28:30 by fporciel         ###   ########.fr       */
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

static int	fdf_project_and_connect_y(t_fdf *fdf, int x, int y)

static int	fdf_project_and_connect_x(t_fdf *fdf, int x, int y)
{
	int	px;
	int	py;

	fdf->angle = 0.8;
	if (map[y][x] >= 0)
		fdf->y0 -= map[y][x];
	else
		fdf->y0 += map[y][x];
	px = (fdf->x0 - fdf->y0) * cos(fdf->angle);
	py = (fdf->x0 + fdf->y0) * sin(fdf->angle);
	fdf->x0 = px;
	fdf->y0 = py;
	if (x == 0)
		return (0);
	else
		return (fdf_bresenham(fdf, fdf->x1, fdf->y1));
}

static int	fdf_set_points_and_trace_lines(t_fdf *fdf, int x, int y)
{
	if (x == 0)
		fdf->x0 = STARTX;
	else
		fdf->x0 = fdf->xp + fdf->dstx;
	if (y == 0)
		fdf->y0 = STARTY;
	else
	{
		if (x == 0)
			fdf->y0 = fdf->yp + fdf->dsty;
	}
	fdf->xp = fdf->x0;
	if (x == (fdf->width - 1))
		fdf->yp = fdf->y0;
	fdf->imap = fdf_project_and_connect_x(fdf, x, y);
	if (y != 0)
		fdf->imap = fdf_project_and_connect_y(fdf, x, y);
	fdf->x1 = fdf->x0;
	fdf->y1 = fdf->y0;
	return (fdf->imap);
}

static int	fdf_generate_basic_model(t_fdf *fdf)
{
	int	x;
	int	y;
	int	x1;
	int	y1;

	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			fdf->imap = fdf_set_points_and_trace_lines(fdf, x, y);
			x++;
		}
		y++;
	}
	return (fdf->imap);
}

int	fdf_generate_model(t_fdf *fdf)
{
	fdf->dsty =  (ENDY - STARTY) / fdf->height;
	fdf->dstx = (ENDX - STARTX) / fdf->width;
	if ((fdf->x0 == 0) && (fdf->y0 == 0) && (fdf->dx == 0) && (fdf->dy == 0)
			&& (fdf->sx == 0) && (fdf->sy == 0) && (fdf->e == 0) && (fdf->e2 == 0))
		fdf->imap = fdf_generate_basic_model(fdf);
	return (0);
}
