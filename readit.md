creating a small example of monitor to see how that thread manage other threads
 //      //  //   //     // global mutex for managing thos threads.
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