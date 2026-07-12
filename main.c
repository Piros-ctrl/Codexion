#include "headerfile.h"

int	main(int ac, char **av)
{
	t_conf	config;
	t_sim	*sim;

	if (ac != 9)
	{
		fprintf(stderr, "Usage: %s number_of_coders time_to_burnout "
			"time_to_compile time_to_debug time_to_refactor "
			"[number_of_compiles_required]\n", av[0]);
		return (1);
	}
	if (parser(av, &config) != 0)
		return (1);
	sim = ft_init_sim(&config);
	if (!sim)
		return (1);
	if (ft_simulation(sim))
		return (1);
	return (0);
}
