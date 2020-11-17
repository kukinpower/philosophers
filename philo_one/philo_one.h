#ifndef PHILOSOPHERS_PHILO_ONE_H
#define PHILOSOPHERS_PHILO_ONE_H

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct	s_input {
	int	number_of_philosophers; // also the num of forks;
	int	time_to_die; // in milliseconds. if a philosopher doesn’t start eating ’time_to_die’ milliseconds after starting his last meal or the beginning of the simulation, it dies
	int	time_to_eat; // in milliseconds and is the time it takes for a philosopher to eat. During that time he will need to keep the two forks.
	int time_to_sleep; // in milliseconds and is the time the philosopher will spend sleeping
	int	number_of_times_each_philosopher_must_eat; // is optional, if all philosophers eat at least ’number_of_times_each_philosopher_must_eat’ the simulation will stop. If not specified, the simulation will stop only at the death of a philosopher.
}				t_input;

typedef struct	s_philo {
	int	time_to_die; // in milliseconds. if a philosopher doesn’t start eating ’time_to_die’ milliseconds after starting his last meal or the beginning of the simulation, it dies
	int	time_to_eat; // in milliseconds and is the time it takes for a philosopher to eat. During that time he will need to keep the two forks.
	int time_to_sleep; // in milliseconds and is the time the philosopher will spend sleeping
	int	number_of_times_each_philosopher_must_eat; // is optional, if all philosophers eat at least ’number_of_times_each_philosopher_must_eat’ the simulation will stop. If not specified, the simulation will stop only at the death of a philosopher.
	pthread_mutex_t	*left; // mutex blocks resources in another thread, if made mutax lock. needs to be unlocked in the same thread
	pthread_mutex_t *right;
	_Bool is_left_taken;
	_Bool is_right_taken;
}				t_philo;

extern	t_philo	*g_philosophers;
size_t		ft_strlen(const char *s);
void		ft_putstr_fd(char *s, int fd);
char		*ft_itoa(int n);
int			ft_atoi(const char *str);
int			ft_isdigit(int c);

#endif
