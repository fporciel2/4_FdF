/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_gaining_focus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:05:01 by fporciel          #+#    #+#             */
/*   Updated: 2023/05/24 18:10:21 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfdf.h"

int	fdf_gaining_focus(void *param)
{
	t_focus	*focus;

	focus = (t_focus *)param;
	(*focus).isfocused = 0;
	return (0);
}
