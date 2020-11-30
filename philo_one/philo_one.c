#include "philo_one.h"

t_philo			*g_philosophers;
pthread_mutex_t	*g_forks;
pthread_t		*g_philo_threads;

void		*eat_sleep_repeat(void *val)
{
	t_philo *philo;

	philo = (t_philo *)val;
	while (1)
	{
		//start time variable

		// rules which fork to choose
		 //choose forks
//		pthread_mutex_lock(philo->left_fork);
//		//taken fork
//		pthread_mutex_lock(philo->right_fork);
		//taken fork
		// if both forks taken
			//eat, is_eating = 1;
		// print is_eating
		// get off forks
		usleep(100); // do sleep every time by 100
		// get something of day function, and compare
		//sleep write
		usleep(200 * 1000);
		//think print

		// if
		if (philo->is_dead)
			break ;
	}
	pthread_mutex_lock(philo->left_fork);
	//taken fork
	pthread_mutex_lock(philo->right_fork);
	//taken fork

//	//eat, is_eating = 1;
//	// print is_eating
//	usleep(200 * 1000);
//	//sleep
//	usleep(200 * 1000);
//	//think print
	return (0);
}

char			*get_action(int	action)
{
	if (action == EAT)
		return (" is eating\n");
	else if (action == SLEEP)
		return (" is sleeping\n");
	else if (action == THINK)
		return (" is thinking\n");
	else if (action == TAKEN_A_FORK)
		return (" has taken a fork\n");
	else if (action == DEATH)
		return (" died\n");
	return (NULL);
}

char			*create_message(int time, int philo, int action)
{
	char		*time_str;
	char		*num_str;
	char		*message;
	char		*act;
	size_t		i;

	i = -1;
	act = ft_strdup(get_action(action));
	ft_alloc_check(act);
	time_str = ft_itoa(time);
	ft_alloc_check(time_str);
	num_str = ft_itoa(philo);
	ft_alloc_check(num_str);
	if (!(message = malloc(ft_strlen(time_str) + 4 + ft_strlen(time_str) + 1 + ft_strlen(act) + 1)))
		return (NULL);
	ft_memcpy(message, time_str, ft_strlen(time_str));

	memset(message + ft_strlen(time_str), ' ', 4);
	i = ft_strlen(time_str) + 5;
	ft_memcpy(message + i, num_str, ft_strlen(num_str));
	i += ft_strlen(num_str);
	ft_memcpy(message + i, act, ft_strlen(act) + 1);

	free(act);
	free(time_str);
	free(num_str);
	return (message);
}

void			get_time()
{
	struct timeval		time;

	gettimeofday(&time, NULL);
	time.tv_sec // seconds epoch start
	time.tv_usec // count remainder from seconds
}

int				main(int ac, char **av)
{
//	(void)ac;
//	(void)av;
	pthread_t	waiter;
//	int k = 550;
	t_input		input;

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

// init threads
	int i = 0;

	while (i < input.number_of_philosophers)
	{
		pthread_create(&g_philo_threads[i], NULL, eat_sleep_repeat, (void *)(&g_philosophers[i]));
		i++;
	}

	// could be a different thread
	while (1)
	{

		// last eat = start time
//		if () current time - simulation start time > time death || cur time - last meal > time death
	}

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