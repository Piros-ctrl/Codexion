/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabderra <oabderra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 18:26:07 by oabderra          #+#    #+#             */
/*   Updated: 2026/07/20 18:26:09 by oabderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headerfile.h"

int	ft_cycle_life(t_coder *coder, t_dongles *first, t_dongles *second)
{
	if (take_dongles(coder, first))
		return (1);
	if (coder->sim->params->number_of_coders == 1)
		return (ft_sleep(coder->sim->params->time_to_burnout + 20, coder->sim), 1);
	if (take_dongles(coder, second))
		return (ft_put_dongles(coder), 1);
	ft_change_value(&coder->sim->share_mutex, &coder->last_compile, ft_get_time());
	ft_print_log(coder, "is compiling");
	if (ft_sleep(coder->sim->params->time_to_compile, coder->sim))
		return (ft_put_dongles(coder), 1);
	pthread_mutex_lock(&coder->sim->share_mutex);
	coder->compile_count++;
	pthread_mutex_unlock(&coder->sim->share_mutex);
	ft_put_dongles(coder);
	ft_print_log(coder, "is debugging");
	if (ft_sleep(coder->sim->params->time_to_debug, coder->sim))
		return (1);
	ft_print_log(coder, "is refactoring");
	if (ft_sleep(coder->sim->params->time_to_refactor, coder->sim))
		return (1);
	if (ft_read_safe(&coder->sim->share_mutex, &coder->compile_count)
		>= coder->sim->params->number_of_compiles_required)
		return (1);
	return (0);
}

void	*ft_rotine(void *args)
{
	t_coder		*c;
	t_dongles	*first;
	t_dongles	*second;

	c = (t_coder *)args;
	get_dongle_order(c, &first, &second); // why two pointers
	while (ft_read_safe(&c->sim->share_mutex, &c->sim->simulation_on))
	{
		if (ft_cycle_life(c, first, second))
			return (NULL);
	}
	return (NULL);
}

int	ft_creation_threads(t_sim *sim, t_coder *coder, long i)
{
	sim->simulation_on = 1;
	sim->start_time = ft_get_time();
	if (pthread_create(&sim->monitor_thread, NULL, ft_monitor, sim))
		return (ft_free_thread(sim, coder, i));
	while (i < sim->params->number_of_coders)
	{
		if (pthread_create(&coder[i].thread, NULL, ft_rotine, &coder[i]))
			return (ft_free_thread(sim, coder, i));
		i++;
	}
	pthread_join(sim->monitor_thread, NULL);
	i = 0;
	while (i < sim->params->number_of_coders)
		pthread_join(sim->coders[i++].thread, NULL);
	ft_destroy(sim);
	return (0);
}

int	ft_simulation(t_sim *sim)
{
	t_dongles	*dongle;
	t_coder		*coder;
	long		i;

	dongle = ft_init_dongeles(sim, sim->params->number_of_coders);
	if (!dongle)
		return (1);
	coder = ft_init_coders(sim);
	if (!coder)
		return (1);
	i = 0;
	if (ft_creation_threads(sim, coder, i))
		return (1);
	return (0);
}
