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
	int					n_philos;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				desired_meals;
}						t_input;

typedef struct			s_philo {
	size_t				num;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				desired_meals;
	size_t				current_meal;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t 	*right_fork;
	_Bool				is_hungry;
	size_t				last_meal_time;
}						t_philo;

extern	t_philo			*g_philosophers;
extern	pthread_mutex_t	*g_forks;
extern	pthread_t		*g_philo_threads;
extern	size_t			start_time;
extern	int				full_philos;

size_t					ft_strlen(const char *s);
void					ft_putstr_fd(char *s, int fd);
char					*ft_itoa(size_t num);
int						ft_atoi(const char *str);
int						ft_isdigit(int c);
char					*ft_strdup(const char *s1);
size_t					ft_strlcat(char *dst, const char *src, size_t dstsize);
void					ft_alloc_check(void *ptr);
void					error_fatal();
void					init_forks(int number_of_forks);
void					init_philo(t_input input);
_Bool					init_input(t_input input);
_Bool					parse(int ac, char **av, t_input *input);
size_t					get_time();
char					*get_action(int	action);
char					*create_message(size_t time, int philo, int action);
void					print_message(size_t time, int philo, int action);
void					get_forks(t_philo *philo);

#endif
