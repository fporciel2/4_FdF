/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_prepare_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 13:52:15 by fporciel          #+#    #+#             */
/*   Updated: 2023/11/21 14:44:20 by fporciel         ###   ########.fr       */
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

int	fdf_free_map(t_fdf *fdf)
{
	fdf->imap = 0;
	while (fdf->map && ((fdf->map)[fdf->imap] != NULL))
	{
		free((fdf->map)[fdf->imap]);
		(fdf->map)[fdf->imap] = NULL;
		(fdf->imap)++;
	}
	free(fdf->map);
	fdf->map = NULL;
	return ((int)fdf->imap);
}

static int	**fdf_close_map_prep(t_fdf *fdf)
{
	if (close(fdf->fd) < 0)
		fdf_generic_error(fdf);
	return (fdf->map);
}

static int	*fdf_count_split_and_allocate(t_fdf *fdf)
{
	int	lol;

	fdf->s = 0;
	while ((fdf->spline)[fdf->s] != NULL)
		(fdf->s)++;
	(fdf->map)[fdf->c] = (int *)malloc(sizeof(int) * fdf->s);
	if ((fdf->map)[fdf->c] == NULL)
		lol = fdf_generic_error(fdf);
	(void)lol;
	return ((fdf->map)[fdf->c]);
}

static int	fdf_split_line_and_fill(t_fdf *fdf, char *line, int result)
{
	fdf->spline = ft_split(line, 32);
	if (fdf->spline == NULL)
		result = fdf_generic_error(fdf);
	fdf->i = 0;
	(fdf->map)[fdf->c] = fdf_count_split_and_allocate(fdf);
	while ((fdf->spline)[fdf->i] != NULL)
	{
		(fdf->map)[fdf->c][fdf->i] = ft_atoi((fdf->spline)[fdf->i]);
		(fdf->i)++;
	}
	(fdf->map)[(fdf->c) + 1] = NULL;
	fdf->spline = fdf_free_split(fdf->spline);
	free(fdf->line);
	fdf->line = NULL;
	return (result);
}

int	**fdf_prepare_map(t_fdf *fdf, char *name)
{
	int	result;

	fdf->map = (int **)malloc(sizeof(int *) * (fdf->height + 1));
	fdf->fd = open(name, O_RDONLY);
	if ((fdf->map == NULL) || (fdf->fd < 0))
		result = fdf_generic_error(fdf);
	fdf->c = -1;
	while (1)
	{
		(fdf->c)++;
		(fdf->map)[fdf->c] = NULL;
		errno = 0;
		fdf->line = get_next_line(fdf->fd);
		if ((fdf->line == NULL) && ((errno == ENOMEM)
				|| (errno == EAGAIN) || (errno == EWOULDBLOCK)
				|| (errno == EBADF) || (errno == EFAULT) || (errno == EINTR)
				|| (errno == EINVAL) || (errno == EIO)))
			result = fdf_generic_error(fdf);
		if (fdf->line != NULL)
			result = fdf_split_line_and_fill(fdf, fdf->line, result);
		else
			break ;
	}
	(void)result;
	return (fdf_close_map_prep(fdf));
}
