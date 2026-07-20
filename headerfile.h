#ifndef HEADER_H
#define HEADER_H
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_coder   t_coder;
typedef struct s_dongles t_dongles;
typedef struct s_sim     t_sim;

//===========>this is for the input in parsing
typedef struct s_conf{
    unsigned int    number_of_coders;
    unsigned int    time_to_burnout;
    unsigned int    time_to_compile;
    int             time_to_debug;
    int             time_to_refactor;
    unsigned int    number_of_compiles_required;
    int             dongle_cooldown;
    int             scheduler;
}                   t_conf;

// ============> this is for waiting queue
typedef struct s_queue
{
	t_coder					*coders[2];
}							t_queue;

//============> this is for dungle
typedef struct s_dongles
{
	long					id;
	long					available_at;
	int						is_available;
	t_queue					waiting;
	pthread_mutex_t			lock;
	pthread_cond_t			cond;
}							t_dongles;

//============> this is for sim
typedef struct s_sim
{
	t_conf					*params;
	t_dongles				*dongles;
	t_coder					*coders;
	pthread_t				monitor_thread;
	pthread_mutex_t			share_mutex;
	pthread_mutex_t			log_mutex;
	int						start_flag;
	long					start_time;
	long					burned_out;
	long					simulation_on;
}							t_sim;

//============> this is for the coder
typedef struct s_coder
{
	long					id;
	pthread_t				thread;
	t_dongles				*left_dongle;
	t_dongles				*right_dongle;
	long					last_compile;
	long					compile_count;
	long					request_time;
	t_sim					*sim;
}							t_coder;

//============> parsing
int			is_itzero(char *str);
int			is_positive(char *str);
int			is_solid_int(char *s);
int			parser(char **av, t_conf *config);
long		ft_atoi(char *s);
int			is_goe_to_zero(char *str);
long		ft_get_time(void);

//============> init.c
t_dongles	*ft_init_dongeles(t_sim *sim, long nb);
t_coder		*ft_init_coders(t_sim *sim);
t_sim		*ft_init_sim(t_conf *config);
void		*ft_free(t_sim *sim, long j, int error);
long		ft_is_on(t_sim *sim);

//============> simulation_utils.c
void		ft_change_value(pthread_mutex_t *mutex, long *var, long val);
long		ft_read_safe(pthread_mutex_t *mutex, long *var);
int			ft_sleep(long ms, t_sim *sim);
void		ft_print_log(t_coder *c, char *str);
void		get_dongle_order(t_coder *c, t_dongles **first, t_dongles **second);

//============> dongle_actions.c
int			take_dongles(t_coder *c, t_dongles *d);
void		ft_put_dongles(t_coder *c);

//============> simulation.c
int			ft_cycle_life(t_coder *c, t_dongles *first, t_dongles *second);
void		*ft_rotine(void *args);
int			ft_creation_threads(t_sim *sim, t_coder *coder, long i);
int			ft_simulation(t_sim *sim);

//============> monitor.c
void		*ft_monitor(void *arg);

//============> cleanup.c
void		ft_destroy(t_sim *sim);
int			ft_free_thread(t_sim *sim, t_coder *coder, long i);

//============> waiting coders
t_coder		*ft_first_waiting(t_dongles *dongle);

//============> scheduler
void		choice_scheduler(t_coder *coder);
void		ft_add_to_queue(t_coder *coder, t_dongles *dongle);
t_coder		*ft_pop_queue(t_dongles *dongle);


#endif
