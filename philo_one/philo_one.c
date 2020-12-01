/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 19:21:14 by mkristie          #+#    #+#             */
/*   Updated: 2020/12/01 19:21:15 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

t_philo			*g_philos;
pthread_mutex_t	*g_forks;
pthread_t		*g_philo_threads;
size_t			g_start_time;
int				g_full_philos;

_Bool			monitor(t_input input)
{
	int i;

	while (1)
	{
		i = 0;
		while (i < input.n_philos)
		{
			if (g_philos[i].is_hungry && \
			get_time() - g_philos[i].last_meal_time > g_philos[i].time_to_die)
			{
				print_message(get_time() - g_start_time, i, DEATH);
				return (1);
			}
			if (g_full_philos && g_full_philos == input.n_philos)
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
	free(g_philos);
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
	g_full_philos = 0;
	g_start_time = get_time();
	while (i < input.n_philos)
	{
		g_philos[i].last_meal_time = g_start_time;
		if (pthread_create(&g_philo_threads[i], NULL, \
							eat_sleep_repeat, (void *)(&g_philos[i])))
			error_fatal();
		i++;
	}
	if (monitor(input))
		free_all_mem(input.n_philos);
	return (0);
}
