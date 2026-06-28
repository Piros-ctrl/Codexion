#ifndef CONF_H
#define CONF_H

typedef struct conf{
    unsigned int    number_of_coders;
    unsigned int    time_to_burnout;
    unsigned int    time_to_compile;
    int             time_to_debug;
    int             time_to_refactor;
    unsigned int    number_of_compiles_required;
    int             dongle_cooldown;
    char            *scheduler;
}   t_conf;

#endif
