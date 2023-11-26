/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_model.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 14:37:29 by fporciel          #+#    #+#             */
/*   Updated: 2023/11/26 15:28:25 by fporciel         ###   ########.fr       */
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

static t_map	*fdf_find_correct_point(t_fdf *fdf, int x, int y, t_map *tmp)
{
	int	py;
	int		px;
	int		ty;

	py = y - 1;
	ty = 0;
	px = -1;
	while ((ty != py) && (px != x))
	{
		if (px == fdf->width)
		{
			px = -1;
			ty++;
		}
		tmp = tmp->next;
	}
}

static int	fdf_ordinate_connection(t_fdf *fdf, int x, int y)
{
	t_map	*tmp;

	tmp = fdf->lst;
	tmp = fdf_find_correct_point(fdf, x, y, tmp);
	fdf->x0 = tmp->x;
	fdf->y0 = tmp->y;
	fdf->x1 = fdf->curr->x;
	fdf->y1 = fdf->curr->y;
	fdf->imap = fdf_bresenham(fdf, fdf->x1, fdf->y1);
	return (fdf->imap);
}

static int	fdf_axis_connection(t_fdf *fdf)
{
	t_map	*tmp;

	tmp = fdf->lst;
	while (tmp && (tmp->next != fdf->cur))
		tmp = tmp->next;
	fdf->x0 = tmp->x;
	fdf->y0 = tmp->y;
	fdf->x1 = fdf->curr->x;
	fdf->y1 = fdf->curr->y;
	fdf->imap = fdf_bresenham(fdf, fdf->x1, fdf->y1);
	return (fdf->imap);
}

static int	fdf_project_point(t_fdf *fdf)
{
	int	px;
	int	py;

	px = (int)((fdf->cur->x - fdf->cur->y) * cos(fdf->angle));
	py = (int)((fdf->cur->x + fdf->cur->y) * sin(angle) - fdf->cur->z);
	fdf->cur->x = px;
	fdf->cur->y = py;
	return (0);
}

int	fdf_draw_model(t_fdf *fdf, int x, int y)
{
	fdf->imap = fdf_project_point(fdf);
	if (x != 0)
		fdf->imap = fdf_axis_connection(fdf);
	fdf->imap = fdf_clean_line_parameters(fdf);
	if (y != 0)
		fdf->imap = fdf_ordinate_connection(fdf, x, y);
	fdf->imap = fdf_clean_line_parameters(fdf);
	return (fdf->imap);
}
