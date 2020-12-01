#ifndef PHILOSOPHERS_PHILO_ONE_H
#define PHILOSOPHERS_PHILO_ONE_H

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>


#include <stdio.h>

enum {
	EAT,
	SLEEP,
	THINK,
	TAKEN_A_FORK,
	DEATH,
	RIGHT,
	LEFT
};

typedef struct			s_input {
	int					number_of_philosophers; // also the num of forks;
	size_t				time_to_die; // in milliseconds. if a philosopher doesn’t start eating ’time_to_die’ milliseconds after starting his last meal or the beginning of the simulation, it dies
	size_t				time_to_eat; // in milliseconds and is the time it takes for a philosopher to eat. During that time he will need to keep the two forks.
	size_t				time_to_sleep; // in milliseconds and is the time the philosopher will spend sleeping
	size_t				desired_meals; // is optional, if all philosophers eat at least ’number_of_times_each_philosopher_must_eat’ the simulation will stop. If not specified, the simulation will stop only at the death of a philosopher.
}						t_input;

typedef struct			s_philo {
	size_t				num; //on output + 1
	size_t				time_to_die; // in milliseconds. if a philosopher doesn’t start eating ’time_to_die’ milliseconds after starting his last meal or the beginning of the simulation, it dies
	size_t				time_to_eat; // in milliseconds and is the time it takes for a philosopher to eat. During that time he will need to keep the two forks.
	size_t				time_to_sleep; // in milliseconds and is the time the philosopher will spend sleeping
	int					number_of_times_each_philosopher_must_eat; // is optional, if all philosophers eat at least ’number_of_times_each_philosopher_must_eat’ the simulation will stop. If not specified, the simulation will stop only at the death of a philosopher.
	size_t				desired_meals;
	size_t				current_meal;
	pthread_mutex_t		*left_fork; // mutex blocks resources in another thread, if made mutax lock. needs to be unlocked in the same thread
	pthread_mutex_t 	*right_fork;
	_Bool				is_left_taken;
	_Bool				is_right_taken;
	_Bool				is_eating;
	_Bool				is_dead;
	_Bool				is_hungry;
	size_t				last_meal_time;
}						t_philo;

extern	t_philo			*g_philosophers;
extern	pthread_mutex_t	*g_forks;
extern	pthread_t		*g_philo_threads;
extern	size_t			start_time;
extern	int				meals;

size_t					ft_strlen(const char *s);
void					ft_putstr_fd(char *s, int fd);
char					*ft_itoa(size_t num);
int						ft_atoi(const char *str);
int						ft_isdigit(int c);
void					*ft_memcpy(void *dst, const void *src, size_t n);
char					*ft_strdup(const char *s1);
size_t					ft_strlcat(char *dst, const char *src, size_t dstsize);
void					ft_alloc_check(void *ptr);
void					error_fatal();

void					init_forks(int number_of_forks);
void					init_philo(t_input input);
_Bool					init_input(int ac, char **av, t_input *input);
_Bool					is_bad_input(char **av);
size_t					get_time();
char					*get_action(int	action);
char					*create_message(size_t time, int philo, int action);
void					print_message(size_t time, int philo, int action);
void					get_forks(t_philo *philo);



#endif
