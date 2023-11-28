/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_generate_model.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:06:56 by fporciel          #+#    #+#             */
/*   Updated: 2023/11/28 14:04:16 by fporciel         ###   ########.fr       */
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

static int	fdf_generate_basic_model(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			fdf->x = x;
			fdf->y = y;
			fdf->imap = fdf_generate_list(fdf, x, y);
			fdf->imap = fdf_draw_model(fdf, x, y);
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
	fdf->angle = 0.8;
	if ((fdf->x0 == 0) && (fdf->y0 == 0) && (fdf->dx == 0) && (fdf->dy == 0)
			&& (fdf->sx == 0) && (fdf->sy == 0) && (fdf->e == 0) && (fdf->e2 == 0))
		fdf->imap = fdf_generate_basic_model(fdf);
	return (0);
}
