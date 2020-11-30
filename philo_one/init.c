#include "philo_one.h"


_Bool	is_bad_input(char **av)
{
	int i;
	int j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

_Bool	init_input(int ac, char **av, t_input *input)
{
	input->number_of_philosophers = ft_atoi(av[1]);
	input->time_to_die = ft_atoi(av[2]);
	input->time_to_eat = ft_atoi(av[3]);
	input->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		input->desired_meals = ft_atoi(av[4]);
	else
		input->desired_meals = 0;
	if (input->number_of_philosophers < 2 || input->time_to_die <= 0 || \
		input->time_to_eat <= 0 || input->time_to_sleep <= 0 || \
		(ac == 6 && input->desired_meals < 1))
		return (1);
	if (!(g_philosophers = malloc(sizeof(t_philo) * input->number_of_philosophers)))
		return (1);
	if (!(g_forks = malloc(sizeof(pthread_mutex_t) * input->number_of_philosophers)))
	{
		free(g_philosophers);
		return (1);
	}
	if (!(g_philo_threads = malloc(sizeof(pthread_t) * input->number_of_philosophers)))
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

	while (i < input.number_of_philosophers)
	{
		g_philosophers[i].num = i;
		g_philosophers[i].is_dead = 0;
		g_philosophers[i].time_to_die = input.time_to_die;
		g_philosophers[i].time_to_eat = input.time_to_eat;
		g_philosophers[i].time_to_sleep = input.time_to_sleep;
		g_philosophers[i].desired_meals = input.desired_meals;
		g_philosophers[i].current_meal = 0;
		g_philosophers[i].is_left_taken = 0;
		g_philosophers[i].is_right_taken = 0;
		g_philosophers[i].is_eating = 0;
		g_philosophers[i].left_fork = &g_forks[assign_left_fork(i, input.number_of_philosophers)];
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