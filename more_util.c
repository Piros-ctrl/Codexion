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

void	ft_print_log(t_coder *coder, char *str)
{
	pthread_mutex_lock(&coder->sim->log_mutex);
	if (ft_read_safe(&coder->sim->share_mutex, &coder->sim->simulation_on))
		printf("%ld %ld %s\n", ft_get_time() - coder->sim->start_time, coder->id, str);
	pthread_mutex_unlock(&coder->sim->log_mutex);
}

void	get_dongle_order(t_coder *coder, t_dongles **first, t_dongles **second)
{
	if (coder->left_dongle->id < coder->right_dongle->id)
	{
		*first = coder->left_dongle;
		*second = coder->right_dongle;
	}
	else
	{
		*first = coder->right_dongle;
		*second = coder->left_dongle;
	}
}
