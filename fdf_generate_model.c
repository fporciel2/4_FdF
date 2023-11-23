/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_generate_model.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:06:56 by fporciel          #+#    #+#             */
/*   Updated: 2023/11/23 16:19:11 by fporciel         ###   ########.fr       */
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
	int	x1;
	int	y1;

	y = 0;
	while (y < fdf->height)
	{
		x = 0;
	}
}

int	fdf_generate_model(t_fdf *fdf)
{
	if ((fdf->x0 == 0) && (fdf->y0 == 0) && (fdf->dx == 0) && (fdf->dy == 0)
			&& (fdf->sx == 0) && (fdf->sy == 0) && (fdf->e == 0) && (fdf->e2 == 0))
		fdf->imap = fdf_generate_basic_model(fdf);
	return (0);
}
