#include "headerfile.h"

int main(int ac, char **av)
{
    t_conf config;

    if (ac != 9)
    {
        printf("Usage: ./codexion ...\n");
        return (1);
    }

    if (!parser(av, &config))
        return (1);

    printf("%u\n", config.number_of_coders);
    printf("%u\n", config.time_to_burnout);
    printf("%u\n", config.time_to_compile);
    printf("%d\n", config.time_to_debug);
    printf("%d\n", config.time_to_refactor);
    printf("%u\n", config.number_of_compiles_required);
    printf("%d\n", config.dongle_cooldown);
    printf("%s\n", config.scheduler);

    return (0);
}
