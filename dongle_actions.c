/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabderra <oabderra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 18:26:42 by oabderra          #+#    #+#             */
/*   Updated: 2026/07/22 21:43:09 by oabderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headerfile.h"

int	take_dongles(t_coder *coder, t_dongles *dongle)
{
	choice_scheduler(coder);
	pthread_mutex_lock(&dongle->lock);
	ft_add_to_queue(coder, dongle);
	while (!dongle->is_available
		|| ft_first_waiting(dongle) != coder
		|| ft_get_time() < dongle->available_at)
	{
		if (!ft_read_safe(&coder->sim->share_mutex, &coder->sim->simulation_on))
		{
			pthread_mutex_unlock(&dongle->lock);
			return (1);
		}
		if (dongle->is_available
			&& ft_first_waiting(dongle) == coder
			&& ft_get_time() < dongle->available_at)
		{
			pthread_mutex_unlock(&dongle->lock);
			if (ft_sleep(dongle->available_at - ft_get_time(), coder->sim))
				return (1);
			pthread_mutex_lock(&dongle->lock);
		}
		else
			pthread_cond_wait(&dongle->cond, &dongle->lock);
	}
	ft_pop_queue(dongle);
	dongle->is_available = 0;
	dongle->available_at = ft_get_time();
	pthread_mutex_unlock(&dongle->lock);
	ft_print_log(coder, "has taken a dongle");
	return (0);
}

static void	release_one(t_dongles *dongle, t_coder *coder)
{
	pthread_mutex_lock(&dongle->lock);
	dongle->is_available = 1;
	dongle->available_at = ft_get_time() + coder->sim->params->dongle_cooldown;
	pthread_cond_broadcast(&dongle->cond);
	pthread_mutex_unlock(&dongle->lock);
}

void	ft_put_dongles(t_coder *coder)
{
	release_one(coder->left_dongle, coder);
	release_one(coder->right_dongle, coder);
}
