#include "headerfile.h"

long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_change_value(pthread_mutex_t *mutex, long *var, long val)
{
	pthread_mutex_lock(mutex);
	*var = val;
	pthread_mutex_unlock(mutex);
}

long	ft_read_safe(pthread_mutex_t *mutex, long *var)
{
	long	val;

	pthread_mutex_lock(mutex);
	val = *var;
	pthread_mutex_unlock(mutex);
	return (val);
}

int	ft_sleep(long ms, t_sim *sim)
{
	long	start;

	start = ft_get_time();
	while (ft_get_time() - start < ms)
	{
		if (!ft_read_safe(&sim->share_mutex, &sim->simulation_on))
			return (1);
		usleep(500);
	}
	return (0);
}

void	ft_print_log(t_coder *c, char *str)
{
	pthread_mutex_lock(&c->sim->log_mutex);
	if (ft_read_safe(&c->sim->share_mutex, &c->sim->simulation_on))
		printf("%ld %ld %s\n", ft_get_time() - c->sim->start_time, c->id, str);
	pthread_mutex_unlock(&c->sim->log_mutex);
}

void	get_dongle_order(t_coder *c, t_dongles **first, t_dongles **second)
{
	if (c->left_dongle->id < c->right_dongle->id)
	{
		*first = c->left_dongle;
		*second = c->right_dongle;
	}
	else
	{
		*first = c->right_dongle;
		*second = c->left_dongle;
	}
}
