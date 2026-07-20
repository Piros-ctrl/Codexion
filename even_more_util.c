/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even_more_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabderra <oabderra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 06:58:44 by oabderra          #+#    #+#             */
/*   Updated: 2026/07/20 07:25:40 by oabderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headerfile.h"

void    ft_swap(t_coder **coder0, t_coder **coder1)
{
    t_coder *tmp;

    tmp = *coder0;
    *coder0 = *coder1;
    *coder1 = tmp;
}

t_coder	*ft_first_waiting(t_dongles *dongle)
{
	t_coder	*c0;
	t_coder	*c1;

	c0 = dongle->waiting.coders[0];
	c1 = dongle->waiting.coders[1];
	if (c0 == NULL)
		return (c1);
	if (c1 == NULL)
		return (c0);
	if (c0->request_time <= c1->request_time)
		return (c0);
	return (c1);
}
