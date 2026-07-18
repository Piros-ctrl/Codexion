#include "headerfile.h"

int	take_dongles(t_coder *coder, t_dongles *dongle)
{
	pthread_mutex_lock(&dongle->lock);
	while (!dongle->is_available)
	{
		if (!ft_read_safe(&coder->sim->share_mutex, &coder->sim->simulation_on))
		{
			pthread_mutex_unlock(&dongle->lock);
			return (1);
		}
		pthread_cond_wait(&dongle->cond, &dongle->lock);
	}
	dongle->is_available = 0;
	dongle->available_at = ft_get_time();
	pthread_mutex_unlock(&dongle->lock);
	ft_print_log(coder, "has taken a dongle");
	return (0);
}

static void	release_one(t_dongles *dongle)
{
	pthread_mutex_lock(&dongle->lock);
	dongle->is_available = 1;
	dongle->available_at = ft_get_time();
	pthread_cond_broadcast(&dongle->cond);
	pthread_mutex_unlock(&dongle->lock);
}

void	ft_put_dongles(t_coder *coder)
{
	release_one(coder->left_dongle);
	release_one(coder->right_dongle);
}
