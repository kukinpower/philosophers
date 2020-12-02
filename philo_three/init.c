/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 19:21:20 by mkristie          #+#    #+#             */
/*   Updated: 2020/12/02 02:12:29 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

_Bool		init_semaphors(int size)
{
	sem_unlink("/g_forks");
	if ((g_forks = sem_open("/g_forks", O_CREAT, S_IRWXU, size)) == SEM_FAILED)
		return (1);
	sem_unlink("/g_semathor");
	if ((g_forks = sem_open("/g_semathor", O_CREAT, S_IRWXU, 1)) == SEM_FAILED)
		return (1);
	return (0);
}
