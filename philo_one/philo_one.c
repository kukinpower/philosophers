#include "philo_one.h"

int		main(int ac, char **av)
{
	if (ac != 5 && != 6)
	{
		ft_putstr_fd("error arguments count", 2);
		return (1);
	}
	int	number_of_philosophers; // also the num of forks;
	int	time_to_die; // in milliseconds. if a philosopher doesn’t start eating ’time_to_die’ milliseconds after starting his last meal or the beginning of the simulation, it dies
	int	time_to_eat; // in milliseconds and is the time it takes for a philosopher to eat. During that time he will need to keep the two forks.
	int time_to_sleep; // in milliseconds and is the time the philosopher will spend sleeping
	int	number_of_times_each_philosopher_must_eat; // is optional, if all philosophers eat at least ’number_of_times_each_philosopher_must_eat’ the simulation will stop. If not specified, the simulation will stop only at the death of a philosopher.


	// Each philosopher should be given a number from 1 to ’number_of_philosophers’.

	// Philosopher number 1 is next to philosopher number ’number_of_philosophers’.
	//Any other philosopher with number N is seated between philosopher N - 1 and
	//philosopher N + 1

	if (ac == 6)
	{
		number_of_times_each_philosopher_must_eat = ft_atoi(av[4]);
	}
	else
	{
		number_of_times_each_philosopher_must_eat = 0;
	}
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