#include "philo_one.h"

_Bool	init_input(t_input input)
{
	if (!(g_philosophers = malloc(sizeof(t_philo) * input.n_philos)))
		return (1);
	if (!(g_forks = malloc(sizeof(pthread_mutex_t) * input.n_philos)))
	{
		free(g_philosophers);
		return (1);
	}
	if (!(g_philo_threads = malloc(sizeof(pthread_t) * input.n_philos)))
	{
		free(g_philosophers);
		free(g_forks);
		return (1);
	}
	return (0);
}

int		assign_left_fork(int i, int num)
{
	int		j;

	j = i == 0 ? num - 1 : i - 1;
	return (j);
}

int		assign_right_fork(int i)
{
	int		j;

	j = i == 0 ? 0 : i;
	return (j);
}

void		init_philo(t_input input)
{
	int	i;

	i = 0;

	while (i < input.n_philos)
	{
		g_philosophers[i].num = i;
		g_philosophers[i].time_to_die = input.time_to_die;
		g_philosophers[i].time_to_eat = input.time_to_eat;
		g_philosophers[i].time_to_sleep = input.time_to_sleep;
		g_philosophers[i].desired_meals = input.desired_meals;
		g_philosophers[i].current_meal = 0;
		g_philosophers[i].is_hungry = 1;
		g_philosophers[i].left_fork = &g_forks[assign_left_fork(i, input.n_philos)];
		g_philosophers[i].right_fork = &g_forks[assign_right_fork(i)];
		i++;
	}
}

void		init_forks(int number_of_forks)
{
	int	i;

	i = 0;

	while (i < number_of_forks)
	{
		pthread_mutex_init(&g_forks[i], NULL);
		i++;
	}
}