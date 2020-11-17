#include "philo_one.h"

t_philo	*g_philosophers;

_Bool	is_bad_input(char **av)
{
	int i;
	int j;

	i = 0;
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

void	init_input(int ac, char **av, t_input *input)
{
	input->number_of_philosophers = ft_atoi(av[0]);
	input->time_to_die = ft_atoi(av[1]);
	input->time_to_eat = ft_atoi(av[2]);
	input->time_to_sleep = ft_atoi(av[3]);
	if (ac == 6)
		input->number_of_times_each_philosopher_must_eat = ft_atoi(av[4]);
	else
		input->number_of_times_each_philosopher_must_eat = 0;
}

void		init_philo(t_input input)
{
	int	i;

	i = 0;
	g_philosophers = malloc(sizeof(t_philo) * (input.number_of_philosophers + 1));
	while (i < input.number_of_philosophers)
	{
		g_philosophers[i].time_to_die = input.time_to_die;
		g_philosophers[i].time_to_eat = input.time_to_eat;
		g_philosophers[i].time_to_sleep = input.time_to_sleep;
		g_philosophers[i].desired_meals_count = input.number_of_times_each_philosopher_must_eat;
		g_philosophers[i].current_meals_count = 0;
		// init mutexes
		g_philosophers[i].is_left_taken = 0;
		g_philosophers[i].is_right_taken = 0;
		g_philosophers[i].is_eating = 0;
		i++;
	}
}

int			main(int ac, char **av)
{
	t_input	input;

	if ((ac != 5 && ac != 6) || is_bad_input(av))
	{
		ft_putstr_fd("error arguments count or bad content", 2);
		return (1);
	}
	init_input(ac, av, &input);
	init_philo(input);
	// save start time
	// usleep. create my function to count time without calculation errors

//	ft_alloc_check(g_philosophers);

	// Each philosopher should be given a number from 1 to ’number_of_philosophers’.

	// Philosopher number 1 is next to philosopher number ’number_of_philosophers’.
	//Any other philosopher with number N is seated between philosopher N - 1 and
	//philosopher N + 1

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