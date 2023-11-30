/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_generate_model.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 10:01:25 by fporciel          #+#    #+#             */
/*   Updated: 2023/11/30 10:42:11 by fporciel         ###   ########.fr       */
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

static int	fdf_vertical_line(t_fdf *fdf, int x, int y)
{
	fdf->x0 = fdf_get_vert_x0(fdf, x, y);
	fdf->y0 = fdf_get_vert_y0(fdf, x, y);
	fdf->x1 = fdf_get_vert_x1(fdf, x, y);
	fdf->y1 = fdf_get_vert_y1(fdf, x, y);
	if (y != 0)
		fdf->imap = fdf_bresenham(fdf, fdf->x1, fdf->y1);
	fdf->imap = fdf_clean_line_parameters(fdf);
	return (fdf->imap);
}

int	fdf_generate_model(t_fdf *fdf)
{
	int	x;
	int	y;

	fdf->dsty = (ENDY - STARTY) / fdf->height;
	fdf->dstx = (ENDX - STARTX) / fdf->width;
	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			fdf->x0 = fdf_get_horizon_x0(fdf, x, y);
			fdf->y0 = fdf_get_horizon_y0(fdf, x, y);
			fdf->x1 = fdf_get_horizon_x1(fdf, x, y);
			fdf->y1 = fdf_get_horizon_y1(fdf, x, y);
			if (x != 0)
				fdf->imap = fdf_bresenham(fdf, fdf->x1, fdf->y1);
			fdf->imap = fdf_clean_line_parameters(fdf);
			fdf->imap = fdf_vertical_line(fdf, x, y);
			x++;
		}
		y++;
	}
	return (fdf->imap);
}
