#include "philo_one.h"

t_philo			*g_philosophers;
pthread_mutex_t	*g_forks;
pthread_t		*g_philo_threads;
size_t			start_time;
int				full_philos;

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
}

void		sleep_philo(size_t sleeping_time, t_philo *philo)
{
	print_message(sleeping_time - start_time, philo->num, SLEEP);
	count_time(sleeping_time, philo->time_to_sleep);
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
		if (philo->desired_meals && philo->current_meal == philo->desired_meals)
		{
			full_philos++;
			philo->is_hungry = 0;
			break ;
		}
		sleep_philo(get_time(), philo);
		print_message(get_time() - start_time, philo->num, THINK);
	}
	return (0);
}

_Bool			monitor(t_input input)
{
	int i;

	while (1)
	{
		i = 0;
		while (i < input.n_philos)
		{
			if (g_philosophers[i].is_hungry && get_time() - g_philosophers[i].last_meal_time > g_philosophers[i].time_to_die)
			{
				print_message(get_time() - start_time, i, DEATH);
				return (1);
			}
			if (full_philos && full_philos == input.n_philos)
			{
				return (1);
			}
			i++;
		}
	}
	return (0);
}

void			free_all_mem(int size)
{
	int			i;

	i = 0;
	while (i < size)
	{
		pthread_detach(g_philo_threads[i]);
		i++;
	}
	free(g_philosophers);
	free(g_forks);
	free(g_philo_threads);
}

int				main(int ac, char **av)
{
	t_input		input;
	int			i;

	if (parse(ac, av, &input))
		return (1);
	init_philo(input);
	init_forks(input.n_philos);
	i = 0;
	full_philos = 0;
	start_time = get_time();
	while (i < input.n_philos)
	{
		g_philosophers[i].last_meal_time = start_time;
		if (pthread_create(&g_philo_threads[i], NULL, \
							eat_sleep_repeat, (void *)(&g_philosophers[i])))
			error_fatal();
		i++;
	}
	if (monitor(input))
		free_all_mem(input.n_philos);

	return (0);
}
