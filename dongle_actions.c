/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabderra <oabderra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 18:26:42 by oabderra          #+#    #+#             */
/*   Updated: 2026/07/20 18:52:49 by oabderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headerfile.h"

int	take_dongles(t_coder *c, t_dongles *d)
{
	choice_scheduler(c);
	pthread_mutex_lock(&d->lock);
	ft_add_to_queue(c, d);
	while (!d->is_available
	|| ft_first_waiting(d) != c
	|| ft_get_time() < d->available_at)
	{
		if (!ft_read_safe(&c->sim->share_mutex, &c->sim->simulation_on))
		{
			pthread_mutex_unlock(&d->lock);
			return (1);
		}

		if (d->is_available
			&& ft_first_waiting(d) == c
			&& ft_get_time() < d->available_at)
		{
			pthread_mutex_unlock(&d->lock);
			if (ft_sleep(d->available_at - ft_get_time(), c->sim))
				return (1);
			pthread_mutex_lock(&d->lock);
		}
		else
			pthread_cond_wait(&d->cond, &d->lock);
	}
	// while (!d->is_available || ft_first_waiting(d) != c || ft_get_time() < d->available_at)
	// {
	// 	if (!ft_read_safe(&c->sim->share_mutex, &c->sim->simulation_on))
	// 	{
	// 		pthread_mutex_unlock(&d->lock);
	// 		return (1);
	// 	}
	// 	pthread_cond_wait(&d->cond, &d->lock);
	// }
	ft_pop_queue(d);
	d->is_available = 0;
	d->available_at = ft_get_time();
	pthread_mutex_unlock(&d->lock);
	ft_print_log(c, "has taken a dongle");
	return (0);
}

static void	release_one(t_dongles *d, t_coder *coder)
{
	pthread_mutex_lock(&d->lock);
	d->is_available = 1;
	d->available_at = ft_get_time() + coder->sim->params->dongle_cooldown;
	pthread_cond_broadcast(&d->cond);
	pthread_mutex_unlock(&d->lock);
}

void	ft_put_dongles(t_coder *coder)
{
	release_one(coder->left_dongle, coder);
	release_one(coder->right_dongle, coder);
}
