/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_prepare_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 13:52:15 by fporciel          #+#    #+#             */
/*   Updated: 2023/11/19 15:17:17 by fporciel         ###   ########.fr       */
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
	ssize_t	imap;

	imap = fdf->width;
	while (imap != fdf->imap)
	{
		free(((fdf->map)[imap]));
		((fdf->map)[imap]) = NULL;
		imap--;
	}
	free(fdf->map);
	fdf->map = NULL;
	return (0);
}

static void	fdf_continue_fill_map(t_fdf *fdf, ssize_t j)
{
	ssize_t	i;

	fdf->spline = ft_split(fdf->line, 32 );
	if (fdf->spline == NULL)
		fdf_generic_error(fdf);
	i = 0;
	while (((fdf->spline)[i]) != NULL)
	{
		((fdf->map)[j][i]) = ft_atoi(((fdf->spline)[i]));
		i++;
	}
	fdf->spline = fdf_free_split(fdf->spline);
}

static void	fdf_fill_map(t_fdf *fdf, char *name)
{
	ssize_t	j;

	j = 0;
	fdf->stop = 1;
	fdf->fd = open(name, O_RDONLY);
	if (fdf->fd < 0)
		fdf_generic_error(fdf);
	while (fdf->stop != 0)
	{
		errno = 0;
		fdf->line = get_next_line(fdf->fd);
		if ((fdf->line == NULL) && ((errno == ENOMEM)
				|| (errno == EAGAIN) || (errno == EWOULDBLOCK)
				|| (errno == EBADF) || (errno == EFAULT) || (errno == EINTR)
				|| (errno == EINVAL) || (errno == EIO)))
			fdf_generic_error(fdf);
		if (fdf->line == NULL)
			fdf->stop = 0;
		fdf_continue_fill_map(fdf, j);
		free(fdf->line);
		j++;
	}
	if (close(fdf->fd) < 0)
		fdf_generic_error(fdf);
}

int	**fdf_prepare_map(t_fdf *fdf, char *name)
{
	fdf->map = (int **)malloc(sizeof(int *) * (fdf->height + 1));
	if (fdf->map == NULL)
		return (&(&fdf_generic_error(fdf)));
	((fdf->map)[fdf->height]) = NULL;
	fdf->imap = fdf->height;
	while (fdf->imap >= 0)
	{
		((fdf->map)[fdf->imap]) = (int *)malloc(sizeof(int) * (fdf->width + 1));
		if (((fdf->map)[fdf->imap]) == NULL)
			return (&(&fdf_generic_error(fdf)));
		(fdf->imap)--;
	}
	fdf_fill_map(fdf, name);
	return (fdf->map);
}
