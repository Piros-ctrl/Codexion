#include "headerfile.h"

int	ft_cycle_life(t_coder *c, t_dongles *first, t_dongles *second)
{
	if (take_dongles(c, first))
		return (1);
	if (c->sim->params->number_of_coders == 1)
		return (ft_sleep(c->sim->params->time_to_burnout + 20, c->sim), 1);
	if (take_dongles(c, second))
		return (ft_put_dongles(c), 1);
	ft_change_value(&c->sim->share_mutex, &c->last_compile, ft_get_time());
	ft_print_log(c, "is compiling");
	if (ft_sleep(c->sim->params->time_to_compile, c->sim))
		return (ft_put_dongles(c), 1);
	pthread_mutex_lock(&c->sim->share_mutex);
	c->compile_count++;
	pthread_mutex_unlock(&c->sim->share_mutex);
	ft_put_dongles(c);
	ft_print_log(c, "is debugging");
	if (ft_sleep(c->sim->params->time_to_debug, c->sim))
		return (1);
	ft_print_log(c, "is refactoring");
	if (ft_sleep(c->sim->params->time_to_refactor, c->sim))
		return (1);
	if (ft_read_safe(&c->sim->share_mutex, &c->compile_count)
		>= c->sim->params->number_of_compiles_required)
		return (1);
	return (0);
}

void	*ft_rotine(void *args)
{
	t_coder		*c;
	t_dongles	*first;
	t_dongles	*second;

	c = (t_coder *)args;
	get_dongle_order(c, &first, &second);
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
