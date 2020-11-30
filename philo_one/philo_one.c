#include "philo_one.h"

t_philo			*g_philosophers;
pthread_mutex_t	*g_forks;
pthread_t		*g_philo_threads;
size_t			start_time;

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

//void			monitor(t_input input)
//{
//
//}

int				main(int ac, char **av)
{
//	(void)ac;
//	(void)av;
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
	start_time = get_time();
	while (i < input.number_of_philosophers)
	{
		g_philosophers[i].last_meal_time = start_time;
		pthread_create(&g_philo_threads[i], NULL, eat_sleep_repeat, (void *)(&g_philosophers[i]));
		i++;
	}
//	monitor(input);

//	while (1)
//	{
//
//		// last eat = start time
////		if () current time - simulation start time > time death || cur time - last meal > time death
//	}

//	pthread_join(thread, NULL);
//
//	start_philo();


	// save start time
	// usleep. create my function to count time without calculation errors

//	ft_alloc_check(g_philosophers);

	// Each philosopher should be given a number from 1 to ’number_of_philosophers’.

	// Philosopher number 1 is next to philosopher number ’number_of_philosophers’.
	//Any other philosopher with number N is seated between philosopher N - 1 and
	//philosopher N + 1
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