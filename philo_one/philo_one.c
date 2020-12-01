#include "philo_one.h"

t_philo			*g_philosophers;
pthread_mutex_t	*g_forks;
pthread_t		*g_philo_threads;
size_t			start_time;
size_t			meals;

void		count_time(size_t time, size_t desired_time)
{
	while (get_time() - time < desired_time)
		usleep(100);
}

void		eat(size_t eating_time, t_philo *philo)
{
	print_message(eating_time - start_time, philo->num, EAT);
	count_time(eating_time, philo->time_to_eat);
	philo->last_meal_time = get_time();
	philo->current_meal++;
	if (philo->current_meal == philo->desired_meals)
		meals++;
}

void		sleep_philo(size_t sleeping_time, t_philo *philo)
{
	print_message(sleeping_time - start_time, philo->num, SLEEP);
	count_time(sleeping_time, philo->time_to_eat);
}

void		*eat_sleep_repeat(void *val)
{
	t_philo *philo;

	philo = (t_philo *)val;
	while (1)
	{
		get_forks(philo);
		eat(get_time(), philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		sleep_philo(get_time(), philo);
		print_message(get_time() - start_time, philo->num, THINK);
	}
	return (0);
}

_Bool			monitor(t_input input)
{
	int i;

	i = 0;
	while (1)
	{
		while (i < input.number_of_philosophers)
		{
			if (get_time() - g_philosophers[i].last_meal_time > g_philosophers[i].time_to_die)
			{
				print_message(get_time() - start_time, i, DEATH);
				return (1);
			}
		if (meals && meals == input.desired_meals)
			return (1);
		i++;
		}
	}
	return (0);
}

void			free_all_mem()
{
	free(g_philosophers);
	free(g_forks);
	free(g_philo_threads);
}

int				main(int ac, char **av)
{
//	(void)ac;
//	(void)av;
//
//	start_time = get_time();
//	print_message(get_time() - start_time, 1, TAKEN_A_FORK);
//	print_message(get_time() - start_time, 1, TAKEN_A_FORK);


	t_input		input;
	int			i;

	if ((ac != 5 && ac != 6) || is_bad_input(av))
	{
		ft_putstr_fd("error arguments count or bad content", 2);
		return (1);
	}
	if (init_input(ac, av, &input))
	{
		ft_putstr_fd("out of memory", 2);
		return (1);
	}
	init_philo(input);
	init_forks(input.number_of_philosophers);

	i = 0;
	meals = 0;
	start_time = get_time();
	while (i < input.number_of_philosophers)
	{
		g_philosophers[i].last_meal_time = start_time;
		pthread_create(&g_philo_threads[i], NULL, eat_sleep_repeat, (void *)(&g_philosophers[i]));
		i++;
	}
	if (monitor(input))
	{
		free_all_mem();
	}
	return (0);

}

/*
• Any change of status of a philosopher must be written as follows (with X replaced
with the philosopher number and timestamp_in_ms the current timestamp in milliseconds)
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
• You can’t have more than 10 ms between the death of a philosopher and when it will print its death.
 */