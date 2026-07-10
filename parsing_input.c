#include "headerfile.h"


static int	parse_number(char *arg, int *value, char *name, int positive)
{
	if (is_solid_int(arg))
	{
		printf("Error: %s must be a valid integer.\n", name);
		return (0);
	}
	if ((positive && !is_positive(arg))
		|| (!positive && !is_goe_to_zero(arg)))
	{
		if (positive)
			printf("Error: %s must be positive.\n", name);
		else
			printf("Error: %s cannot be negative.\n", name);
		return (0);
	}
	*value = ft_atoi(arg);
	return (1);
}

int	parser(char **av, t_conf *config)
{
	if (!parse_number(av[1], &config->number_of_coders, "number_of_coders", 1))
		return (0);
	if (!parse_number(av[2], &config->time_to_burnout, "time_to_burnout", 1))
		return (0);
	if (!parse_number(av[3], &config->time_to_compile, "time_to_compile", 1))
		return (0);
	if (!parse_number(av[4], &config->time_to_debug, "time_to_debug", 0))
		return (0);
	if (!parse_number(av[5], &config->time_to_refactor, "time_to_refactor", 0))
		return (0);
	if (!parse_number(av[6], &config->number_of_compiles_required, "number_of_compiles_required", 1))
		return (0);
	if (!parse_number(av[7], &config->dongle_cooldown, "dongle_cooldown", 0))
		return (0);
	if (strcmp(av[8], "fifo") && strcmp(av[8], "edf"))
	{
		printf("Error: scheduler must be either \"fifo\" or \"edf\".\n");
		return (0);
	}
    if (strcmp(av[8], "edf"))
        config->scheduler = 1;
    else
        config->scheduler = 0;
	return (1);
}
