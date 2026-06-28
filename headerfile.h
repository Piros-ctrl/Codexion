#ifndef HEADER_H
#define HEADER_H
#include "parsing_input.h"
#include <stdio.h>

int     is_itzero(char *str);
int     is_positive(char *str);
int     is_solid_int(char *s);
int     parser(char **av, t_conf *config);
long	ft_atoi(char *s);
int     is_goe_to_zero(char *str);



#endif