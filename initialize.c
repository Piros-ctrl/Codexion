/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabderra <oabderra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 18:26:35 by oabderra          #+#    #+#             */
/*   Updated: 2026/07/22 22:11:26 by oabderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headerfile.h"

t_dongles	*ft_init_dongeles(t_sim *sim, long nb)
{
	t_dongles	*dongle;
	long		i;

	dongle = malloc(nb * sizeof(t_dongles));
	if (!dongle)
		return (ft_free(sim, -1, 1));
	sim->dongles = dongle;
	i = 0;
	while (i < nb)
	{
		dongle[i].id = i + 1;
		dongle[i].available_at = 0;
		dongle[i].is_available = 1;
		pthread_mutex_init(&dongle[i].lock, NULL);
		pthread_cond_init(&dongle[i].cond, NULL);
		dongle[i].waiting.coders[0] = NULL;
		dongle[i].waiting.coders[1] = NULL;
		i++;
	}
	return (dongle);
}

t_coder	*ft_init_coders(t_sim *sim)
{
	t_coder	*coder;
	long	nb;
	long	i;

	nb = sim->params->number_of_coders;
	coder = malloc(nb * sizeof(t_coder));
	if (!coder)
		return (ft_free(sim, -1, 2));
	sim->coders = coder;
	i = 0;
	while (i < nb)
	{
		coder[i].id = i + 1;
		memset(&coder[i].thread, 0, sizeof(pthread_t));
		coder[i].right_dongle = &sim->dongles[i];
		coder[i].left_dongle = &sim->dongles[(i + 1) % nb];
		coder[i].last_compile = ft_get_time();
		coder[i].compile_count = 0;
		coder[i].request_time = 0;
		coder[i].sim = sim;
		i++;
	}
	return (coder);
}

t_sim	*ft_init_sim(t_conf *config)
{
	t_sim	*sim;

	sim = malloc(sizeof(t_sim));
	if (!sim)
		return (NULL);
	sim->params = config;
	sim->dongles = NULL;
	sim->coders = NULL;
	sim->start_flag = 0;
	sim->start_time = 0;
	sim->burned_out = 0;
	sim->simulation_on = 1;
	memset(&sim->monitor_thread, 0, sizeof(pthread_t));
	pthread_mutex_init(&sim->share_mutex, NULL);
	pthread_mutex_init(&sim->log_mutex, NULL);
	if (!ft_init_dongeles(sim, config->number_of_coders))
		return (NULL);
	if (!ft_init_coders(sim))
		return (NULL);
	return (sim);
}

void	*ft_free(t_sim *sim, long j, int error)
{
	if (error == 1)
		fprintf(stderr, "Error: Memory allocation failed for Dongles.\n");
	else if (error == 2)
		fprintf(stderr, "Error: Memory allocation failed for Coder.\n");
	else if (error == 3)
		fprintf(stderr, "Error: Failed to create a Coder thread.\n");
	else if (error == 4)
		fprintf(stderr,
			"Error: Memory allocation failed for Dongle waiting queue.\n");
	if (sim->dongles)
	{
		while (--j >= 0)
		{
			if (sim->dongles[j].waiting.coders)
				free(sim->dongles[j].waiting.coders);
		}
		free(sim->dongles);
		sim->dongles = NULL;
	}
	if (sim->coders)
	{
		free(sim->coders);
		sim->coders = NULL;
	}
	return (NULL);
}

long	ft_is_on(t_sim *sim)
{
	long	val;

	pthread_mutex_lock(&sim->share_mutex);
	val = sim->simulation_on;
	pthread_mutex_unlock(&sim->share_mutex);
	return (val);
}
