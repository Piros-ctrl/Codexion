#include "headerfile.h"

void	ft_destroy(t_sim *sim)
{
	long	i;

	i = 0;
	while (i < sim->params->number_of_coders)
	{
		pthread_mutex_destroy(&sim->dongles[i].lock);
		pthread_cond_destroy(&sim->dongles[i].cond);
		i++;
	}
	pthread_mutex_destroy(&sim->share_mutex);
	pthread_mutex_destroy(&sim->log_mutex);
	free(sim->dongles);
	free(sim->coders);
	free(sim);
}

int	ft_free_thread(t_sim *sim, t_coder *coder, long i)
{
	long	j;

	ft_change_value(&sim->share_mutex, &sim->simulation_on, 0);
	if (sim->monitor_thread)
		pthread_join(sim->monitor_thread, NULL);
	j = 0;
	while (j < i)
	{
		if (coder[j].thread)
			pthread_join(coder[j].thread, NULL);
		j++;
	}
	ft_destroy(sim);
	return (1);
}
