#include "headerfile.h"

int	take_dongles(t_coder *c, t_dongles *d)
{
	pthread_mutex_lock(&d->lock);
	while (!d->is_available)
	{
		if (!ft_read_safe(&c->sim->share_mutex, &c->sim->simulation_on))
		{
			pthread_mutex_unlock(&d->lock);
			return (1);
		}
		pthread_cond_wait(&d->cond, &d->lock);
	}
	d->is_available = 0;
	d->available_at = ft_get_time();
	pthread_mutex_unlock(&d->lock);
	ft_print_log(c, "has taken a dongle");
	return (0);
}

static void	release_one(t_dongles *d)
{
	pthread_mutex_lock(&d->lock);
	d->is_available = 1;
	d->available_at = ft_get_time();
	pthread_cond_broadcast(&d->cond);
	pthread_mutex_unlock(&d->lock);
}

void	ft_put_dongles(t_coder *c)
{
	release_one(c->left_dongle);
	release_one(c->right_dongle);
}
