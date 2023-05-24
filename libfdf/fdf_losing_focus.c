/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_losing_focus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:43:44 by fporciel          #+#    #+#             */
/*   Updated: 2023/05/24 18:09:56 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfdf.h"

int	fdf_losing_focus(void *param)
{
	t_focus	*focus;
	void	*pause;

	focus = (t_focus *)param;
	(*focus).isfocused = 1;
	while ((*focus).isfocused != 0)
		(void)pause;
	return (0);
}
