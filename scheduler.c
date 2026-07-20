/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabderra <oabderra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 06:14:41 by oabderra          #+#    #+#             */
/*   Updated: 2026/07/20 07:14:36 by oabderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headerfile.h"


void	choice_scheduler(t_coder *coder)
{
	if (coder->sim->params->scheduler)
        ft_change_value(&coder->sim->share_mutex, &coder->request_time, ft_get_time());
	else
	{
    	ft_change_value(&coder->sim->share_mutex, &coder->request_time,
		ft_read_safe(&coder->sim->share_mutex, &coder->last_compile));
	}
}

void	ft_add_to_queue(t_coder *coder, t_dongles *dongle)
{
    if(dongle->waiting.coders[0] == NULL)
        dongle->waiting.coders[0] = coder;
    else
        dongle->waiting.coders[1] = coder;
}

t_coder	*ft_pop_queue(t_dongles *dongle)
{
	t_coder	*coder;

	if (!dongle->waiting.coders[0])
		return (NULL);
	if (!dongle->waiting.coders[1])
	{
		coder = dongle->waiting.coders[0];
		dongle->waiting.coders[0] = NULL;
		return (coder);
	}
	if (dongle->waiting.coders[0]->request_time
		<= dongle->waiting.coders[1]->request_time)
	{
		coder = dongle->waiting.coders[0];
		dongle->waiting.coders[0] = dongle->waiting.coders[1];
		dongle->waiting.coders[1] = NULL;
	}
	else
	{
		coder = dongle->waiting.coders[1];
		dongle->waiting.coders[1] = NULL;
	}
	return (coder);
}
