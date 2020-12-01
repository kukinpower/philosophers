/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 23:11:48 by mkristie          #+#    #+#             */
/*   Updated: 2020/12/01 00:58:05 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

char			*get_action(int action)
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

char			*create_message(size_t time, int philo, int action)
{
	char		*time_str;
	char		*num_str;
	char		*message;
	char		*act;
	size_t		len;

	act = ft_strdup(get_action(action));
	ft_alloc_check(act);
	time_str = ft_itoa(time);
	ft_alloc_check(time_str);
	num_str = ft_itoa(philo + 1);
	ft_alloc_check(num_str);
	len = ft_strlen(time_str) + 2 + ft_strlen(time_str) + ft_strlen(act);
	if (!(message = malloc(len + 1)))
		return (NULL);
	*message = '\0';
	ft_strlcat(message, time_str, len);
	ft_strlcat(message, " ", len);
	ft_strlcat(message, num_str, len);
	ft_strlcat(message, act, len);
	free(act);
	free(time_str);
	free(num_str);
	return (message);
}

void			print_message(size_t time, int philo, int action)
{
	char		*msg;

	msg = create_message(time, philo, action);
	ft_putstr_fd(msg, 1);
	free(msg);
}
