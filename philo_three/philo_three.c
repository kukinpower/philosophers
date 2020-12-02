/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 19:21:14 by mkristie          #+#    #+#             */
/*   Updated: 2020/12/02 02:14:04 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

t_philo			*g_philo;
sem_t			*g_message_sem;
pthread_t		*g_philo_threads;
size_t			g_start_time;
int				g_full_philos;

_Bool			monitor()
{
	int i;

	while (1)
	{
		i = 0;
		while (i < g_philo->n_philos)
		{
			if (g_philo[i].is_hungry && \
			get_time() - g_philo[i].last_meal_time > g_philo[i].time_to_die)
			{
				print_message(get_time() - g_start_time, i, DEATH);
				return (1);
			}
			if (g_full_philos && g_full_philos == g_philo->n_philos)
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
	free(g_philo);
	free(g_philo_threads);
	if (sem_close(g_forks) == -1)
		error_fatal();
	if (sem_close(g_message_sem) == -1)
		error_fatal();
}

int				main(int ac, char **av)
{
	int			i;

	if (parse(ac, av))
		return (1);
	init_forks(g_philo->n_philos);
	i = 0;
	g_full_philos = 0;
	g_start_time = get_time();
	while (i < g_philo->n_philos)
	{
		g_philo[i].last_meal_time = g_start_time;
		g_philo[i].num = i;
		g_philo[i].pid = fork();
		if (g_philo[i].pid < 0)
			error_fatal();
		else if (g_philo[i].pid == 0)
		{
			eat_sleep_repeat((void *)(&g_philo[i]));
			exit(0);
		}
		i++;
	}
	int	ret;

	ret = waitpid(-1, &status, 0);
	if (monitor(input))
		free_all_mem(input.n_philos);
	return (0);
}
