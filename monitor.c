#include "headerfile.h"

static int	check_burnout(t_sim *sim)
{
	long	i;
	long	last;
	long	now;

	i = 0;
	while (i < sim->params->number_of_coders)
	{
		pthread_mutex_lock(&sim->share_mutex);
		last = sim->coders[i].last_compile;
		now = ft_get_time();
		if (now - last > sim->params->time_to_burnout)
		{
			sim->burned_out = sim->coders[i].id;
			sim->simulation_on = 0;
			pthread_mutex_unlock(&sim->share_mutex);
			return (1);
		}
		pthread_mutex_unlock(&sim->share_mutex);
		i++;
	}
	return (0);
}

static int	check_all_done(t_sim *sim)
{
	long	i;
	int		done;

	i = 0;
	done = 1;
	pthread_mutex_lock(&sim->share_mutex);
	while (i < sim->params->number_of_coders)
	{
		if (sim->coders[i].compile_count
			< sim->params->number_of_compiles_required)
			done = 0;
		i++;
	}
	if (done)
		sim->simulation_on = 0;
	pthread_mutex_unlock(&sim->share_mutex);
	return (done);
}

void	*ft_monitor(void *arg)
{
	t_sim	*sim;

	sim = (t_sim *)arg;
	while (ft_read_safe(&sim->share_mutex, &sim->simulation_on))
	{
		if (check_burnout(sim))
		{
			pthread_mutex_lock(&sim->log_mutex);
			printf("%ld %ld burned out\n",
				ft_get_time() - sim->start_time, sim->burned_out);
			pthread_mutex_unlock(&sim->log_mutex);
			break ;
		}
		if (check_all_done(sim))
			break ;
		usleep(500);
	}
	return (NULL);
}
