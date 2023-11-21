/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:57:57 by fporciel          #+#    #+#             */
/*   Updated: 2023/11/21 15:30:16 by fporciel         ###   ########.fr       */
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

static int	fdf_generate_image(t_fdf *fdf)
{
	fdf->img = mlx_new_image(fdf->dsp, IMGX, IMGY);
	if (fdf->img == NULL)
		fdf->imap = fdf_generic_error(fdf);
	fdf->data = mlx_get_data_addr(fdf->img, &(fdf->bits),
			&(fdf->row), &(fdf->endian));
	if (fdf->data == NULL)
		fdf->imap = fdf_generic_error(fdf);
	//mlx_put_image_to_window(fdf->display, fdf->window, fdf->image, 0, 0);
	return (0);
}
/*
static int	fdf_hook_events(int keysym, t_fdf *fdf)
{
	if (keysym == 0)
	{
		mlx_hook(fdf->win, KeyPress,
			KeyPressMask, fdf_hook_events, fdf);
		mlx_hook(fdf->win, DestroyNotify,
			ButtonPressMask, fdf_normal_exit, fdf);
	}
	else if (keysym == XK_Escape)
		fdf->imap = fdf_normal_exit(fdf);
	return (0);
}*/

static int	fdf_hook(int keysym, t_fdf *fdf)

int	fdf_mlx(t_fdf *fdf)
{
	fdf->dsp = mlx_init();
	if (fdf->dsp == NULL)
		fdf->imap = fdf_generic_error(fdf);
	fdf->win = mlx_new_window(fdf->dsp, WINX, WINY, "FDF");
	if (fdf->win == NULL)
		fdf->imap = fdf_generic_error(fdf);
	mlx_hook(fdf->win, KeyPress, KeyPressMask, fdf_hook, fdf);
	mlx_hook(fdf->win, DestroyNotify, ButtonPressMask, fdf_normal_exit, fdf);
	//fdf_hook_events(0, fdf);
	fdf_generate_image(fdf);
	mlx_loop(fdf->dsp);
	return (fdf->imap);
}
